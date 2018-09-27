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
        console.log(Global);
        var ws = new WebSocket("wss://www.uxgoo.com:8083");
        ws.onopen = function (event) {
            console.log("Send Text WS was opened.");
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
            var cmd = json.cmd;
            var data = json.data;
            if(cmd == "playerReady") {
                //如果开始倒计时，说明所有玩家都已经准备完成，倒计时结束后开始初始化游戏，初始化游戏完成后开始第一次发牌
                if(data.isCountDown == true) {
                    var second = data.second;
                    var count = 0;
                    this.schedule(function() {
                        //获取时钟对象，修改里面的数字
                        count ++;
                        if(count == second) {   //倒计时完成，开始初始化游戏
                            ws.send("{\"cmd\":\"initGame\", \"data\": {}}");
                        }
                    }, 1, second, 0);
                }
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
        var readyBtn = this.node.getChildByName("buttons").getChildByName("ready");
        var giveupBtn = this.node.getChildByName("buttons").getChildByName("giveup");
        giveupBtn.active = false;
        var restartBtn = this.node.getChildByName("buttons").getChildByName("restart_btn");
        var backBtn = this.node.getChildByName("buttons").getChildByName("back_btn");
        readyBtn.on(cc.Node.EventType.TOUCH_START, function(event) {
            this.expreInfoArr = [];
            var btn = event.target;
            btn.runAction(cc.sequence(cc.scaleTo(0.1, 0.85, 0.85), cc.scaleTo(0.1, 1, 1), cc.callFunc(function() {
                this.refreshPoker();
            }, this)));
            cc.loader.loadRes("audio/button", cc.AudioClip, function (err, clip) {
                var audioID = cc.audioEngine.play(clip, false, 1);
            });
            var firstPoker = this.node.getChildByName("first_porker");
            var secondPoker = this.node.getChildByName("second_porker");
            var thirdPoker = this.node.getChildByName("third_porker");
            var forthPoker = this.node.getChildByName("forth_porker");
            var lastFirstVal = firstPoker.getComponent("Porker").value;
            var lastSecondVal = secondPoker.getComponent("Porker").value;
            var lastThirdVal = thirdPoker.getComponent("Porker").value;
            var lastForthVal = forthPoker.getComponent("Porker").value;
            if(!lastFirstVal || !lastSecondVal || !lastThirdVal || !lastForthVal) {
                return ;
            }
            this.lastPokerValues = [lastFirstVal, lastSecondVal, lastThirdVal, lastForthVal];
            var lastPokers = "上局提示：\n\n"+lastFirstVal+", "+lastSecondVal+", "+lastThirdVal+", "+lastForthVal;
            this.lastPokerLbl.string = lastPokers;
            this.recursiveCal(this.selectedVal);
            var tips = "无解";
            if(this.expreInfoArr.length > 0) {
                tips = "";
                for(var i = 0; i < this.expreInfoArr.length; i ++) {
                    tips = tips + this.expreInfoArr[i]+"\n\n";
                }
            }
            this.lastExpression.string = tips;
        }, this);

        readyBtn.on(cc.Node.EventType.TOUCH_END, function(event){
            //发送到服务端玩家准备完成
            ws.send("{\"cmd\":\"playerReady\", \"data\": {\"roomNo\":"+Global.roomNo+", \"playerId\":"+Global.playerId+"}}");
            giveupBtn.active = true;
            readyBtn.active = false;
        }, this);

        giveupBtn.on(cc.Node.EventType.TOUCH_END, function(event){
            readyBtn.active = true;
            giveupBtn.active = false;
        }, this);

        restartBtn.on(cc.Node.EventType.TOUCH_START, function(event) {
            var btn = event.target;
            btn.runAction(cc.sequence(cc.scaleTo(0.1, 0.85, 0.85), cc.scaleTo(0.1, 1, 1), cc.callFunc(function() {
                this.refreshPoker();
            }, this)));
            cc.loader.loadRes("audio/button", cc.AudioClip, function (err, clip) {
                var audioID = cc.audioEngine.play(clip, false, 1);
            });
            this.initGame();
        }, this);

        backBtn.on(cc.Node.EventType.TOUCH_START, function(event) {
            var btn = event.target;
            cc.loader.loadRes("audio/button", cc.AudioClip, function (err, clip) {
                var audioID = cc.audioEngine.play(clip, false, 1);
            });
            btn.runAction(cc.sequence(cc.scaleTo(0.1, 0.85, 0.85), cc.scaleTo(0.1, 1, 1), cc.callFunc(function() {
                cc.director.loadScene("Menu");
            }, this)));
        }, this);
    },

    initGame() {
        this.clearTips();
        if(this.gameLevel == 0) {
            this.pokerValue = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
        } else if(this.gameLevel == 1) {
            this.pokerValue = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13];
        } else if(this.gameLevel == 2) {    //简单的在线对战
            //出现准备按钮
        }
        this.pokers = [];        
        for(var j = 0; j < this.pokerType.length; j ++) {
            for(var i = 0; i < this.pokerValue.length; i ++) {
                var key = this.pokerValue[i]+"-"+this.pokerType[j];
                var value = this.pokerValue[i];
                var poker = new Object();
                poker["key"] = key;
                poker["value"] = value;
                this.pokers.push(poker);
            }
        }
    },

    start () {

    },

    onDestroy() {
        cc.audioEngine.stop(this.current);
    },
    refreshPoker() {
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
        var cardDealAudioID = null;
        cc.loader.loadRes("audio/card_deal", cc.AudioClip, function (err, clip) {
            cardDealAudioID = cc.audioEngine.play(clip, false, 1);
        });
        var firstPoker = this.node.getChildByName("first_porker");
        var secondPoker = this.node.getChildByName("second_porker");
        var thirdPoker = this.node.getChildByName("third_porker");
        var forthPoker = this.node.getChildByName("forth_porker");
        var calFirstPoker = this.node.getChildByName("cal_first_porker");
        var calSecondPoker = this.node.getChildByName("cal_second_porker");
        var calThirdPoker = this.node.getChildByName("cal_third_porker");
        var calForthPoker = this.node.getChildByName("cal_forth_porker");
        var firstVal = 0;
        var secondVal = 0;
        var thirdVal = 0;
        var forthVal = 0;
        var poker = this.getPoker();
        if(poker) {
            cc.loader.loadRes("game/"+poker["key"], cc.SpriteFrame, function (err, spriteFrame) {
                firstPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            });
            firstPoker.getComponent("Porker").value=poker["value"];
            firstPoker.getComponent("Porker").key = poker["key"];
            firstVal = poker["value"];
        }
        
        poker = this.getPoker();
        if(poker) {
            cc.loader.loadRes("game/"+poker["key"], cc.SpriteFrame, function (err, spriteFrame) {
                secondPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            });
            secondPoker.getComponent("Porker").value=poker["value"];
            secondPoker.getComponent("Porker").key = poker["key"];
            secondVal = poker["value"];
        }
        
        poker = this.getPoker();
        if(poker) {
            cc.loader.loadRes("game/"+poker["key"], cc.SpriteFrame, function (err, spriteFrame) {
                thirdPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            });
            thirdPoker.getComponent("Porker").value=poker["value"];
            thirdPoker.getComponent("Porker").key = poker["key"];
            thirdVal = poker["value"];
        }
        poker = this.getPoker();
        if(poker) {
            cc.loader.loadRes("game/"+poker["key"], cc.SpriteFrame, function (err, spriteFrame) {
                forthPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            });
            forthPoker.getComponent("Porker").value=poker["value"];
            forthPoker.getComponent("Porker").key = poker["key"];
            forthVal = poker["value"];
        }
        this.selectedVal = [firstVal, secondVal, thirdVal, forthVal];
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
        if(Number.isInteger(result1) && Number.isInteger(result2) && result == 24) {
            console.log(expreTemp);
            this.expreInfoArr = expreTemp;
        }
        this.expreTemp = [];
        return result;
    },
    getResult(val, val2, expre, expreArr) {
        var result = 0;
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
            var firstResult = this.calculateResult(firstVal, secondVal, firstSymbol);
            console.log("symbol:"+firstSymbol+"第一个值"+firstVal+"和第二个值"+secondVal+"计算结果为："+firstResult);
            var secondResult = this.calculateResult(firstResult, thirdVal, secondSymbol);
            console.log("symbol:"+secondSymbol+"第一个结果"+firstResult+"和第三个值"+thirdVal+"计算结果为："+secondResult);
            var thirdResult = this.calculateResult(secondResult, forthVal, thirdSymbol);
            console.log("symbol:"+thirdSymbol+"第二个结果"+secondResult+"和第四个值"+forthVal+"计算结果为："+thirdResult);
            console.log("计算结果为："+thirdResult);
            //等于24，则提示用户赢了，并且增加用户积分，刷新新的牌出来
            if(thirdResult == 24) {
                this.showInfo("过关");
                this.refreshPoker();
                this.clearTips();
                return;
            }
            firstResult = this.calculateResult(firstVal, secondVal, firstSymbol);
            console.log("symbol:"+firstSymbol+"第一个值"+firstVal+"和第二个值"+secondVal+"计算结果为："+firstResult);
            secondResult = this.calculateResult(thirdVal, forthVal, thirdSymbol);
            console.log("symbol:"+thirdSymbol+"第三个值"+thirdVal+"和第四个值"+forthVal+"计算结果为："+secondResult);
            thirdResult = this.calculateResult(firstResult, secondResult, secondSymbol);
            console.log("symbol:"+secondSymbol+"第二个结果"+firstResult+"和第二个结果"+secondResult+"计算结果为："+thirdResult);
            if(thirdResult == 24) {
                this.showInfo("过关");
                this.refreshPoker();
                this.clearTips();
                return;
            }
            firstResult = this.calculateResult(secondVal, thirdVal, secondSymbol);
            console.log("symbol:"+secondSymbol+"第二个值"+secondVal+"和第三个值"+thirdVal+"计算结果为："+firstResult);
            secondResult = this.calculateResult(firstVal, firstResult, firstSymbol);
            console.log("symbol:"+firstSymbol+"第一个值"+firstVal+"和第一个结果"+firstResult+"计算结果为："+secondResult);
            thirdResult = this.calculateResult(secondResult, forthVal, thirdSymbol);
            console.log("symbol:"+thirdSymbol+"第二个结果"+secondResult+"和第四个值"+forthVal+"计算结果为："+thirdResult);
            if(thirdResult == 24) {
                this.showInfo("过关");
                this.refreshPoker();
                this.clearTips();
                return;
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
    showPokerInfo() {
        var len = this.pokers.length;
        this.pokerInfo.string = "剩余牌数："+len;
    },
    clearTips() {
        this.lastExpression.string = "";
        this.lastPokerLbl.string = "";
    }

    // update (dt) {},
});
