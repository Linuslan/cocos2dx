cc.Class({
    extends: cc.Component,

    properties: {
        bgAudio: {
            default: null,
            url: cc.AudioClip
        }
    },

    // use this for initialization
    onLoad: function () {
        var url = "https://www.uxgoo.com/calculate24/UserAction.php?m=userLogin";
        // wx.login({
        //     timeout: 6000,
        //     success: function(code) {
        //         console.log("打印返回的code");
        //         console.log(code.code);
        //         var sendUrl = url + "&code="+code.code;
        //         console.log(sendUrl);
        //         // wx.request({
        //         //     url: sendUrl,
        //         //     success: function(data, statusCode, header) {
        //         //         console.log(data);
        //         //     }
        //         // });
        //         wx.connectSocket({
        //             url: "wss://www.uxgoo.com:8083",
        //             success: function() {
        //                 console.log("链接websocket完成");
        //             }
        //         });
        //     }
        // });
        // var xhr = new XMLHttpRequest();
        // xhr.onreadystatechange = function () {
        //     if (xhr.readyState == 4 && (xhr.status >= 200 && xhr.status < 400)) {
        //         var response = xhr.responseText;
        //         console.log(response);
        //     }
        // };
        // xhr.open("GET", url, true);
        // xhr.send();
        var ws = new WebSocket("wss://www.uxgoo.com:8083");
        //var ws = new WebSocket("ws://localhost:8083");
        ws.onopen = function (event) {
            console.log("Send Text WS was opened.");
            ws.send("Hello WebSocket, I'm a text message.");
        };
        ws.onmessage = function (event) {
            console.log("response text msg: " + event.data);
        };
        ws.onerror = function (event) {
            console.log("Send Text fired an error");
        };
        ws.onclose = function (event) {
            console.log("WebSocket instance closed.");
        };

        /*setTimeout(function () {
            if (ws.readyState === WebSocket.OPEN) {
                ws.send("Hello WebSocket, I'm a text message.");
            }
            else {
                console.log("WebSocket instance wasn't ready...");
            }
        }, 20);*/
        
        this.bgAudioId = cc.audioEngine.play(this.bgAudio, true, 1);
        cc.director.preloadScene("Game", function() {
            console.log("预加载游戏场景");
        });
        var quickStartBtn = this.node.getChildByName("quickStartBtn");
        var advanceBtn = this.node.getChildByName("advanceBtn");
        var onlineBtn = this.node.getChildByName("onlineBtn");
        if(quickStartBtn) {
            quickStartBtn.on(cc.Node.EventType.TOUCH_START, function(event) {
                console.log("按下快速开始按钮");
                var btn = event.target;
                btn.runAction(cc.scaleTo(0.1, 0.85));
                cc.loader.loadRes("audio/button", cc.AudioClip, function (err, clip) {
                    var audioID = cc.audioEngine.play(clip, false, 1);
                });
            });
            quickStartBtn.on(cc.Node.EventType.TOUCH_END, function(event) {
                console.log("按下快速开始按钮结束");
                var btn = event.target;
                var action = cc.sequence(cc.scaleTo(0.1, 1), cc.callFunc(function() {
                    console.log("开始执行动作回调");
                    cc.director.loadScene("Game", function() {
                        var scene = cc.director.getScene();
                        var canvas = scene.getChildByName("Canvas");
                        var gameCmp = canvas.getComponent("Game");
                        gameCmp.gameLevel = 0;
                        gameCmp.initGame();
                    });
                }));
                btn.runAction(action);
            });
        }
        if(advanceBtn) {
            advanceBtn.on(cc.Node.EventType.TOUCH_START, function(event) {
                console.log("按下进阶场按钮");
                var btn = event.target;
                btn.runAction(cc.scaleTo(0.1, 0.85));
                cc.loader.loadRes("audio/button", cc.AudioClip, function (err, clip) {
                    var audioID = cc.audioEngine.play(clip, false, 1);
                });
            });
            advanceBtn.on(cc.Node.EventType.TOUCH_END, function(event) {
                console.log("按下快速开始按钮结束");
                var btn = event.target;
                var action = cc.sequence(cc.scaleTo(0.1, 1), cc.callFunc(function() {
                    console.log("开始执行动作回调");
                    cc.director.loadScene("Game", function() {
                        var scene = cc.director.getScene();
                        var canvas = scene.getChildByName("Canvas");
                        var gameCmp = canvas.getComponent("Game");
                        gameCmp.gameLevel = 1;
                        gameCmp.initGame();
                    });
                }));
                btn.runAction(action);
            });
        }
        //点击对战，将数据发送到微信上，获取匹配
        if(onlineBtn) {
            onlineBtn.on(cc.Node.EventType.TOUCH_START, function(event) {
                console.log("进入在线对战");

            });
        }
    },

    onDestroy() {
        cc.audioEngine.stop(this.bgAudioId);
    }

    // called every frame, uncomment this function to activate update callback
    // update: function (dt) {

    // },
});
