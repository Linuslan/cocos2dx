<?php
	$method = $_REQUEST["m"];
	if($method == "userLogin") {
		userLogin();
	}
	function userLogin() {
		$code=$_REQUEST["code"];
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
	}
?>