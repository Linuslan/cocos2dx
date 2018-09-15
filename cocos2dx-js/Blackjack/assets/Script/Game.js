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
        }
    },

    // LIFE-CYCLE CALLBACKS:

    onLoad () {
        cc.director.preloadScene("Menu", function() {
            console.log("预加载游戏场景");
        });
        this.current = cc.audioEngine.play(this.bgAudio, true, 1);
        this.resultInfo.string = "";
        this.pokerType = ["clubs", "diamonds", "hearts", "spades"];
        var startBtn = this.node.getChildByName("buttons").getChildByName("hit");
        var restartBtn = this.node.getChildByName("buttons").getChildByName("restart_btn");
        var backBtn = this.node.getChildByName("buttons").getChildByName("back_btn");
        startBtn.on(cc.Node.EventType.TOUCH_START, function(event) {
            var btn = event.target;
            btn.runAction(cc.sequence(cc.scaleTo(0.1, 0.85, 0.85), cc.scaleTo(0.1, 1, 1), cc.callFunc(function() {
                this.refreshPoker();
            }, this)));
            cc.loader.loadRes("audio/button", cc.AudioClip, function (err, clip) {
                var audioID = cc.audioEngine.play(clip, false, 1);
            });
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
        if(this.gameLevel == 0) {
            this.pokerValue = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
        } else {
            this.pokerValue = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13];
        }
                        
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
        var poker = this.getPoker();
        if(poker) {
            cc.loader.loadRes("game/"+poker["key"], cc.SpriteFrame, function (err, spriteFrame) {
                firstPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            });
            firstPoker.getComponent("Porker").value=poker["value"];
            firstPoker.getComponent("Porker").key = poker["key"];
        }
        
        poker = this.getPoker();
        if(poker) {
            cc.loader.loadRes("game/"+poker["key"], cc.SpriteFrame, function (err, spriteFrame) {
                secondPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            });
            secondPoker.getComponent("Porker").value=poker["value"];
            secondPoker.getComponent("Porker").key = poker["key"];
        }
        
        poker = this.getPoker();
        if(poker) {
            cc.loader.loadRes("game/"+poker["key"], cc.SpriteFrame, function (err, spriteFrame) {
                thirdPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            });
            thirdPoker.getComponent("Porker").value=poker["value"];
            thirdPoker.getComponent("Porker").key = poker["key"];
        }
        poker = this.getPoker();
        if(poker) {
            cc.loader.loadRes("game/"+poker["key"], cc.SpriteFrame, function (err, spriteFrame) {
                forthPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            });
            forthPoker.getComponent("Porker").value=poker["value"];
            forthPoker.getComponent("Porker").key = poker["key"];
        }
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
        console.log("选中索引："+idx);
        console.log(this.pokers);
        var poker = this.pokers[idx];
        this.pokers.splice(idx, 1);
        this.showPokerInfo();
        return poker;
    },
    calculate() {
        console.log("进入结果计算");
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
            console.log("开始计算结果");
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
        console.log("通知信息为："+msg);
        this.resultInfo.string = msg;
        this.resultInfo.scheduleOnce(function() {
            // 这里的 this 指向 component
            this.string = "";
        }, 2);
    },
    showPokerInfo() {
        var len = this.pokers.length;
        this.pokerInfo.string = "剩余牌数："+len;
    }

    // update (dt) {},
});
