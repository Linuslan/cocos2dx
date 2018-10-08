<?php
require_once __DIR__ . '/Workerman/Autoloader.php';
include_once __DIR__."/action/GameRoomAction.php";
include_once __DIR__."/action/PlayerAction.php";
include_once __DIR__."/action/UserAction.php";
use Workerman\Worker;

$gameRoomAction = new GameRoomAction();
$playerAction = new PlayerAction();

// 证书最好是申请的证书
$context = array(
    // 更多ssl选项请参考手册 http://php.net/manual/zh/context.ssl.php
    'ssl' => array(
        // 请使用绝对路径
        'local_cert'                 => dirname(__FILE__).'\\1_www.uxgoo.com_bundle.crt', // 也可以是crt文件
        'local_pk'                   => dirname(__FILE__).'\\2_www.uxgoo.com.key',
        'verify_peer'                => false,
        "verify_peer_name"			 => false,
        // 'allow_self_signed' => true, //如果是自签名证书需要开启此选项
    )
);
// 这里设置的是websocket协议（端口任意，但是需要保证没被其它程序占用）
$worker = new Worker('websocket://0.0.0.0:443', $context);
// 设置transport开启ssl，websocket+ssl即wss
$worker->transport = 'ssl';
$clients = [];
$worker->onMessage = function($con, $msg) {
	global $playerAction;
	global $gameRoomAction;
	global $clients;
	echo "receive:".$msg."\n";
	$result = [];
	$result["success"] = false;
	$result["msg"] = "";
	$result["code"] = "";
	$result["data"] = "";
	$isSend = false;
	try {
		if($msg == null) {
			throw new Exception("{\"msg\":\"command is null\", \"code\": \"1\"}");
		}
		$jsonData = json_decode($msg);
		$cmd = $jsonData->{"cmd"};	//获取指令
		$result["cmd"] = $cmd;
		//var_dump($clients);
		if($cmd == "userLogin") {
			$data = $jsonData->{"data"};
			$res = userLogin($data);
			$result["data"] = $res;
		} else if($cmd == "getSocketId") {
			$socketId = uniqid();
			$data = [];
			$data["socketId"] = $socketId;
			$result["data"] = $data;
			$clients[$socketId] = $con;
		} else if($cmd == "updateSocketId") {
			$data = $jsonData->{"data"};
			$rs = $playerAction->updateSocketId($jsonData->{"data"});
			echo "updateSocketId result:".$rs."\n";
		} else if($cmd == "updatePlayer") {
			$data = $jsonData->{"data"};
			$rs = $playerAction->updatePlayer($data);
		} else if($cmd == "searchRoom") {
            $rs = $gameRoomAction->searchRoom($jsonData->{"data"});
            if($rs != null) {
                $result["data"] = $rs;
            }
        } else if($cmd == "enterRoom") {
            $rs = $gameRoomAction->enterRoom($jsonData->{"data"});
            $result["data"] = $rs;
			$result["success"] = true;
			$currSocketId = $jsonData->{"data"}->{"socketId"};
			$socketIds = $rs["socketIds"];
        	echo "playerReady->socketIds:".$socketIds."\n";
            $socketArr = explode(",", $socketIds);
            foreach($socketArr as $socketId) {
            	echo "socketId:".$socketId."\n";
            	if($socketId == $currSocketId) {
            		$isSend = true;  //确保后面不会再发送
            	}
                $socket = $clients[$socketId];
                $socket->send(json_encode($result));
            }
        } else if ($cmd == "playerReady") {
			$currSocketId = $jsonData->{"data"}->{"socketId"};
			$rs = $gameRoomAction->playerReady($jsonData->{"data"});
			$result["data"] = $rs;
			$result["success"] = true;
            if($rs["isCountDown"]) {
            	$socketIds = $rs["socketIds"];
            	echo "enterRoom->socketIds:".$socketIds."\n";
	            $socketArr = explode(",", $socketIds);
	            foreach($socketArr as $socketId) {
	            	echo "socketId:".$socketId."\n";
	            	if($socketId == $currSocketId) {
	            		$isSend = true;  //确保后面不会再发送
	            	}
	                $socket = $clients[$socketId];
	                var_dump($socket);
	                $socket->send(json_encode($result));
	            }
            }
		} else if($cmd == "refreshPoker") {
            $data = $jsonData->{"data"};
            $rs = $gameRoomAction->refreshPoker($data);
            $result["data"] = $rs;
        } else if($cmd == "initGame") {
            $data = $jsonData->{"data"};
            $rs = $gameRoomAction->initGame($data);
            $result["data"] = $rs;
        } else if($cmd == "commit") {
            $data = $jsonData->{"data"};
            $currSocketId = $jsonData->{"data"}->{"socketId"};
            $rs = $gameRoomAction->commit($data);
            $result["data"] = $rs;
            $result["success"] = true;
            $socketIds = $rs["socketIds"];
        	echo "playerReady->socketIds:".$socketIds."\n";
            $socketArr = explode(",", $socketIds);
            foreach($socketArr as $socketId) {
            	echo "socketId:".$socketId."\n";
            	if($socketId == $currSocketId) {
            		$isSend = true;  //确保后面不会再发送
            	}
                $socket = $clients[$socketId];
                $socket->send(json_encode($result));
            }
        }
		$result["success"] = true;
	} catch(Exception $ex) {
		$errJson = json_decode($ex->getMessage());
		$result["success"] = false;
		$result["msg"] = $errJson->{"msg"};
		$result["code"] = $errJson->{"code"};
	}
	if(!$isSend) {
		$con->send(json_encode($result));
	}
    //$con->send('ok');
};

Worker::runAll();

?>