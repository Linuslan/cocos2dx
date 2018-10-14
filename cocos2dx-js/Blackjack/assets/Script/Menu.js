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
        console.log("初始化menu");
        /*cc.loader.downloader.loadSubpackage('script_game', function (err) {
            if (err) {
                return console.error(err);
            }
            console.log('load subpackage successfully.');
        });*/
        //每次第一次进入游戏菜单没有更新过，才出现按钮，如果已经更新过，则不再出现按钮
        //省的用户不断的在授权
        let wxQuickStart;
        let wxAdvanceBtn;
        let wxOnlineBtn;
        if(!Global.updatePlayer || Global.updatePlayer == 0) {
            wxQuickStart = wx.createUserInfoButton({
                type: 'text',
                text: '更新',
                style: {
                    left: 450,
                    top: 45,
                    width: 230,
                    height: 85,
                    lineHeight: 0,
                    backgroundColor: '',
                    borderColor: '#000000',
                    borderWidth: '#000000',
                    color: '#ffffff',
                    textAlign: 'center',
                    fontSize: 16,
                    borderRadius: 4
                }
            });
            //console.log(wxQuickStart);
            wxQuickStart.show();
            wxQuickStart.onTap(function(res) {
                console.log("点击了快速开始按钮");
                console.log(res);
                var userInfo = res.userInfo;
                var userName = userInfo.nickName;
                var avatarUrl = userInfo.avatarUrl;
                var ws = Global.webSocket;
                if(!ws || ws.readyState !== WebSocket.OPEN || !Global.playerId || !Global.socketId) {
                    wx.showToast({title:"正在联网中，请稍后"});
                    //alert("正在联网中，请稍后");
                    return ;
                }
                console.log("开始联网请求");
                ws.send("{\"cmd\":\"updatePlayer\", \"data\":{\"playerId\":"+Global.playerId+", \"nickName\":\""+userName+"\", \"avatarUrl\":\""+avatarUrl+"\", \"btn\":\"quickStart\"}}");
            });
    
            wxAdvanceBtn = wx.createUserInfoButton({
                type: 'text',
                text: '更新2',
                style: {
                    left: 450,
                    top: 150,
                    width: 230,
                    height: 85,
                    lineHeight: 0,
                    backgroundColor: '',
                    borderColor: '#000000',
                    borderWidth: '#000000',
                    color: '#ffffff',
                    textAlign: 'center',
                    fontSize: 16,
                    borderRadius: 4
                }
            });
            //console.log(wxAdvanceBtn);
            wxAdvanceBtn.show();
            wxAdvanceBtn.onTap(function(res) {
                console.log("点击了进阶场按钮");
                var userInfo = res.userInfo;
                var userName = userInfo.nickName;
                var avatarUrl = userInfo.avatarUrl;
                var ws = Global.webSocket;
                if(!ws || ws.readyState !== WebSocket.OPEN || !Global.playerId || !Global.socketId) {
                    wx.showToast({title:"正在联网中，请稍后"});
                    //alert("正在联网中，请稍后");
                    return ;
                }
                ws.send("{\"cmd\":\"updatePlayer\", \"data\":{\"playerId\":"+Global.playerId+", \"nickName\":\""+userName+"\", \"avatarUrl\":\""+avatarUrl+"\", \"btn\":\"advanceBtn\"}}");
            });
    
            wxOnlineBtn = wx.createUserInfoButton({
                type: 'text',
                text: '更新3',
                style: {
                    left: 450,
                    top: 265,
                    width: 230,
                    height: 85,
                    lineHeight: 0,
                    backgroundColor: '',
                    borderColor: '#000000',
                    borderWidth: '#000000',
                    color: '#ffffff',
                    textAlign: 'center',
                    fontSize: 16,
                    borderRadius: 4
                }
            });
            //console.log(wxOnlineBtn);
            wxOnlineBtn.show();
            wxOnlineBtn.onTap(function(res) {
                console.log("点击了联网按钮");
                var userInfo = res.userInfo;
                var userName = userInfo.nickName;
                var avatarUrl = userInfo.avatarUrl;
                var ws = Global.webSocket;
                if(!ws || ws.readyState !== WebSocket.OPEN || !Global.playerId || !Global.socketId) {
                    wx.showToast({title:"正在联网中，请稍后"});
                    //alert("正在联网中，请稍后");
                    return ;
                }
                ws.send("{\"cmd\":\"updatePlayer\", \"data\":{\"playerId\":"+Global.playerId+", \"nickName\":\""+userName+"\", \"avatarUrl\":\""+avatarUrl+"\", \"btn\":\"advanceBtn\"}}");
            });
        }

        var ws;
        var url = "https://www.uxgoo.com/calculate24/UserAction.php?m=userLogin";
        var self = this;
        //this.showDialog();
        wx.login({
            timeout: 6000,
            success: function(code) {
                console.log("打印返回的code");
                console.log(code.code);
                //var sendUrl = url + "&code="+code.code;
                //console.log(sendUrl);
                //Global.playerId = response.playerId;
                ws = new WebSocket("wss://www.uxgoo.com");
                Global.webSocket = ws;
                Global.heartBeat(); //启动心跳
                ws.onopen = function (event) {
                    console.log("Send Text WS was opened.");
                    ws.send("{\"cmd\":\"userLogin\", \"data\":{\"code\":\""+code.code+"\"}}");
                    console.log("发送登陆请求成功");
                    //ws.send("{\"cmd\":\"getSocketId\"}");
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
                        return;
                    }
                    if(json.cmd == "userLogin") {
                        console.log("用户登陆返回响应成功");
                        Global.playerId = json.data.playerId;
                        ws.send("{\"cmd\":\"getSocketId\"}");
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
                        if(!responseData.roomNo || responseData.gameLevel === null || responseData.gameLevel < 0) {
                            wx.showToast({title:"查找房间异常", icon: "none"});
                            //alert("查找房间异常");
                            return;
                        }
                        var gameLevel = responseData.gameLevel;
                        Global.gameLevel = gameLevel;
                        Global.roomNo = responseData.roomNo;
                        Global.roomId = responseData.roomId;
                        cc.director.loadScene("Game", function() {
                            var scene = cc.director.getScene();
                            var canvas = scene.getChildByName("Canvas");
                            var gameCmp = canvas.getComponent("Game");
                            gameCmp.gameLevel = gameLevel;
                            gameCmp.initGame();
                            ws.send("{\"cmd\":\"enterRoom\", \"data\":{\"socketId\":\""+Global.socketId+"\", \"roomNo\":\""+Global.roomNo+"\", \"roomId\":"+Global.roomId+", \"playerId\":"+Global.playerId+"}}");
                        });
                    }
                    if(json.cmd == "updatePlayer") {
                        var btn = json.data.btn;
                        Global.updatePlayer = 1;
                        if(wxQuickStart) {
                            wxQuickStart.destroy();
                        }
                        if(wxAdvanceBtn) {
                            wxAdvanceBtn.destroy();
                        }
                        if(wxOnlineBtn) {
                            wxOnlineBtn.destroy();
                        }
                        console.log("用户信息更新成功，用户点击的按钮为："+btn);
                        if(btn == "quickStart") {
                            //ws.send("{\"cmd\":\"searchRoom\", \"data\": {\"gameLevel\": 0}}");
                        } else if(btn == "advanceBtn") {
                            //ws.send("{\"cmd\":\"searchRoom\", \"data\": {\"gameLevel\": 1}}");
                        } else if(btn == "onlienBtn") {
                            //wx.showToast({title:"功能正在开发中，请耐心等待", icon: "none"});
                        }
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
                    if(Global.updatePlayer == 1) {
                        ws.send("{\"cmd\":\"searchRoom\", \"data\": {\"gameLevel\": 0}}");
                        console.log("开始执行动作回调");
                    }
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
                    /*cc.director.loadScene("Game", function() {
                        var scene = cc.director.getScene();
                        var canvas = scene.getChildByName("Canvas");
                        var gameCmp = canvas.getComponent("Game");
                        gameCmp.gameLevel = 1;
                        gameCmp.initGame();
                    });*/
                    if(!ws || ws.readyState !== WebSocket.OPEN) {
                        wx.showToast({title:"正在联网中，请稍后"});
                        //alert("正在联网中，请稍后");
                        return ;
                    }
                    if(Global.updatePlayer == 1) {
                        ws.send("{\"cmd\":\"searchRoom\", \"data\": {\"gameLevel\": 1}}");
                        console.log("开始执行动作回调");
                    }
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
    },
    showDialog() {
        
    }

    // called every frame, uncomment this function to activate update callback
    // update: function (dt) {

    // },
});
