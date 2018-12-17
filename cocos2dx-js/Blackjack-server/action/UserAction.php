<?php
	//include_once "utils/JdbcUtil.php";
	$cur_dir=dirname(__FILE__);
	chdir($cur_dir);
	include_once "../utils/JdbcUtil.php";
	$conn = getConn();
	/*$method = $_REQUEST["m"];
	if($method == "userLogin") {
		userLogin();
	}*/
	function userLogin($data) {
		//$code=$_REQUEST["code"];
		$code = $data->{"code"};
		$appSecret = "709a289f7d94b235d42fa9aac3b44449";
		$appId = "wx6dfb528574f8fb69";
		$url = "https://api.weixin.qq.com/sns/jscode2session?appid=".$appId."&secret=".$appSecret."&js_code=".$code."&grant_type=authorization_code";
		$curl=curl_init();
		curl_setopt($curl, CURLOPT_URL, $url);
		curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, FALSE);
	    curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, FALSE);
		curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($curl, CURLOPT_CONNECTTIMEOUT, 5);
	    $output = curl_exec($curl);
	    curl_close($curl);
		//$json = json_decode($output, true);
		//$openId = $json["openid"];
		$json = json_decode($output);
		$openId = $json->{"openid"};
		$sql = "SELECT * FROM tbl_wechat_player t WHERE t.openid='".$openId."'";
		$result = mysqli_query($conn, $sql);
		$userCount = 0;
		$id = null;
		$userName = "";
		while($row = mysqli_fetch_array($result, MYSQL_BOTH)) {
			$id = $row["id"];
			$userName = $row["user_name"];
		}
		if($id == null || $id < 0) {
			$sql = "INSERT INTO tbl_wechat_player(openid, score, create_time, login_time) VALUES('".$openId."', 0, '".date("Y-m-d H:i:s")."', '".date("Y-m-d H:i:s")."')";
			$id = db_execute($sql);
		}
		echo "{\"playerId\": \"".$id."\", \"userName\":\"".$userName."\"}\n";
		$result = [];
		$result["playerId"] = $id;
		$result["userName"] = $userName;
		return $result;
	}
?>