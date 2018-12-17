<?php
/**
 * Created by xwx
 * Date: 2017/10/18
 * Time: 14:33
 */
include_once dirname(__FILE__)."/action/GameRoomAction.php";
include_once dirname(__FILE__)."/action/PlayerAction.php";
$gameRoomAction = new GameRoomAction();
$playerAction = new PlayerAction();
class SocketService
{
    private $address  = '0.0.0.0';
    private $port = 8083;
    private $_sockets;
    public function __construct($address = '', $port='')
    {
            if(!empty($address)){
                $this->address = $address;
            }
            if(!empty($port)) {
                $this->port = $port;
            }
    }
 
    public function service(){
        //获取tcp协议号码。
        $tcp = getprotobyname("tcp");
        $sock = socket_create(AF_INET, SOCK_STREAM, $tcp);
        socket_set_option($sock, SOL_SOCKET, SO_REUSEADDR, 1);
        
        if($sock < 0)
        {
            throw new Exception("failed to create socket: ".socket_strerror($sock)."\n");
        }
        socket_bind($sock, $this->address, $this->port);
        socket_listen($sock, $this->port);
        /*$context = stream_context_create();

        // local_cert must be in PEM format
        stream_context_set_option($context, 'ssl', 'local_cert', "D:/Study/php/2_www.uxgoo.com.crt");
        stream_context_set_option($context, 'ssl', 'local_pk', 'D:/Study/php/3_www.uxgoo.com.key');
        // Pass Phrase (password) of private key
        //stream_context_set_option($context, 'ssl', 'passphrase', $pem_passphrase);
        stream_context_set_option($context, 'ssl', 'allow_self_signed', true);
        stream_context_set_option($context, 'ssl', 'verify_peer', false);

        // Create the server socket
        $sock = stream_socket_server(
            'ssl://0.0.0.0:8083',
            $errno,
            $errstr,
            STREAM_SERVER_BIND|STREAM_SERVER_LISTEN,
            $context
        );*/
        echo "listen on $this->address $this->port ... \n";
        $this->_sockets = $sock;
    }
 
    public function run(){
        $this->service();
        $clients[] = $this->_sockets;
        while (true){
            $changes = $clients;
            $write = NULL;
            $except = NULL;
            socket_select($changes,  $write,  $except, NULL);
            foreach ($changes as $key => $_sock){
                if($this->_sockets == $_sock){ //判断是不是新接入的socket
                    if(($newClient = socket_accept($_sock))  === false){
                        die('failed to accept socket: '.socket_strerror($_sock)."\n");
                    }
                    $line = trim(socket_read($newClient, 1024));
                    $this->handshaking($newClient, $line);
                    //获取client ip
                    socket_getpeername ($newClient, $ip);
                    $id = uniqid();
                    $clients[$id] = $newClient;
                    echo  "Client ip:{$ip}   \n";
                    echo "Client msg:{$line} \n";
                    echo "command:{$id}";
                    $this->send($newClient, $id);
                } else {
                    try {
                        $i = socket_recv($_sock, $buffer,  2048, 0);
                        if($i === false) {
                            echo "socket 异常 ".socket_strerror($_sock)."\n";
                            array_splice($clients, intval($key), 1);
                            break;
                        }
                        $msg = $this->message($buffer);
                        $json = json_decode($msg);
                        $command = $json->{"command"};
                        $response = null;
                        if($command == "updateSocketId") {
                            $result = $playerAction->updateSocketId($json->{"data"});
                            if($result == true) {
                                $this->send($_sock, "{\"result\":true}");
                            } else {
                                $this->send($_sock, "{\"result\":false}");
                            }
                        } else if($command == "searchRoom") {
                            $response = $gameRoomAction->searchRoom($json->{"data"});
                            $this->send($_sock, $response);
                        } else if($command == "playerReady") {
                            $result = $gameRoomAction->playerReady($json->{"data"});
                            $resultJson = json_decode($result);
                            $socketIds = $resultJson->{"socketIds"};
                            $socketArr = explode(",", $socketIds);
                            foreach($socketArr as $socketId) {
                                $socket = $clients[$socketId];
                                $this->send($socket, $resultJson->{"card"});
                            }
                        }
                    } catch(Exception $ex) {

                    }
                    
                    //在这里业务代码
                    /*echo "{$key} clinet msg:",$msg,"\n";
                    fwrite(STDOUT, 'Please input a argument:');
                    $response = trim(fgets(STDIN));*/
                    echo "{$key} response to Client:".$response,"\n";
                }
            }
        }
    }
 
    /**
     * 握手处理
     * @param $newClient socket
     * @return int  接收到的信息
     */
    public function handshaking($newClient, $line){
 
        $headers = array();
        $lines = preg_split("/\r\n/", $line);
        foreach($lines as $line)
        {
            $line = chop($line);
            if(preg_match('/\A(\S+): (.*)\z/', $line, $matches))
            {
                $headers[$matches[1]] = $matches[2];
            }
        }
        $secKey = $headers['Sec-WebSocket-Key'];
        $secAccept = base64_encode(pack('H*', sha1($secKey . '258EAFA5-E914-47DA-95CA-C5AB0DC85B11')));
        $upgrade  = "HTTP/1.1 101 Web Socket Protocol Handshake\r\n" .
            "Upgrade: websocket\r\n" .
            "Connection: Upgrade\r\n" .
            "WebSocket-Origin: $this->address\r\n" .
            "WebSocket-Location: wss://$this->address:$this->port/websocket/websocket\r\n".
            "Sec-WebSocket-Accept:$secAccept\r\n\r\n";
        return socket_write($newClient, $upgrade, strlen($upgrade));
    }
 
    /**
     * 解析接收数据
     * @param $buffer
     * @return null|string
     */
    public function message($buffer){
        $len = $masks = $data = $decoded = null;
        $len = ord($buffer[1]) & 127;
        if ($len === 126)  {
            $masks = substr($buffer, 4, 4);
            $data = substr($buffer, 8);
        } else if ($len === 127)  {
            $masks = substr($buffer, 10, 4);
            $data = substr($buffer, 14);
        } else  {
            $masks = substr($buffer, 2, 4);
            $data = substr($buffer, 6);
        }
        for ($index = 0; $index < strlen($data); $index++) {
            $decoded .= $data[$index] ^ $masks[$index % 4];
        }
        return $decoded;
    }
 
    /**
     * 发送数据
     * @param $newClinet 新接入的socket
     * @param $msg   要发送的数据
     * @return int|string
     */
    public function send($newClinet, $msg){
        $msg = $this->frame($msg);
        socket_write($newClinet, $msg, strlen($msg));
    }
 
    public function frame($s) {
        $a = str_split($s, 125);
        if (count($a) == 1) {
            return "\x81" . chr(strlen($a[0])) . $a[0];
        }
        $ns = "";
        foreach ($a as $o) {
            $ns .= "\x81" . chr(strlen($o)) . $o;
        }
        return $ns;
    }
 
    /**
     * 关闭socket
     */
    public function close(){
        return socket_close($this->_sockets);
    }
}
 
$sock = new SocketService();
$sock->run();
?>