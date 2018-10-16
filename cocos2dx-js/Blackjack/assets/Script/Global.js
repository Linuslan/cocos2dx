window.Global = {
    playerId: null,
    socketId: null,
    roomId: null,
    roomNo: null,
    gameNo: null,
    gameLevel: null,
    webSocket: null,    //WebSocket实例
    roundId: null,
    updatePlayer: 0,
    heartBeat: function() { //心跳
        var self = this;
        setInterval(function() {
            console.log("开始发送心跳");
            self.webSocket.send("{\"cmd\":\"heartBeat\"}");
        }, 5000);
    }
}
