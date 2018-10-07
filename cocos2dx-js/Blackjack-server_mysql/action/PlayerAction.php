<?php
	$cur_dir=dirname(__FILE__);
	chdir($cur_dir);
	include_once "../utils/JdbcUtil.php";
	getConn();
	class PlayerAction {
		function updateSocketId($data) {
			//$json = json_decode($data);
			$websocketId = $data->{"socketId"};
			$playerId = $data->{"playerId"};
			$sql = "UPDATE tbl_wechat_player SET websocket_id='".$websocketId."' WHERE id=".$playerId;
			echo $sql."\n";
			mysql_query($sql);
			return true;
		}
		function updatePlayer($data) {
			$playerId = $data->{"playerId"};
			$avatarUrl = $data->{"avatarUrl"};
			$nickName = $data->{"nickName"};
			$sql = "UPDATE tbl_wechat_player SET avatar_url='".$avatarUrl."', user_name='".$nickName."' WHERE id=".$playerId;
			db_execute($sql);
			return true;
		}
	}
?>