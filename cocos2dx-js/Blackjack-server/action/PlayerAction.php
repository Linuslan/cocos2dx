<?php
	include "../utils/JdbcUtil.php";
	class PlayerAction {
		getConn();
		function updateSocketId($data) {
			$json = json_decode($data);
			$websocketId = $json->{"webSocketId"};
			$playerId = $json->{"playerId"};
			$sql = "UPDATE tbl_wechat_player SET websocket_id='".$websocketId."' WHERE id=".$playerId;
			mysql_query($sql);
			return true;
		}
	}
?>