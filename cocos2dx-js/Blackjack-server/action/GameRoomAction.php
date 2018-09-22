<?php
	$cur_dir=dirname(__FILE__);
	chdir($cur_dir);
	include_once "../utils/JdbcUtil.php";
	include_once "../model/GameRoom.php";
	getConn();
	class GameRoomAction {
		
		//搜索房间，如果有空闲房间，则进入空闲房间，如果没有空闲房间，则创建一个房间，等待玩家进入
		public function searchRoom($data) {
			$sql = "SELECT * FROM tbl_wechat_game_room t WHERE t.status = 0 ORDER BY t.id ASC LIMIT 1";
			$result = mysql_query($sql);
			$roomNo = null;
			while($row = mysql_fetch_array($result)) {
				$roomNo = $row["room_no"];
			}
			//创建房间
			if($roomId == null) {
				$roomNo = uniqid();
				$time = date('Y-m-j G:i:s');
				$gameRoom = new GameRoom();
				$gameRoom->setRoomNo($roomId);
				$gameRoom->setRoomName("房间");
				$gameRoom->setStatus(0);
				$gameRoom->setCreateTime($time);
			}
			return $roomId;
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
	}
?>