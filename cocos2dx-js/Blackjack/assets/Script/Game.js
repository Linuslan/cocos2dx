cc.Class({
    extends: cc.Component,

    properties: {
        bgAudio: {
            default: null,
            url: cc.AudioClip
        },
        gameLevel: {
            default: 0,
            type: cc.Integer
        },
        pokerValue: {
            default:[],
            type: [cc.Integer]
        },
        pokerType: {
            default:[],
            type: [cc.String]
        },
        pokers: {
            default: [],
            type: [cc.Object]
        },
        firstBtn: {
            default: null,
            type: cc.Node
        },
        secondBtn: {
            default: null,
            type: cc.Node
        },
        thirdBtn: {
            default: null,
            type: cc.Node
        },
        resultInfo: {
            default: null,
            type: cc.Label
        },
        pokerInfo: {
            default: null,
            type: cc.Label
        },
        selectedVal: {
            default: [],
            type: [cc.Integer]
        },
        expreArr: {
            default: [],
            type: [cc.Integer]
        },
        calArr: {
            default: [],
            type: [cc.Integer]
        },
        expreInfoArr: {
            default: [],
            type: [cc.String]
        },
        result: {
            default: 0,
            type: cc.Integer
        },
        lastPokerValues: {
            default: [],
            type: [cc.Integer]
        },
        lastPokerLbl: {
            default: null,
            type: cc.Label
        },
        lastExpression: {
            default: null,
            type: cc.Label
        }
    },

    // LIFE-CYCLE CALLBACKS:

    onLoad () {
        /*cc.loader.downloader.loadSubpackage('script_model', function (err) {
            if (err) {
                return console.error(err);
            }
            console.log('load subpackage successfully.');
        });*/
        console.log(Global);
        var readyBtn = this.node.getChildByName("buttons").getChildByName("ready");
        var giveupBtn = this.node.getChildByName("buttons").getChildByName("giveup");
        var clockNode = this.node.getChildByName("clock");
        var calClockNode = this.node.getChildByName("cal_clock");
        
        clockNode.active = false;
        calClockNode.active = false;
        
        //giveupBtn.active = false;
        var ws = Global.webSocket;
        /*ws.onopen = function (event) {
            console.log("Send Text WS was opened.");
        };*/
        var self = this;
        ws.onmessage = function (event) {
            var data = event.data;
            //console.log(self);
            console.log("response text msg: " + event.data);
            var json = JSON.parse(data);
            //console.log("JSON解析成功");
            //console.log(json);
            if(json.success == false) {
                wx.showToast({title:json.msg, icon: "none"});
                return;
            }
            var cmd = json.cmd;
            var data = json.data;
            //玩家准备，同时需要更新房间内其他玩家的界面，将准备的玩家的状态改为已准备，同时分数清空
            //同时，如果准备好的玩家是当前玩家本人，则将玩家的界面上的牌清空
            if(cmd == "playerReady") {
                readyBtn.active = false;
                if(data.playerId == Global.playerId) {
                    self.resetPoker();
                    self.resetCalUI();
                    var playerInfoLbl = self.node.getChildByName("player_info").getComponent(cc.Label);
                    playerInfoLbl.string = "分数：0";
                } else {
                    console.log("playerId:"+data.playerId);
                    var player = self.getPlayerByPlayerId(data.playerId);
                    //更新分数
                    player.getChildByName("score").getComponent(cc.Label).string = 0;
                    //更新状态
                    player.getChildByName("status").getComponent(cc.Label).string = "已准备";
                }
                //如果开始倒计时，说明所有玩家都已经准备完成，倒计时结束后开始初始化游戏，初始化游戏完成后开始第一次发牌
                if(data.isCountDown == true) {
                    var second = data.second;
                    var cards = JSON.parse(data.cards);
                    var pokerCount = data.pokerCount;
                    //console.log(cards);
                    var gameNo = data.gameNo;
                    Global.gameNo = gameNo;
                    var roundId = data.roundId;
                    Global.roundId = roundId;
                    self.clockCountDown(cards, second, pokerCount);
                }

            } else if(cmd == "commit") {
                //首先更新已经完成的玩家的信息
                //如果是自己完成，则更新分数，将放弃按钮改为不可用，如果是其他玩家完成，则更新其他玩家的状态以及分数
                //更新完成后，判断是否所有玩家都已经结束，如果是，则开始一个新的回合
                var playerId = data.playerId;
                var score = data.score;
                //玩家回合状态，0：解题中；1：完成；2：放弃；3：超时
                var status = data.status;
                var restart = data.restart;
                var statusStr = "";
                if(status == 0) {
                    statusStr = "解题中"
                } else if(status == 1) {
                    statusStr = "已完成";
                } else if(status == 2) {
                    statusStr = "已放弃";
                } else if(status == 3) {
                    statusStr = "已超时";
                }
                console.log("开始判断是否为玩家本人或者其他玩家, playerId="+playerId);
                //如果是玩家自己，则更新分数
                if(playerId == Global.playerId) {
                    console.log("玩家本人");
                    var playerInfoLbl = self.node.getChildByName("player_info").getComponent(cc.Label);
                    playerInfoLbl.string = "分数："+score;
                    console.log("更新玩家信息完成");
                } else {
                    console.log("其他玩家");
                    var player = self.getPlayerByPlayerId(playerId);
                    console.log("获取到的玩家为");
                    console.log(player);
                    //更新分数
                    player.getChildByName("score").getComponent(cc.Label).string = score;
                    //更新状态
                    player.getChildByName("status").getComponent(cc.Label).string = statusStr;
                    console.log("更新完成");
                }
                //重新开始，将放弃按钮隐藏，将准备按钮显示为可见，同时刷新界面
                if(restart) {
                    wx.showToast({title:"没牌啦，请重新开始", icon: "none"});
                    readyBtn.active = true;
                    giveupBtn.active = false;
                    self.resetPoker();
                    self.resetCalUI();
                    return;
                }
                var newRound = data.newRound;
                if(newRound == true) {
                    var cards = JSON.parse(data.cards);
                    console.log("新一回合的牌为");
                    console.log(cards);
                    var pokerCount = data.pokerCount;
                    Global.roundId = data.roundId;
                    console.log("剩余牌数为："+pokerCount+", 新一回合id为："+data.roundId+", 开始倒计时");
                    //开始倒计时，进行新一回合
                    self.clockCountDown(cards, 3, pokerCount);
                }
            } else if(cmd == "enterRoom") {
                wx.showToast({title:"进入房间成功"});
                var players = data.players;
                console.log("本房间共有玩家");
                console.log(players);
                for(var i = 0; i < players.length; i ++) {
                    var player = players[i];
                    var id = player.id;
                    var avatarUrl = player.avatarUrl;
                    var userName = player.userName;
                    if(id == Global.playerId) {
                        continue;
                    }
                    console.log("非本玩家，更新玩家头像");
                    var playerNode = self.getEmptyPlayerCmp();
                    var player = playerNode.getComponent("Player");
                    player.playerId = id;
                    console.log(playerNode);
                    console.log("playerId="+player.playerId);
                    var avatarNode = playerNode.getChildByName("avatar").getChildByName("image");
                    var avatarCmp = avatarNode.getComponent(cc.Sprite);
                    cc.loader.load({url:avatarUrl, type:"jpg"}, function (err, texture) {
                        var spriteFrame  = new cc.SpriteFrame(texture);
                        avatarCmp.spriteFrame = spriteFrame;
                    });
                    var userNameNode = playerNode.getChildByName("name");
                    var userNameCmp = userNameNode.getComponent(cc.Label);
                    userNameCmp.string = userName;
                    var scoreNode = playerNode.getChildByName("score");
                    var scoreCmp = scoreNode.getComponent(cc.Label);
                    scoreCmp.string = 0;
                    var statusNode = playerNode.getChildByName("status");
                    var statusCmp = statusNode.getComponent(cc.Label);
                    statusCmp.string = "未准备";
                }
            } else if(cmd == "quitRoom") {
                var playerId = data.playerId;
                if(playerId != Global.playerId) {
                    var playerNode = self.getPlayerByPlayerId(playerId);
                    var player = playerNode.getComponent("Player");
                    player.playerId = null;
                    var avatarNode = playerNode.getChildByName("avatar").getChildByName("image");
                    var avatarCmp = avatarNode.getComponent(cc.Sprite);
                    cc.loader.load({url:"", type:"jpg"}, function (err, texture) {
                        var spriteFrame  = new cc.SpriteFrame(texture);
                        avatarCmp.spriteFrame = spriteFrame;
                    });
                    var userNameNode = playerNode.getChildByName("name");
                    var userNameCmp = userNameNode.getComponent(cc.Label);
                    userNameCmp.string = "";
                    var scoreNode = playerNode.getChildByName("score");
                    var scoreCmp = scoreNode.getComponent(cc.Label);
                    scoreCmp.string = "";
                    var statusNode = playerNode.getChildByName("status");
                    var statusCmp = statusNode.getComponent(cc.Label);
                    statusCmp.string = "";
                }
                cc.director.loadScene("Menu");
                
            }
        };
        ws.onerror = function (event) {
            console.log("Send Text fired an error");
        };
        ws.onclose = function (event) {
            console.log("WebSocket instance closed.");
        };
        cc.director.preloadScene("Menu", function() {
            console.log("预加载游戏场景");
        });
        this.current = cc.audioEngine.play(this.bgAudio, true, 1);
        this.resultInfo.string = "";
        this.pokerType = ["clubs", "diamonds", "hearts", "spades"];
        //var restartBtn = this.node.getChildByName("buttons").getChildByName("restart_btn");
        var backBtn = this.node.getChildByName("buttons").getChildByName("back_btn");
        readyBtn.on(cc.Node.EventType.TOUCH_START, function(event) {
            this.expreInfoArr = [];
            var btn = event.target;
            btn.runAction(cc.sequence(cc.scaleTo(0.1, 0.85, 0.85), cc.scaleTo(0.1, 1, 1), cc.callFunc(function() {
                //this.refreshPoker();
            }, this)));
            cc.loader.loadRes("audio/button", cc.AudioClip, function (err, clip) {
                var audioID = cc.audioEngine.play(clip, false, 1);
            });
            var firstPoker = this.node.getChildByName("first_porker");
            var secondPoker = this.node.getChildByName("second_porker");
            var thirdPoker = this.node.getChildByName("third_porker");
            var forthPoker = this.node.getChildByName("forth_porker");
            
            
        }, this);

        readyBtn.on(cc.Node.EventType.TOUCH_END, function(event){
            //发送到服务端玩家准备完成
            ws.send("{\"cmd\":\"playerReady\", \"data\": {\"roomNo\":\""+Global.roomNo+"\", \"playerId\":"+Global.playerId+", \"gameLevel\":"+this.gameLevel+", \"socketId\":\""+Global.socketId+"\"}}");
            giveupBtn.active = true;
            readyBtn.active = false;
            //玩家准备完成，清空提示框
            this.clearTips();
            //清空分数
        }, this);

        //放弃本回合，则发送放弃的状态到服务端，服务端响应成功后，再计算本局是否能够解出来
        //同时将放弃按钮改为不可用状态
        giveupBtn.on(cc.Node.EventType.TOUCH_END, function(event){
            //readyBtn.active = true;
            //giveupBtn.active = false;
            ws.send("{\"cmd\":\"commit\", \"data\":{\"playerId\":"+Global.playerId+", \"socketId\":\""+Global.socketId+"\",\"roomNo\":\""+Global.roomNo+"\", \"roomId\":"+Global.roomId+", \"gameNo\":"+Global.gameNo+", \"roundId\":"+Global.roundId+", \"status\": 2}}");
            //计算可能的解
            this.showTips();
            this.calClockUnschedule();
        }, this);

        //点击退出按钮，则向服务端发送退出房间指令
        backBtn.on(cc.Node.EventType.TOUCH_START, function(event) {
            ws.send("{\"cmd\":\"quitRoom\", \"data\":{\"playerId\":"+Global.playerId+", \"roomNo\":\""+Global.roomNo+"\", \"gameNo\":\""+Global.gameNo+"\", \"roundId\":\""+Global.roundId+"\"}}");
            var btn = event.target;
            cc.loader.loadRes("audio/button", cc.AudioClip, function (err, clip) {
                var audioID = cc.audioEngine.play(clip, false, 1);
            });
            btn.runAction(cc.sequence(cc.scaleTo(0.1, 0.85, 0.85), cc.scaleTo(0.1, 1, 1), cc.callFunc(function() {
                
            }, this)));
        }, this);
    },

    initGame() {
        this.clearTips();
        // if(this.gameLevel == 0) {
        //     this.pokerValue = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
        // } else if(this.gameLevel == 1) {
        //     this.pokerValue = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13];
        // } else if(this.gameLevel == 2) {    //简单的在线对战
        //     //出现准备按钮
        // }
        this.pokers = [];        
        // for(var j = 0; j < this.pokerType.length; j ++) {
        //     for(var i = 0; i < this.pokerValue.length; i ++) {
        //         var key = this.pokerValue[i]+"-"+this.pokerType[j];
        //         var value = this.pokerValue[i];
        //         var poker = new Object();
        //         poker["key"] = key;
        //         poker["value"] = value;
        //         this.pokers.push(poker);
        //     }
        // }
    },

    start () {
        
    },

    onDestroy() {
        cc.audioEngine.stop(this.current);
    },
    clockCountDown(cards, second, pokerCount) {
        this.calClockUnschedule();
        console.log("进入倒计时，时间为："+second);
        var clockNode = this.node.getChildByName("clock");
        var calClockNode = this.node.getChildByName("cal_clock");
        calClockNode.active = false;
        var clock = clockNode.getComponent(cc.Label);
        var count = 0;
        var self = this;
        this.pokers = [];
        console.log("开始倒计时");
        this.showInfo("即将开始新回合");
        clock.schedule(function() {
            //获取时钟对象，修改里面的数字
            var time = second-count;
            console.log("倒计时数字："+time);
            clock.string = time;
            clockNode.active = true;
            if(time <= 0) {   //倒计时完成，开始发牌
                console.log("倒计时完成，开始发牌");
                clockNode.active = false;
                for(var key in cards) {
                    var value = cards[key];
                    var poker = new cc.Object();
                    poker.key = key;
                    poker.value = value;
                    self.pokers.push(poker);

                }
                console.log("得到的牌：");
                console.log(self.pokers);
                self.refreshPoker();
                self.showPokerInfo(pokerCount);
            }
            count ++;
        }, 1, second, 0);
    },
    clockUnschedule() {
        var clockNode = this.node.getChildByName("clock");
        var clock = clockNode.getComponent(cc.Label);
        clock.unscheduleAllCallbacks(clock);
    },
    calClockCountDown() {
        this.clockUnschedule();
        var clock1 = this.node.getChildByName("clock");
        clock1.active = false;
        var clockNode = this.node.getChildByName("cal_clock");
        var clock = clockNode.getComponent(cc.Label);
        var count = 0;
        var second = 60;
        console.log("发完牌，开始进入计算时间倒计时");
        var self = this;
        //开始倒计时，一局的限定时间为60秒
        clock.schedule(function() {
            //获取时钟对象，修改里面的数字
            var time = second-count;
            console.log("倒计时数字："+time);
            clock.string = time;
            clockNode.active = true;
            if(time <= 0) {   //倒计时完成，开始发牌
                console.log("倒计时完成，玩家没有完成计算");
                clockNode.active = false;
                var ws = Global.webSocket;
                ws.send("{\"\cmd\":\"commit\", \"data\":{\"playerId\":"+Global.playerId+", \"socketId\":\""+Global.socketId+"\",\"roomNo\":\""+Global.roomNo+"\", \"roomId\":"+Global.roomId+", \"gameNo\":"+Global.gameNo+", \"roundId\":"+Global.roundId+", \"status\": 3}}");
                self.showTips();
            }
            count ++;
        }, 1, second, 0);
    },
    calClockUnschedule() {
        console.log("计算倒计时停止");
        var clockNode = this.node.getChildByName("cal_clock");
        var clock = clockNode.getComponent(cc.Label);
        clock.unscheduleAllCallbacks(clock);
        console.log("计算倒计时停止结束");
    },
    refreshPoker() {
        this.resetCalUI();
        var cardDealAudioID = null;
        cc.loader.loadRes("audio/card_deal", cc.AudioClip, function (err, clip) {
            cardDealAudioID = cc.audioEngine.play(clip, false, 1);
        });
        var firstPoker = this.node.getChildByName("first_porker");
        var secondPoker = this.node.getChildByName("second_porker");
        var thirdPoker = this.node.getChildByName("third_porker");
        var forthPoker = this.node.getChildByName("forth_porker");
        
        var firstVal = 0;
        var secondVal = 0;
        var thirdVal = 0;
        var forthVal = 0;
        //var poker = this.getPoker();
        var poker = this.pokers[0];
        if(poker) {
            cc.loader.loadRes("game/"+poker["key"], cc.SpriteFrame, function (err, spriteFrame) {
                firstPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            });
            var pokerCmp = firstPoker.getComponent("Porker");
            pokerCmp.value=poker["value"];
            pokerCmp.key = poker["key"];
            firstVal = poker["value"];
        }
        
        //poker = this.getPoker();
        poker = this.pokers[1];
        if(poker) {
            cc.loader.loadRes("game/"+poker["key"], cc.SpriteFrame, function (err, spriteFrame) {
                secondPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            });
            var pokerCmp = secondPoker.getComponent("Porker");
            pokerCmp.value=poker["value"];
            pokerCmp.key = poker["key"];
            secondVal = poker["value"];
        }
        
        //poker = this.getPoker();
        poker = this.pokers[2];
        if(poker) {
            cc.loader.loadRes("game/"+poker["key"], cc.SpriteFrame, function (err, spriteFrame) {
                thirdPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            });
            var pokerCmp = thirdPoker.getComponent("Porker");
            pokerCmp.value=poker["value"];
            pokerCmp.key = poker["key"];
            thirdVal = poker["value"];
        }
        //poker = this.getPoker();
        poker = this.pokers[3];
        if(poker) {
            cc.loader.loadRes("game/"+poker["key"], cc.SpriteFrame, function (err, spriteFrame) {
                forthPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            });
            var pokerCmp = forthPoker.getComponent("Porker");
            pokerCmp.value=poker["value"];
            pokerCmp.key = poker["key"];
            forthVal = poker["value"];
        }
        this.calClockCountDown();
    },
    resetPoker() {
        var firstPoker = this.node.getChildByName("first_porker");
        var secondPoker = this.node.getChildByName("second_porker");
        var thirdPoker = this.node.getChildByName("third_porker");
        var forthPoker = this.node.getChildByName("forth_porker");

        cc.loader.loadRes("game/poker_bg", cc.SpriteFrame, function (err, spriteFrame) {
            firstPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            firstPoker.getComponent("Porker").key = "";
            firstPoker.getComponent("Porker").value = 0;
            secondPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            secondPoker.getComponent("Porker").key = "";
            secondPoker.getComponent("Porker").value = 0;
            thirdPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            thirdPoker.getComponent("Porker").key = "";
            thirdPoker.getComponent("Porker").value = 0;
            forthPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            forthPoker.getComponent("Porker").key = "";
            forthPoker.getComponent("Porker").value = 0;
        });
    },
    //重置计算区域的UI
    resetCalUI() {

        /**/

        var calculate_buttons = this.node.getChildByName("calculate_button").children;
        for(var i = 0; i < calculate_buttons.length; i ++) {
            var buttonContainer = calculate_buttons[i];
            var buttons = buttonContainer.children;
            for(var j = 0; j < buttons.length; j ++) {
                var button = buttons[j];
                button.runAction(cc.scaleTo(0.1, 1, 1));
            }
        }
        this.firstBtn = null;
        this.secondBtn = null;
        this.thirdBtn = null;
        this.forthBtn = null;
        var calFirstPoker = this.node.getChildByName("cal_first_porker");
        var calSecondPoker = this.node.getChildByName("cal_second_porker");
        var calThirdPoker = this.node.getChildByName("cal_third_porker");
        var calForthPoker = this.node.getChildByName("cal_forth_porker");
        cc.loader.loadRes("game/poker_bg", cc.SpriteFrame, function(err, spriteFrame) {
            calFirstPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            calFirstPoker.getComponent("Porker").key = "";
            calFirstPoker.getComponent("Porker").value = 0;
            calSecondPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            calSecondPoker.getComponent("Porker").key = "";
            calSecondPoker.getComponent("Porker").value = 0;
            calThirdPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            calThirdPoker.getComponent("Porker").key = "";
            calThirdPoker.getComponent("Porker").value = 0;
            calForthPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            calForthPoker.getComponent("Porker").key = "";
            calForthPoker.getComponent("Porker").value = 0;
        });
    },
    getPoker() {
        if(this.pokers.length <= 0) {
            this.clearTips();
            this.resetCalUI();
            this.resetPoker();
            var playerInfoLbl = this.node.getChildByName("player_info").getComponent(cc.Label);
            playerInfoLbl.string = "分数：0";
            this.showInfo("没牌啦，请重新开始");
        }
        var pokerList = [];
        for(var i = 0; i < this.pokers.length; i ++) {
            if(this.pokers[i] && this.pokers[i]["key"] && this.pokers[i]["value"]) {
                pokerList.push(this.pokers[i]);
            }
        }
        this.pokers = pokerList;
        if(this.pokers.length <= 0) {
            return;
        }
        var idx = Math.floor(Math.random()*(this.pokers.length-1-0+1)+0);
        //console.log("选中索引："+idx);
        //console.log(this.pokers);
        var poker = this.pokers[idx];
        this.pokers.splice(idx, 1);
        this.showPokerInfo();
        return poker;
    },
    //机器人计算可能的公式
    recursiveCal(arr) {
        for(var i = 0; i < arr.length; i ++) {
            var val = arr[i];
            this.calArr.push(val);
            var arr2 = this.rebuildArr(i, arr);
            if(arr2.length <= 0) {
                this.result = this.calculateVal(this.calArr);
                this.expreArr = [];
            } else {
                this.result = this.recursiveCal(arr2);
            }
            this.calArr.pop();
            if(this.result == 24) {
                return this.result;
            }
        }
    },
    rebuildArr(j, arr) {
        var temp = [];
        for(var i = 0; i < arr.length; i ++) {
            if(i == j) {
                continue;
            }
            temp.push(arr[i]);
        }
        return temp;
    },
    calculateVal(arr) {
        var result = 0;
        for(var i = 0; i < arr.length; i ++) {
            var val = arr[i];
            this.expreArr.push(val);
            var arr2 = this.rebuildArr(i, arr);
            if(arr2.length <= 0) {
                result = this.executeExpre(this.expreArr);
                this.expreArr.pop();
                this.expreArr.pop();
                return result;
            }
            for(var j = 1; j <= 4; j ++) {
                this.expreArr.push(j);
                result = this.calculateVal(arr2);
                if(result == 24) {
                    return result;
                }
                if(arr2.length <= 0) {
                    result = this.executeExpre(this.expreArr);
                    this.expreArr.pop();
                    this.expreArr.pop();
                    return result;
                }
            }
            this.expreArr.pop();
            this.expreArr.pop();
            return 0;
        }
    },
    executeExpre(expreArr) {
        var val = expreArr[0];
        var expre = expreArr[1];
        var val2 = expreArr[2];
        var expre2 = expreArr[3];
        var val3 = expreArr[4];
        var expre3 = expreArr[5];
        var val4 = expreArr[6];
        var expreTemp = [];
        //第一种组合方式：按顺序组合
        var result1 = this.getResult(val, val2, expre, expreTemp);
        var result2 = this.getResult(result1, val3, expre2, expreTemp);
        var result = this.getResult(result2, val4, expre3, expreTemp);
        console.log("第一种组合方式计算结果为：");
        console.log(expreTemp);
        if(Number.isInteger(result1) && Number.isInteger(result2) && result == 24) {
            console.log(expreTemp);
            this.expreInfoArr = expreTemp;
            return result;
        }
        expreTemp = [];
        //第二种组合方式：第一个数和第二个数组合，第三个数和第四个数组合
        var result1 = this.getResult(val, val2, expre, expreTemp);
        var result2 = this.getResult(val3, val4, expre3, expreTemp);
        result = this.getResult(result1, result2, expre2, expreTemp);
        console.log("第二种组合方式计算结果为：");
        console.log(expreTemp);
        if(Number.isInteger(result1) && Number.isInteger(result2) && result == 24) {
            console.log(expreTemp);
            this.expreInfoArr = expreTemp;
            return result;
        }
        expreTemp = [];
        //第三种组合方式：第二个数和第三个数组合，再和第一个数组合，再和第四个数组合
        var result1 = this.getResult(val2, val3, expre2, expreTemp);
        var result2 = this.getResult(val, result1, expre, expreTemp);
        result = this.getResult(result2, val4, expre3, expreTemp);
        console.log("第三种组合方式计算结果为：");
        console.log(expreTemp);
        if(Number.isInteger(result1) && Number.isInteger(result2) && result == 24) {
            console.log(expreTemp);
            this.expreInfoArr = expreTemp;
            return result;
        }
        expreTemp = [];
        //第四种组合方式：第二个数和第三个数组合，再和第四个数组合，再和第一个数组合
        var result1 = this.getResult(val2, val3, expre2, expreTemp);
        var result2 = this.getResult(result1, val4, expre3, expreTemp);
        result = this.getResult(val, result2, expre, expreTemp);
        console.log("第四种组合方式计算结果为：");
        console.log(expreTemp);
        if(Number.isInteger(result1) && Number.isInteger(result2) && result == 24) {
            console.log(expreTemp);
            this.expreInfoArr = expreTemp;
            return result;
        }
        expreTemp = [];
        //第五种组合方式：第三个数和第四个数组合，再和第二个数组合，再和第一个数组合
        var result1 = this.getResult(val3, val4, expre3, expreTemp);
        var result2 = this.getResult(val2, result1, expre2, expreTemp);
        result = this.getResult(val, result2, expre, expreTemp);
        console.log("第五种组合方式计算结果为：");
        console.log(expreTemp);
        if(Number.isInteger(result1) && Number.isInteger(result2) && result == 24) {
            console.log(expreTemp);
            this.expreInfoArr = expreTemp;
        }
        this.expreTemp = [];
        return result;
    },
    getResult(val, val2, expre, expreArr) {
        var result = 0;
        if(Number.isInteger(val)) {
            val = parseInt(val);
        } else {
            val = parseFloat(val);
        }
        if(Number.isInteger(val2)) {
            val2 = parseInt(val2);
        } else {
            val2 = parseFloat(val2);
        }
        switch(expre) {
            case 1: result = val + val2; expreArr.push(val+"+"+val2+"="+result); break;
            case 2: result = val - val2; expreArr.push(val+"-"+val2+"="+result); break;
            case 3: result = val * val2; expreArr.push(val+"*"+val2+"="+result); break;
            case 4: result = val2 && val2 > 0 ? (val / val2) : 0; expreArr.push(val+"/"+val2+"="+result); break;
        }
        return result;
    },
    calculate() {
        //console.log("进入结果计算");
        var calFirstPoker = this.node.getChildByName("cal_first_porker");
        var calSecondPoker = this.node.getChildByName("cal_second_porker");
        var calThirdPoker = this.node.getChildByName("cal_third_porker");
        var calForthPoker = this.node.getChildByName("cal_forth_porker");
        var firstVal = calFirstPoker.getComponent("Porker").value;
        var secondVal = calSecondPoker.getComponent("Porker").value;
        var thirdVal = calThirdPoker.getComponent("Porker").value;
        var forthVal = calForthPoker.getComponent("Porker").value;
        firstVal = firstVal ? firstVal : 0;
        secondVal = secondVal ? secondVal : 0;
        thirdVal = thirdVal ? thirdVal : 0;
        forthVal = forthVal ? forthVal : 0;
        if(this.firstBtn && this.secondBtn && this.thirdBtn && firstVal > 0 && secondVal > 0 && thirdVal > 0 && forthVal > 0) {
            //console.log("开始计算结果");
            var firstSymbol = this.firstBtn.getComponent("CalculateBtn").symbol;
            var secondSymbol = this.secondBtn.getComponent("CalculateBtn").symbol;
            var thirdSymbol = this.thirdBtn.getComponent("CalculateBtn").symbol;
            var expreArr = [firstVal, firstSymbol, secondVal, secondSymbol, thirdVal, thirdSymbol, forthVal];
            console.log(expreArr);
            var result = this.executeExpre(expreArr);
            console.log("计算结果为："+result);
            if(result == 24) {
                this.showInfo("过关");
                this.clearTips();
                var ws = Global.webSocket;
                ws.send("{\"cmd\":\"commit\", \"data\":{\"playerId\":"+Global.playerId+", \"socketId\":\""+Global.socketId+"\",\"roomNo\":\""+Global.roomNo+"\", \"roomId\":"+Global.roomId+", \"gameNo\":"+Global.gameNo+", \"roundId\":"+Global.roundId+", \"status\": 1}}");
                //var clockNode = this.node.getChildByName("clock");
                //var clock = clockNode.getComponent(cc.Label);
                //clock.unschedule();
                console.log("停止计算倒计时");
                this.calClockUnschedule();
                return ;
            }
        }
    },
    calculateResult(firstVal, secondVal, symbol) {
        var result = 0;
        switch(symbol) {
            case 1: result = firstVal + secondVal; break;
            case 2: result = firstVal - secondVal; break;
            case 3: result = firstVal * secondVal; break;
            case 4: result = firstVal / secondVal; break;
        }
        return result;
    },
    showInfo(msg) {
        //console.log("通知信息为："+msg);
        this.resultInfo.string = msg;
        this.resultInfo.scheduleOnce(function() {
            // 这里的 this 指向 component
            this.string = "";
        }, 2);
    },
    showPokerInfo(pokerCount) {
        var len = this.pokers.length;
        if(pokerCount) {
            len = pokerCount;
        }
        this.pokerInfo.string = "剩余牌数："+len;
    },
    showTips() {
        this.clearTips();
        var firstPoker = this.node.getChildByName("first_porker");
        var secondPoker = this.node.getChildByName("second_porker");
        var thirdPoker = this.node.getChildByName("third_porker");
        var forthPoker = this.node.getChildByName("forth_porker");
        var lastFirstVal = firstPoker.getComponent("Porker").value;
        var lastSecondVal = secondPoker.getComponent("Porker").value;
        var lastThirdVal = thirdPoker.getComponent("Porker").value;
        var lastForthVal = forthPoker.getComponent("Porker").value;
        if(!lastFirstVal || lastFirstVal <= 0 || !lastSecondVal || lastSecondVal <= 0 || !lastThirdVal || lastThirdVal <=0 || !lastForthVal || lastForthVal <= 0) {
            return ;
        }
        this.lastPokerValues = [lastFirstVal, lastSecondVal, lastThirdVal, lastForthVal];
        var lastPokers = lastFirstVal+", "+lastSecondVal+", "+lastThirdVal+", "+lastForthVal;
        this.lastPokerLbl.string = lastPokers;
        console.log(this.expreInfoArr);
        this.recursiveCal(this.lastPokerValues);
        var tips = "无解";
        console.log(this.expreInfoArr);
        if(this.expreInfoArr.length > 0) {
            tips = "";
            for(var i = 0; i < this.expreInfoArr.length; i ++) {
                tips = tips + this.expreInfoArr[i]+"\n\n";
            }
        }
        console.log("解题思路为："+tips);
        this.lastExpression.string = tips;
    },
    clearTips() {
        this.expreInfoArr=[];
        this.lastExpression.string = "";
        this.lastPokerLbl.string = "";
    },
    getPlayerByPlayerId(playerId) {
        var firstPlayer = this.node.getChildByName("first_player");
        var secondPlayer = this.node.getChildByName("second_player");
        var thirdPlayer = this.node.getChildByName("third_player");
        var forthPlayer = this.node.getChildByName("forth_player");
        var playerCmp = firstPlayer.getComponent("Player");
        var playerCmpId = playerCmp.playerId;
        console.log("第一个玩家的playerId="+playerCmpId);
        if(playerCmpId && playerCmpId == playerId) {
            return firstPlayer;
        }
        playerCmp = secondPlayer.getComponent("Player");
        playerCmpId = playerCmp.playerId;
        console.log("第二个玩家的playerId="+playerCmpId);
        if(playerCmpId && playerCmpId == playerId) {
            return secondPlayer;
        }
        playerCmp = thirdPlayer.getComponent("Player");
        playerCmpId = playerCmp.playerId;
        console.log("第三个玩家的playerId="+playerCmpId);
        if(playerCmpId && playerCmpId == playerId) {
            return thirdPlayer;
        }
        playerCmp = forthPlayer.getComponent("Player");
        playerCmpId = playerCmp.playerId;
        console.log("第四个玩家的playerId="+playerCmpId);
        if(playerCmpId && playerCmpId == playerId) {
            return forthPlayer;
        }
        console.log("未找到玩家");
    },
    getEmptyPlayerCmp() {
        var firstPlayer = this.node.getChildByName("first_player");
        var secondPlayer = this.node.getChildByName("second_player");
        var thirdPlayer = this.node.getChildByName("third_player");
        var forthPlayer = this.node.getChildByName("forth_player");
        var playerCmp = firstPlayer.getComponent("Player");
        var playerCmpId = playerCmp.playerId;
        if(!playerCmpId) {
            return firstPlayer;
        }
        playerCmp = secondPlayer.getComponent("Player");
        playerCmpId = playerCmp.playerId;
        if(!playerCmpId) {
            return secondPlayer;
        }
        playerCmp = thirdPlayer.getComponent("Player");
        playerCmpId = playerCmp.playerId;
        if(!playerCmpId) {
            return thirdPlayer;
        }
        playerCmp = forthPlayer.getComponent("Player");
        playerCmpId = playerCmp.playerId;
        if(!playerCmpId) {
            return forthPlayer;
        }
    }

    // update (dt) {},
});
