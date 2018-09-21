<?php
require_once __DIR__ . '/Workerman/Autoloader.php';
use Workerman\Worker;
echo dirname(__FILE__).'\\2_www.uxgoo.com.crt';
echo "    ";
echo dirname(__FILE__).'\\3_www.uxgoo.com.key';
// 证书最好是申请的证书
$context = array(
    // 更多ssl选项请参考手册 http://php.net/manual/zh/context.ssl.php
    'ssl' => array(
        // 请使用绝对路径
        'local_cert'                 => dirname(__FILE__).'\\2_www.uxgoo.com.crt', // 也可以是crt文件
        'local_pk'                   => dirname(__FILE__).'\\3_www.uxgoo.com.key',
        'verify_peer'                => false,
        "verify_peer_name"			 => false,
        // 'allow_self_signed' => true, //如果是自签名证书需要开启此选项
    )
);
// 这里设置的是websocket协议（端口任意，但是需要保证没被其它程序占用）
$worker = new Worker('websocket://0.0.0.0:8083', $context);
// 设置transport开启ssl，websocket+ssl即wss
$worker->transport = 'ssl';
$worker->onMessage = function($con, $msg) {
	echo "receive:".$msg;
    $con->send('ok');
};

Worker::runAll();

?>