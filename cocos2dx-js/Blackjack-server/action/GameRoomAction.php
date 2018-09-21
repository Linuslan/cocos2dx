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
			$roomId = null;
			while($row = mysql_fetch_array($result)) {
				$roomId = $row["roomId"];
			}
			//创建房间
			if($roomId == null) {
				$roomId = uniqid();
				$time = date('Y-m-j G:i:s');
				$gameRoom = new GameRoom();
				$gameRoom->setRoomId($roomId);
				$gameRoom->setRoomName("房间");
				$gameRoom->setStatus(0);
				$gameRoom->setCreateTime($time);
			}
			return $roomId;
		}

		public function playerReady($data) {
			$json = json_decode($data);
			$roomId = $json->{"roomId"};
			$playerId = $json->{"playerId"};
			$sql = "UPDATE tbl_wechat_game_room_player SET status = 1 WHERE room_id='".$roomId."' AND player_id=".$playerId;
			mysql_query($sql);
			//得出有多少个玩家已准备
			$sql = "SELECT COUNT(*) cnt FROM tbl_wechat_game_room_player t WHERE t.status = 1 AND t.room_id='".$roomId."'";
			$result = mysql_query($sql);
			$readyCount = 0;
			while($row = mysql_fetch_array($result)) {
				$readyCount = $row["cnt"];
			}
			$sql = "SELECT COUNT(*) cnt FROM tbl_wechat_game_room_player t WHERE t.room_id='".$roomId."'";
			$result = mysql_query($sql);
			$playerCount = 0;
			while($row = mysql_fetch_array($result)) {
				$playerCount = $row["cnt"];
			}
			$card = "";
			$socketIdStr = "";
			if($readyCount == $playerCount) {
				$card = "4,3,2,1";
				$sql = "SELECT t1.websocket_id FROM (SELECT * FROM tbl_wechat_game_room_player t WHERE t.room_id='".$roomId."') t INNER JOIN tbl_wechat_player t1 ON t.player_id = t1.id";
				$result = mysql_query($sql);
				$socketIds = array();
				while($row = mysql_fetch_array($result)) {
					array_push($socketIds, $row["websocket_id"]);
				}
				$socketIdStr = implode(",", $socketIds);
			}
			return "{\"cards\":\"".$card."\", \"socketIds\":\"".$socketIdStr."\"}";
		}
	}
?>