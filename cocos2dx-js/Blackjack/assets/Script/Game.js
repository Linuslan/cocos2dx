cc.Class({
    extends: cc.Component,

    properties: {
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
        }
    },

    // LIFE-CYCLE CALLBACKS:

    onLoad () {
        this.pokerType = ["clubs", "diamonds", "hearts", "spades"];
        this.pokerValue = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13];
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
        var startBtn = this.node.getChildByName("buttons").getChildByName("start_btn").getChildByName("button");
        startBtn.on(cc.Node.EventType.TOUCH_START, function(event) {
            var btn = event.target;
            btn.runAction(cc.sequence(cc.scaleTo(0.1, 0.4, 0.85), cc.scaleTo(0.1, 0.5, 1), cc.callFunc(function() {
                if(this.pokers.length <= 0) {
                    return;
                }
                var firstPoker = this.node.getChildByName("first_porker");
                var secondPoker = this.node.getChildByName("second_porker");
                var thirdPoker = this.node.getChildByName("third_porker");
                var forthPoker = this.node.getChildByName("forth_porker");
                var idx = Math.floor(Math.random()*(this.pokers.length-0+1)+0);
                var poker = this.pokers[idx];
                var key = poker["key"];
                var value = poker["value"]
                cc.loader.loadRes("game/"+key, cc.SpriteFrame, function (err, spriteFrame) {
                    firstPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
                });
                firstPoker.getComponent("Porker").value=value;
                this.pokers.splice(idx, 1);
                console.log("选中索引："+idx);

                idx = Math.floor(Math.random()*(this.pokers.length-0+1)+0);
                poker = this.pokers[idx];
                key = poker["key"];
                value = poker["value"]
                cc.loader.loadRes("game/"+key, cc.SpriteFrame, function (err, spriteFrame) {
                    secondPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
                });
                secondPoker.getComponent("Porker").value=value;
                this.pokers.splice(idx, 1);
                console.log("选中索引："+idx);

                idx = Math.floor(Math.random()*(this.pokers.length-0+1)+0);
                poker = this.pokers[idx];
                key = poker["key"];
                value = poker["value"]
                cc.loader.loadRes("game/"+key, cc.SpriteFrame, function (err, spriteFrame) {
                    thirdPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
                });
                thirdPoker.getComponent("Porker").value=value;
                this.pokers.splice(idx, 1);
                console.log("选中索引："+idx);
                
                idx = Math.floor(Math.random()*(this.pokers.length-0+1)+0);
                poker = this.pokers[idx];
                key = poker["key"];
                value = poker["value"]
                cc.loader.loadRes("game/"+key, cc.SpriteFrame, function (err, spriteFrame) {
                    forthPoker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
                });
                forthPoker.getComponent("Porker").value=value;
                this.pokers.splice(idx, 1);
                console.log("选中索引："+idx);
            }, this)));
        }, this);
    },

    start () {

    },

    // update (dt) {},
});
