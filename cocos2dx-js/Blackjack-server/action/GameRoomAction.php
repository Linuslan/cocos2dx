<?php
	$cur_dir=dirname(__FILE__);
	chdir($cur_dir);
	include_once "../utils/JdbcUtil.php";
	include_once "../model/GameRoom.php";
	getConn();
	class GameRoomAction {
		
		//搜索房间，如果有空闲房间，则进入空闲房间，如果没有空闲房间，则创建一个房间，等待玩家进入
		public function searchRoom($data) {
			$gameLevel = $data->{"gameLevel"};
			$sql = "SELECT * FROM tbl_wechat_game_room t WHERE t.status = 0 ORDER BY t.id ASC LIMIT 1";
			$result = mysql_query($sql);
			$roomNo = null;
			$roomId = null;
			while($row = mysql_fetch_array($result)) {
				$roomNo = $row["room_no"];
				$roomId = $row["id"];
			}
			//创建房间
			if($roomNo == null) {
				$roomNo = uniqid();
				$time = date('Y-m-j G:i:s');
				$gameRoom = new GameRoom();
				$gameRoom->setRoomNo($roomNo);
				$gameRoom->setRoomName("房间");
				$gameRoom->setStatus(0);
				$gameRoom->setCreateTime($time);
				$sql = "INSERT INTO tbl_wechat_game_room(room_no, room_name, create_time, status, pwd) VALUES('".$roomNo."', '', '".$time."', 0, '')";
				echo $sql."\n";
				mysql_query($sql);
				$roomId = mysql_insert_id();
			}
			$result = [];
			$result["roomNo"] = $roomNo;
			$result["gameLevel"] = $gameLevel;
			$result["roomId"] = $roomId;
			//return "{\"roomNo\":\"".$roomNo."\", \"gameLevel\": ".$gameLevel."}";
			return $result;
		}

		public function enterRoom($data) {
			$roomNo = $data->{"roomNo"};
			$roomId = $data->{"roomId"};
			$playerId = $data->{"playerId"};
			$sql = "SELECT * FROM tbl_wechat_game_room t WHERE t.status = 0 AND t.id=".$roomId." ORDER BY t.id ASC LIMIT 1";
			$result = mysql_query($sql);
			$roomNo = null;
			$roomId = null;
			if(mysql_num_rows($result) < 1) {
				throw new Exception("{\"msg\":\"game room is not exist\", \"code\":\"1000-02\"}");
			}
			while($row = mysql_fetch_array($result)) {
				$roomNo = $row["room_no"];
				$roomId = $row["id"];
			}
			$sql = "SELECT * FROM tbl_wechat_player t WHERE t.id=".$playerId;
			$result = mysql_query($sql);
			if(mysql_num_rows($result) < 1) {
				throw new Exception("{\"msg\":\"player is not exist\", \"code\":\"1000-03\"}");
			}
			$sql = "INSERT INTO tbl_wechat_game_room_player(room_id, room_no, player_id, status, score) VALUES(".$roomId.", '".$roomNo."', ".$playerId.", 0, 0)";
			echo $sql."\n";
			mysql_query($sql);
			return true;
		}

		public function playerReady($data) {
			$roomNo = $data->{"roomNo"};
			$playerId = $data->{"playerId"};
			$sql = "UPDATE tbl_wechat_game_room_player SET status = 1 WHERE room_no='".$roomNo."' AND player_id=".$playerId;
			mysql_query($sql);
			//得出有多少个玩家已准备
			$sql = "SELECT COUNT(*) cnt FROM tbl_wechat_game_room_player t WHERE t.status = 1 AND t.room_no='".$roomNo."'";
			$result = mysql_query($sql);
			$readyCount = 0;
			while($row = mysql_fetch_array($result)) {
				$readyCount = $row["cnt"];
			}
			$sql = "SELECT COUNT(*) cnt FROM tbl_wechat_game_room_player t WHERE t.room_no='".$roomNo."'";
			$result = mysql_query($sql);
			$playerCount = 0;
			while($row = mysql_fetch_array($result)) {
				$playerCount = $row["cnt"];
			}
			$card = "";
			$socketIdStr = "";
			$isCountDown = false;
			$second = 5;
			$result = [];
			if($readyCount == $playerCount) {
				$isCountDown = true;
				//$card = "4,3,2,1";
				$sql = "SELECT t1.websocket_id FROM (SELECT * FROM tbl_wechat_game_room_player t WHERE t.room_no='".$roomNo."') t INNER JOIN tbl_wechat_player t1 ON t.player_id = t1.id";
				$rs = mysql_query($sql);
				$socketIds = array();
				while($row = mysql_fetch_array($rs)) {
					array_push($socketIds, $row["websocket_id"]);
				}
				$socketIdStr = implode(",", $socketIds);
				$sql = "UPDATE tbl_wechat_game_room SET status = 1 WHERE room_no='".$roomNo."'";
				mysql_query($sql);
				//开始初始化游戏数据
				$initResult = $this->initGame($data);
				$data->{"gameNo"} = $initResult["gameNo"];
				$refreshPokerResult = $this->refreshPoker($data);
				$result["gameNo"] = $initResult["gameNo"];
				$result["pokerCount"] = $refreshPokerResult["pokerCount"];
				$result["cards"] = $refreshPokerResult["cards"];
				$result["roundId"] = $refreshPokerResult["roundId"];
			}
			
			$result["isCountDown"] = $isCountDown;
			$result["second"] = $second;
			$result["socketIds"] = $socketIdStr;
			//return "{\"isCountDown\": ".$isCountDown.", \"second\": ".$second.", \"cards\":\"".$card."\", \"socketIds\":\"".$socketIdStr."\"}";
			return $result;
		}

		public function initGame($data) {
			$roomNo = $data->{"roomNo"};
			$sql = "SELECT * FROM tbl_wechat_game_room t WHERE t.room_no = '".$roomNo."'";
			$result = mysql_query($sql);
			$roomId = null;
			while($row = mysql_fetch_array($result)) {
				$roomId = $row["id"];
			}
			if($roomId == null) {
				throw new Exception("{\"msg\": \"未查询到房间\", \"code\": \"1000-01\"}");
			}
			$gameLevel = $data->{"gameLevel"};
			$pokerValue = [];
			if($gameLevel == 0) {
				$pokerValue = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
			} else if($gameLevel == 1) {
				$pokerValue = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13];
			}
			$sql = "SELECT MAX(game_no) gameNo FROM tbl_wechat_game_room_number WHERE room_no='".$roomNo."'";
			$rs = mysql_query($sql);
			$gameNo = 0;
			while($row = mysql_fetch_array($rs)) {
				$gameNo = $row["gameNo"];
			}
			$gameNo += 1;
			$sql = "INSERT INTO tbl_wechat_game_room_number(room_no, game_no, create_time) VALUES('".$roomNo."', ".$gameNo.", '".date('Y-m-j G:i:s')."')";
			mysql_query($sql);
			$pokerType = ["clubs", "diamonds", "hearts", "spades"];
			$count = 0;
			for($j = 0; $j < count($pokerType); $j ++) {
	            for($i = 0; $i < count($pokerValue); $i ++) {
	                $key = $pokerValue[$i]."-".$pokerType[$j];
	                $value = $pokerValue[$i];
	                $sql = "INSERT INTO tbl_wechat_game_room_poker(room_id, room_no, game_no, poker_key, poker_value, status, create_time) VALUES(".$roomId.", '".$roomNo."', ".$gameNo.", '".$key."', '".$value."', 0, '".date('Y-m-j G:i:s')."')";
	                mysql_query($sql);
	                $count ++;
	            }
	        }
	        $result = [];
	        $result["pokerCount"] = $count;
	        $result["gameNo"] = $gameNo;
	        return $result;
		}

		public function refreshPoker($data) {
			$roomNo = $data->{"roomNo"};
			$gameNo = $data->{"gameNo"};
			$sql = "SELECT * FROM tbl_wechat_game_room_poker t WHERE t.room_no = '".$roomNo."' AND t.status = 0 AND t.game_no=".$gameNo;
			$pokerlist = [];
			$result = mysql_query($sql);
			$idx = 0;
			while($row = mysql_fetch_array($result)) {
				$key = $row["poker_key"];
				$value = $row["poker_value"];
				$poker = [];
				$poker[$key]=$value;
				$poker["pokerId"] = $row["id"];
				$pokerlist[$idx] = $poker;
				$idx ++;
			}
			$count = count($pokerlist);
			if($count <= 0) {
				throw new Exception("{\"code\":\"1000-02\", \"msg\":\"没牌啦，请重新开始\"}");
			}
			$sql = "INSERT INTO tbl_wechat_game_room_round(room_no, create_time) VALUES('".$roomNo."', '".date('Y-m-j G:i:s')."')";
			mysql_query($sql);
			$roundId = mysql_insert_id();
			$pokerArr = [];
			for($i = 0; $i < 4; $i ++) {
				$idx = mt_rand(0, $count-1);
				$poker = $pokerlist[$idx];
				$key = key($poker);
				$value = current($poker);
				$pokerId = $poker["pokerId"];
				$pokerArr[$key] = $value;
				$sql = "INSERT INTO tbl_wechat_game_room_round_poker(round_id, poker_id, poker_key, poker_value, create_time) VALUES('".$roundId."', ".$pokerId.", '".$key."', ".$value.", '".date('Y-m-j G:i:s')."')";
				mysql_query($sql);
				$sql = "UPDATE tbl_wechat_game_room_poker SET status = 1 WHERE id=".$pokerId;
				mysql_query($sql);
			}
			$sql = "SELECT COUNT(*) cnt FROM tbl_wechat_game_room_poker t WHERE t.status = 0 AND t.game_no='".$gameNo."' AND t.room_no='".$roomNo."'";
			$pokerCount = 0;
			while($row = mysql_fetch_array($result)) {
				$pokerCount = $row["cnt"];
			}
			$result = [];
			$result["cards"] = json_encode($pokerArr);
			$result["roundId"] = $roundId;
			$result["pokerCount"] = $pokerCount;
			//return "{\"cards\": ".json_encode($pokerArr).", \"roundId\":".$roundId."}";
			return $result;
		}
		
		public function playerInfo($data) {
			$roomNo = $data->{"roomNo"};
			$gameNo = $data->{"gameNo"};

		}

		public function commit($data) {
			$roomNo = $data->{"roomNo"};
			$roundId = $data->{"roundId"};
			$playerId = $data->{"playerId"};
			$sql = "SELECT * FROM tbl_wechat_game_room_round_poker t WHERE t.round_id=".$roundId;
			$sql = "SELECT * FROM tbl_wechat_player t WHERE t.id=".$playerId;
			$score = 0;
			$result = mysql_query($sql);
			while($row = mysql_fetch_array($result)) {
				$score = $row["score"];
			}
			$score += 1;
			$sql = "UPDATE tbl_wechat_player SET score=".$score." WHERE id=".$playerId;
			mysql_query($sql);
		}
	}
?>