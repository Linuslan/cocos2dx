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
			while($row = mysql_fetch_array($result)) {
				$roomNo = $row["room_no"];
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
				echo $sql;
				mysql_query($sql);
			}
			return "{\"roomNo\":\"".$roomNo."\", \"gameLevel\": ".$gameLevel."}";
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
			if($readyCount == $playerCount) {
				$isCountDown = true;
				$card = "4,3,2,1";
				$sql = "SELECT t1.websocket_id FROM (SELECT * FROM tbl_wechat_game_room_player t WHERE t.room_no='".$roomNo."') t INNER JOIN tbl_wechat_player t1 ON t.player_id = t1.id";
				$result = mysql_query($sql);
				$socketIds = array();
				while($row = mysql_fetch_array($result)) {
					array_push($socketIds, $row["websocket_id"]);
				}
				$socketIdStr = implode(",", $socketIds);
				$sql = "UPDATE tbl_wechat_game_room SET status = 1 WHERE room_no='".$roomNo."'";
				mysql_query($sql);
			}
			return "{\"isCountDown\": ".$isCountDown.", \"second\": ".$second.", \"cards\":\"".$card."\", \"socketIds\":\"".$socketIdStr."\"}";
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
			$pokerType = ["clubs", "diamonds", "hearts", "spades"];
			$count = 0;
			for($j = 0; $j < count($pokerType); $j ++) {
	            for($i = 0; $i < count($pokerValue); $i ++) {
	                $key = $pokerValue[$i]."-".$pokerType[$j];
	                $value = $pokerValue[$i];
	                $sql = "INSERT INTO tbl_wechat_game_room_poker(room_id, room_no, poker_key, poker_value, status, create_time) VALUES(".$roomId.", '".$roomNo."', '".$key."', '".$value."', 0, '".date('Y-m-j G:i:s')."')";
	                mysql_query($sql);
	                $count ++;
	            }
	        }
	        return "{\"pokerCount\":".$count."}";
		}

		public function refreshPoker($data) {
			$roomNo = $data->{"roomNo"};
			$sql = "SELECT * FROM tbl_wechat_game_room_poker t WHERE t.room_no = '".$roomNo."' AND t.status = 0";
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
				$idx = mt_rand(0, $count);
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
			return "{\"cards\": ".json_encode($pokerArr).", \"roundId\":".$roundId."}";
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