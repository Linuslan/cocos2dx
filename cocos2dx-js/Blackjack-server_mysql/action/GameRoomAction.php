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
			if(mysql_num_rows($result) > 0) {
				while($row = mysql_fetch_array($result)) {
					$roomNo = $row["room_no"];
					$roomId = $row["id"];
				}
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
				$roomId = db_execute($sql);
				echo "new roomId is ".$roomId."\n";
			}
			$result = [];
			$result["roomNo"] = $roomNo;
			$result["gameLevel"] = $gameLevel;
			$result["roomId"] = $roomId;
			//return "{\"roomNo\":\"".$roomNo."\", \"gameLevel\": ".$gameLevel."}";
			return $result;
		}

		public function enterRoom($data) {
			$result = [];
			$roomNo = $data->{"roomNo"};
			$roomId = $data->{"roomId"};
			$playerId = $data->{"playerId"};
			$sql = "SELECT * FROM tbl_wechat_game_room t WHERE t.status = 0 AND t.id=".$roomId." ORDER BY t.id ASC LIMIT 1";
			$rows = mysql_query($sql);
			$roomNo = null;
			$roomId = null;
			if(mysql_num_rows($rows) < 1) {
				throw new Exception("{\"msg\":\"game room is not exist\", \"code\":\"1000-02\"}");
			}
			while($row = mysql_fetch_array($rows)) {
				$roomNo = $row["room_no"];
				$roomId = $row["id"];
			}
			$sql = "SELECT * FROM tbl_wechat_player t WHERE t.id=".$playerId;
			$rows = mysql_query($sql);
			if(mysql_num_rows($rows) < 1) {
				throw new Exception("{\"msg\":\"player is not exist\", \"code\":\"1000-03\"}");
			}
			$sql = "INSERT INTO tbl_wechat_game_room_player(room_id, room_no, player_id, status, score) VALUES(".$roomId.", '".$roomNo."', ".$playerId.", 0, 0)";
			db_execute($sql);
			$sql = "SELECT t1.websocket_id, t1.user_name, t1.avatar_url, t1.id FROM (SELECT * FROM tbl_wechat_game_room_player t WHERE t.room_no='".$roomNo."') t INNER JOIN tbl_wechat_player t1 ON t.player_id = t1.id";
			echo $sql."\n";
			$rs = mysql_query($sql);
			$socketIds = array();
			$players = [];
			$idx = 0;
			while($row = mysql_fetch_array($rs)) {
				echo "get socketid\n";
				array_push($socketIds, $row["websocket_id"]);
				$player = [];
				$player["avatarUrl"] = $row["avatar_url"];
				$player["userName"] = $row["user_name"];
				$player["id"] = $row["id"];
				$players[$idx] = $player;
				$idx ++;
			}
			$socketIdStr = implode(",", $socketIds);
			echo "socketids is ".$socketIdStr."\n";
			$result["enter"] = true;
			$result["socketIds"] = $socketIdStr;
			$result["playerId"] = $playerId;
			$result["players"] = $players;
			return $result;
		}

		public function playerReady($data) {
			$roomNo = $data->{"roomNo"};
			$playerId = $data->{"playerId"};
			$sql = "UPDATE tbl_wechat_game_room_player SET status = 1 WHERE room_no='".$roomNo."' AND player_id=".$playerId;
			db_execute($sql);
			//得出有多少个玩家已准备
			$sql = "SELECT COUNT(*) cnt FROM tbl_wechat_game_room_player t WHERE t.status = 1 AND t.room_no='".$roomNo."'";
			$rows = mysql_query($sql);
			$readyCount = 0;
			while($row = mysql_fetch_array($rows)) {
				$readyCount = $row["cnt"];
			}
			$sql = "SELECT COUNT(*) cnt FROM tbl_wechat_game_room_player t WHERE t.room_no='".$roomNo."' AND t.status <> 2";
			$rows = mysql_query($sql);
			$playerCount = 0;
			while($row = mysql_fetch_array($rows)) {
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
				$sql = "SELECT t1.websocket_id FROM (SELECT * FROM tbl_wechat_game_room_player t WHERE t.room_no='".$roomNo."' AND t.status = 1) t INNER JOIN tbl_wechat_player t1 ON t.player_id = t1.id";
				$rs = mysql_query($sql);
				$socketIds = array();
				while($row = mysql_fetch_array($rs)) {
					array_push($socketIds, $row["websocket_id"]);
				}
				$socketIdStr = implode(",", $socketIds);
				$sql = "UPDATE tbl_wechat_game_room SET status = 1 WHERE room_no='".$roomNo."'";
				db_execute($sql);
				//开始初始化游戏数据
				$initResult = $this->initGame($data);
				$gameNo = $initResult["gameNo"];
				//将准备好的玩家写入到tbl_wechat_game_room_number_player表中，表示即将参加本局游戏的玩家
				$sql = "SELECT * FROM tbl_wechat_game_room_player t WHERE t.room_no='".$roomNo."' AND t.status = 1";
				$rows = mysql_query($sql);
				while($row = mysql_fetch_array($rows)) {
					$playerId = $row["player_id"];
					$time = date('Y-m-j G:i:s');
					$sql = "INSERT INTO tbl_wechat_game_room_number_player(player_id, score, create_time, game_no, room_no, status) VALUES(".$playerId.", 0, '".$time."', ".$gameNo.", '".$roomNo."', 0)";
					db_execute($sql);
				}

				$data->{"gameNo"} = $gameNo;
				$refreshPokerResult = $this->refreshPoker($data);
				$result["gameNo"] = $initResult["gameNo"];
				$result["pokerCount"] = $refreshPokerResult["pokerCount"];
				$result["cards"] = $refreshPokerResult["cards"];
				$result["roundId"] = $refreshPokerResult["roundId"];
			}
			$result["playerId"] = $playerId;
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
			db_execute($sql);
			$pokerType = ["clubs", "diamonds", "hearts", "spades"];
			$count = 0;
			for($j = 0; $j < count($pokerType); $j ++) {
	            for($i = 0; $i < count($pokerValue); $i ++) {
	                $key = $pokerValue[$i]."-".$pokerType[$j];
	                $value = $pokerValue[$i];
	                $sql = "INSERT INTO tbl_wechat_game_room_poker(room_id, room_no, game_no, poker_key, poker_value, status, create_time) VALUES(".$roomId.", '".$roomNo."', ".$gameNo.", '".$key."', '".$value."', 0, '".date('Y-m-j G:i:s')."')";
	                db_execute($sql);
	                $count ++;
	            }
	        }
	        $result = [];
	        $result["pokerCount"] = $count;
	        $result["gameNo"] = $gameNo;
	        return $result;
		}

		public function refreshPoker($data) {
			$result = [];
			$roomNo = $data->{"roomNo"};
			$gameNo = $data->{"gameNo"};
			$sql = "SELECT * FROM tbl_wechat_game_room_poker t WHERE t.room_no = '".$roomNo."' AND t.status = 0 AND t.game_no=".$gameNo;
			$pokerlist = [];
			$rows = mysql_query($sql);
			$idx = 0;
			while($row = mysql_fetch_array($rows)) {
				$key = $row["poker_key"];
				$value = $row["poker_value"];
				$poker = [];
				$poker[$key]=$value;
				$poker["pokerId"] = $row["id"];
				$pokerlist[$idx] = $poker;
				$idx ++;
			}
			$count = count($pokerlist);
			$result["restart"] = false;
			$pokerCount = 0;
			if($count <= 0) {
				$result["restart"] = true;
				$result["pokerCount"] = $pokerCount;
				//没牌了，将房间状态更新为0，让其他玩家进入
				$sql = "UPDATE tbl_wechat_game_room SET t.status=0 WHERE t.room_no='".$roomNo."'";
				db_execute($sql);
				//throw new Exception("{\"code\":\"1000-02\", \"msg\":\"没牌啦，请重新开始\"}");
				return $result;
			}
			//生成新的一个回合
			$sql = "INSERT INTO tbl_wechat_game_room_round(room_no, create_time) VALUES('".$roomNo."', '".date('Y-m-j G:i:s')."')";
			$roundId = db_execute($sql);
			//获取本局中共有多少个准备好的玩家，生成这些玩家的新一回合的数据
			$sql = "SELECT * FROM tbl_wechat_game_room_number_player t WHERE t.status=0 AND t.room_no='".$roomNo."' AND t.game_no=".$gameNo;
			$rows = mysql_query($sql);
			while($row=mysql_fetch_array($rows)) {
				$playerId = $row["player_id"];
				$time = date('Y-m-j G:i:s');
				//生成新回合的玩家，用于表示本回合该玩家的状态是放弃还是已完成还是解题中
				$sql = "INSERT INTO tbl_wechat_game_room_round_player(game_no, round_id, player_id, status, create_time, room_no) VALUES('".$gameNo."', ".$roundId.", ".$playerId.", 0, '".$time."', '".$roomNo."')";
				db_execute($sql);
			}
			$pokerArr = [];
			for($i = 0; $i < 4; $i ++) {
				echo "poker's count is ".$count."\n";
				$idx = mt_rand(0, $count-1);
				echo "select ".$idx."\n";
				$poker = $pokerlist[$idx];
				$key = key($poker);
				$value = current($poker);
				$pokerId = $poker["pokerId"];
				$pokerArr[$key] = $value;
				$sql = "INSERT INTO tbl_wechat_game_room_round_poker(round_id, poker_id, poker_key, poker_value, create_time) VALUES('".$roundId."', ".$pokerId.", '".$key."', ".$value.", '".date('Y-m-j G:i:s')."')";
				db_execute($sql);
				$sql = "UPDATE tbl_wechat_game_room_poker SET status = 1 WHERE id=".$pokerId;
				db_execute($sql);
				array_splice($pokerlist, $idx, 1);
				$count = count($pokerlist);
			}
			$sql = "SELECT COUNT(*) cnt FROM tbl_wechat_game_room_poker t WHERE t.status = 0 AND t.game_no=".$gameNo." AND t.room_no='".$roomNo."'";
			echo $sql."\n";
			
			$rows = mysql_query($sql);
			while($row = mysql_fetch_array($rows)) {
				$pokerCount = $row["cnt"];
			}
			echo "left pokers is ".$pokerCount."\n";
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

		//提交的操作
		//1.玩家本局的积分加1，玩家自己的积分加1
		//2.将玩家的状态更新为本回合已完成的状态。
		//3.如果玩家选择放弃，则将玩家本回合的状态更新为放弃。
		//4.判断本房间内的所有玩家的状态是否都已经是放弃或者完成的状态，如果都是已完成或者已放弃的状态，则开始下一回合，即刷新扑克。
		//5.如果还有玩家未完成，则将该已完成的玩家的状态同时更新到本房间内的其他玩家的视图中。
		public function commit($data) {
			$roomNo = $data->{"roomNo"};
			$roundId = $data->{"roundId"};
			$playerId = $data->{"playerId"};
			$gameNo = $data->{"gameNo"};
			//玩家回合状态，0：解题中；1：完成；2：放弃；3：超时；4：离开；
			$status = $data->{"status"};
			echo "Update player's status\n";
			//更新玩家的回合状态
			$sql = "UPDATE tbl_wechat_game_room_round_player SET status=".$status." WHERE round_id=".$roundId." AND player_id=".$playerId." AND game_no=".$gameNo." AND room_no='".$roomNo."'";
			db_execute($sql);
			//如果状态是成功，则增加玩家的积分
			if($status == 1) {
				echo "update player score\n";
				//增加玩家的总积分
				$sql = "UPDATE tbl_wechat_player SET score=score+1 WHERE id=".$playerId;
				db_execute($sql);
				//增加玩家在本局的积分
				$sql = "UPDATE tbl_wechat_game_room_number_player SET score=score+1 WHERE game_no=".$gameNo." AND player_id=".$playerId." AND room_no='".$roomNo."'";
				db_execute($sql);
			}
			//查询本回合内的玩家是否还有处于未完成的状态，如果没有，则开始新的一个回合，不管有没有，都需要更新玩家的视图
			$sql = "SELECT COUNT(*) cnt FROM tbl_wechat_game_room_round_player t WHERE t.status = 0 AND game_no=".$gameNo." AND room_no='".$roomNo."' AND round_id=".$roundId;
			echo $sql."\n";
			$rows = mysql_query($sql);
			$count = 0;
			while($row = mysql_fetch_array($rows)) {
				$count = $row["cnt"];
			}
			echo "unfinished player's count is ".$count."\n";
			$newRound = false;
			//说明玩家都已经完成
			if($count <= 0) {
				$newRound = true;
			}
			$result = [];
			$result["status"] = $status;
			$result["newRound"] = $newRound;
			$result["playerId"]=$playerId;
			//查询当前玩家在本局内已经得到了多少分
			$sql = "SELECT * FROM tbl_wechat_game_room_number_player t WHERE t.room_no='".$roomNo."' AND t.player_id=".$playerId." AND t.game_no=".$gameNo;
			$rows = mysql_query($sql);
			$score = 0;
			while($row = mysql_fetch_array($rows)) {
				$score = $row["score"];
			}
			$result["score"] = $score;
			$sql = "SELECT t1.websocket_id FROM (SELECT * FROM tbl_wechat_game_room_player t WHERE t.room_no='".$roomNo."' AND t.status = 1) t INNER JOIN tbl_wechat_player t1 ON t.player_id = t1.id";
			$rs = mysql_query($sql);
			$socketIds = array();
			while($row = mysql_fetch_array($rs)) {
				array_push($socketIds, $row["websocket_id"]);
			}
			$socketIdStr = implode(",", $socketIds);
			echo "upgrade player's socket is ".$socketIdStr."\n";
			$result["socketIds"] = $socketIdStr;
			if($newRound) {
				echo "new round is start\n";
				$refreshResult = $this->refreshPoker($data);
				$result["restart"] = $refreshResult["restart"];
				$result["pokerCount"] = $refreshResult["pokerCount"];
				$result["status"] = 0;
				if($refreshResult["restart"] == false) {
					$result["cards"] = $refreshResult["cards"];
					$result["roundId"] = $refreshResult["roundId"];
				}
			}
			return $result;
		}

		public function quitRoom($data) {
			echo "player quit room";
			$time = date('Y-m-j G:i:s');
			$playerId = $data->{"playerId"};
			$roomNo = $data->{"roomNo"};
			$gameNo = $data->{"gameNo"};
			$roundId = $data->{"roundId"};
			$sql = "UPDATE tbl_wechat_game_room_player SET status = 2, quit_time='".$time."' WHERE room_no='".$roomNo."' AND player_id=".$playerId;
			db_execute($sql);
			
			if(!empty($gameNo)) {
				$sql = "UPDATE tbl_wechat_game_room_number_player SET status = 1 WHERE room_no='".$roomNo."' AND game_no=".$gameNo." AND player_id=".$playerId;
				db_execute($sql);
				if(!empty($roundId)) {
					$sql = "UPDATE tbl_wechat_game_room_round_player SET status = 1 WHERE room_no='".$roomNo."' AND game_no=".$gameNo." AND round_id=".$roundId." AND player_id=".$playerId;
					db_execute($sql);
				}
			}
			$result = [];
			//如果房间没玩家了，则将房间关闭
			$sql = "SELECT COUNT(*) cnt FROM tbl_wechat_game_room_player WHERE status<>2 AND room_no='".$roomNo."'";
			$rows = mysql_query($sql);
			$playerCount = 0;
			while($row = mysql_fetch_array($rows)) {
				$playerCount = $row["cnt"];
			}
			if($playerCount <= 0) {
				$sql = "UPDATE tbl_wechat_game_room SET status = 2 WHERE room_no='".$roomNo."'";
				db_execute($sql);
			} else {
				$sql = "SELECT t1.websocket_id FROM (SELECT * FROM tbl_wechat_game_room_player t WHERE t.room_no='".$roomNo."' AND t.status = 1) t INNER JOIN tbl_wechat_player t1 ON t.player_id = t1.id";
				$rows = mysql_query($sql);
				$socketIds = array();
				while($row = mysql_fetch_array($rows)) {
					array_push($socketIds, $row["websocket_id"]);
				}
				$socketIdStr = implode(",", $socketIds);
				echo "upgrade player's socket is ".$socketIdStr."\n";
				$result["socketIds"] = $socketIdStr;
			}
			$result["playerId"] = $playerId;
			return $result;
		}

		public function quitRoomBySocketId($clients, $socketId) {
			$playerId = null;
			$sql = "SELECT * FROM tbl_wechat_player t WHERE t.websocket_id='".$socketId."'";
			$rows = mysql_query($sql);
			while($row = mysql_fetch_array($rows)) {
				$playerId = $row["id"];
			}
			if($playerId != null) {
				$time = date('Y-m-j G:i:s');
				$sql = "UPDATE tbl_wechat_game_room_player SET status = 2, quit_time='".$time."' WHERE player_id=".$playerId;
				db_execute($sql);
				$sql = "UPDATE tbl_wechat_game_room_number_player SET status = 1 WHERE player_id=".$playerId;
				db_execute($sql);
				$sql = "UPDATE tbl_wechat_game_room_round_player SET status = 1 WHERE player_id=".$playerId;
				db_execute($sql);
				$sql = "SELECT * FROM tbl_wechat_game_room_player WHERE player_id=".$playerId;
				$roomIdArr = [];
				$rows = mysql_query($sql);
				while($row = mysql_fetch_array($rows)) {
					$roomNo = $row["room_no"];
					$sql = "SELECT COUNT(*) cnt FROM tbl_wechat_game_room_player WHERE status<>2 AND room_no='".$roomNo."'";
					$rows = mysql_query($sql);
					$playerCount = 0;
					while($row = mysql_fetch_array($rows)) {
						$playerCount = $row["cnt"];
					}
					if($playerCount <= 0) {
						$sql = "UPDATE tbl_wechat_game_room SET status = 2 WHERE room_no='".$roomNo."'";
						db_execute($sql);
					} else {
						$sql = "SELECT t1.websocket_id FROM (SELECT * FROM tbl_wechat_game_room_player t WHERE t.room_no='".$roomNo."' AND t.status = 1) t INNER JOIN tbl_wechat_player t1 ON t.player_id = t1.id";
						$rows = mysql_query($sql);
						$socketIds = array();
						while($row = mysql_fetch_array($rows)) {
							array_push($socketIds, $row["websocket_id"]);
						}
						$result = [];
						$data = [];
						$data["playerId"] = $playerId;
						$result["cmd"] = "quitRoom";
						$result["success"] = true;
						$result["data"] = $data;
						foreach($socketIds as $socketId) {
			            	echo "socketId:".$socketId."\n";
			                $socket = $clients[$socketId];
			                $socket->send(json_encode($result));
			                echo "upgrade player's socket is ".$socketId."\n";
			            }
					}
				}
			}
		}
	}
?>