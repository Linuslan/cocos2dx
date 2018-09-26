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
        var ws;
        var url = "https://www.uxgoo.com/calculate24/UserAction.php?m=userLogin";
        wx.login({
            timeout: 6000,
            success: function(code) {
                console.log("打印返回的code");
                console.log(code.code);
                var sendUrl = url + "&code="+code.code;
                console.log(sendUrl);
                wx.request({
                    url: sendUrl,
                    success: function(data, statusCode, header) {
                        console.log(data);
                        var response = data.data;
                        console.log("用户登录响应");
                        console.log(response);
                        console.log("用户id："+response.playerId);
                        if(!response.playerId) {
                            wx.showToast({title:"请求服务端异常", icon: "none"});
                        }
                        console.log("给全局赋值");
                        Global.playerId = response.playerId;
                        ws = new WebSocket("wss://www.uxgoo.com:8083");
                        ws.onopen = function (event) {
                            console.log("Send Text WS was opened.");
                            ws.send("{\"cmd\":\"getSocketId\"}");
                        };
                        ws.onmessage = function (event) {
                            var data = event.data;
                            console.log("response text msg: " + event.data);
                            var json = JSON.parse(data);
                            console.log("JSON解析成功");
                            console.log(json);
                            if(json.success == false) {
                                wx.showToast({title:"请求服务端异常", icon: "none"});
                                //alert("请求服务器异常");
                            }
                            if(json.cmd == "getSocketId") {
                                console.log("进入getSocketId处理流程，开始发送更新socketId操作");
                                Global.socketId = json.data.socketId;
                                console.log(Global);
                                ws.send("{\"cmd\":\"updateSocketId\", \"data\":{\"socketId\":\""+Global.socketId+"\", \"playerId\":"+Global.playerId+"}}");
                            }
                            if(json.cmd == "updateSocketId") {
                                console.log("进入updateSocketId处理流程，开始弹出更新成功提示");
                                wx.showToast({title:"联网成功"});
                                //alert("联网成功");
                            }
                            if(json.cmd == "searchRoom") {
                                console.log("进入searchRoom处理流程");
                                var responseData = json.data;
                                console.log("responseData:"+responseData);
                                if(!responseData.roomNo || responseData.gameLevel) {
                                    wx.showToast({title:"查找房间异常", icon: "none"});
                                    //alert("查找房间异常");
                                }
                                var gameLevel = responseData.gameLevel;
                                Global.gameLevel = gameLevel;
                                Global.roomId = responseData.roomId;
                                cc.director.loadScene("Game", function() {
                                    var scene = cc.director.getScene();
                                    var canvas = scene.getChildByName("Canvas");
                                    var gameCmp = canvas.getComponent("Game");
                                    gameCmp.gameLevel = gameLevel;
                                    gameCmp.initGame();
                                });
                            }
                        };
                        ws.onerror = function (event) {
                            console.log("Send Text fired an error");
                        };
                        ws.onclose = function (event) {
                            console.log("WebSocket instance closed.");
                        };
                    }
                });
                // wx.connectSocket({
                //     url: "wss://www.uxgoo.com:8083",
                //     success: function() {
                //         console.log("链接websocket完成");
                //     }
                // });
            }
        });
        // var xhr = new XMLHttpRequest();
        // xhr.onreadystatechange = function () {
        //     if (xhr.readyState == 4 && (xhr.status >= 200 && xhr.status < 400)) {
        //         var response = xhr.responseText;
        //         console.log(response);
        //     }
        // };
        // xhr.open("GET", url, true);
        // xhr.send();

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
                    if(!ws || ws.readyState !== WebSocket.OPEN) {
                        wx.showToast({title:"正在联网中，请稍后"});
                        //alert("正在联网中，请稍后");
                        return ;
                    }
                    ws.send("{\"cmd\":\"searchRoom\", \"data\": {\"gameLevel\": 0}}");
                    console.log("开始执行动作回调");
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
