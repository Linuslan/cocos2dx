// Learn cc.Class:
//  - [Chinese] http://www.cocos.com/docs/creator/scripting/class.html
//  - [English] http://www.cocos2d-x.org/docs/editors_and_tools/creator-chapters/scripting/class/index.html
// Learn Attribute:
//  - [Chinese] http://www.cocos.com/docs/creator/scripting/reference/attributes.html
//  - [English] http://www.cocos2d-x.org/docs/editors_and_tools/creator-chapters/scripting/reference/attributes/index.html
// Learn life-cycle callbacks:
//  - [Chinese] http://www.cocos.com/docs/creator/scripting/life-cycle-callbacks.html
//  - [English] http://www.cocos2d-x.org/docs/editors_and_tools/creator-chapters/scripting/life-cycle-callbacks/index.html

cc.Class({
    extends: cc.Component,

    properties: {
        value: {
            default: null,
            type: cc.Integer
        },
        key: {
            default: "",
            type: cc.String
        },
        positionX: {
            default: 0,
            type: cc.Float
        },
        positionY: {
            default: 0,
            type: cc.Float
        },
        originalX: {
            default: 0,
            type: cc.Float
        },
        originalY: {
            default: 0,
            type: cc.Float
        },
        zIndex: {
            default: 0,
            type: cc.Integer
        }
    },

    // LIFE-CYCLE CALLBACKS:

    onLoad () {
        console.log("key="+this.key);
        console.log("value="+this.value);
        this.positionX = this.node.x;
        this.positionY = this.node.y;
        this.node.zIndex = 0;
        this.node.on(cc.Node.EventType.TOUCH_START, function(event) {
            console.log("获取到的位置为：x="+event.getLocation().x+", y="+event.getLocation().y);
            //this.node.position = cc.v2(event.getLocation().x, event.getLocation().y);
            this.originalX = this.node.position.x;
            this.originalY = this.node.position.y;
            this.node.zIndex = 100;
            //this.node.position = cc.v2(this.node.x-5, this.node.y-5);
        }, this);
        this.node.on(cc.Node.EventType.TOUCH_MOVE, function(event) {
            //将屏幕触摸的点的坐标转化为游戏内的坐标
            var touchX = event.getLocation().x - this.node.parent.position.x;
            var touchY = event.getLocation().y - this.node.parent.position.y;
            this.node.position = cc.v2(touchX, touchY);
        }, this);
        //移动结束，判断是否和需要计算卡牌的空格相交，如果相交，则复制一份副本到相交的卡牌中
        this.node.on(cc.Node.EventType.TOUCH_END, function(event) {
            this.node.zIndex = 0;
            var calculatePorker = this.node.parent;
            var firstPorker = calculatePorker.getChildByName("cal_first_porker");
            var secondPorker = calculatePorker.getChildByName("cal_second_porker");
            var thirdPorker = calculatePorker.getChildByName("cal_third_porker");
            var forthPorker = calculatePorker.getChildByName("cal_forth_porker");
            var pokerNodes = [firstPorker, secondPorker, thirdPorker, forthPorker];
            console.log("移动结束");
            console.log(this.node.getBoundingBoxToWorld());
            console.log(firstPorker.getBoundingBoxToWorld());
            console.log("key="+this.key);
            console.log("value="+this.value);
            for(var i = 0; i < pokerNodes.length; i ++) {
                var pokerNode = pokerNodes[i];
                this.changePoker(pokerNode);
            }
            this.node.position = cc.v2(this.positionX, this.positionY);
            this.node.parent.getComponent("Game").calculate();
        }, this);
    },

    start () {

    },

    changePoker: function(pokerNode) {
        console.log(pokerNode);
        var calculatePorker = this.node.parent;
        var firstPorker = calculatePorker.getChildByName("cal_first_porker");
        var secondPorker = calculatePorker.getChildByName("cal_second_porker");
        var thirdPorker = calculatePorker.getChildByName("cal_third_porker");
        var forthPorker = calculatePorker.getChildByName("cal_forth_porker");
        var pokerNodes = [firstPorker, secondPorker, thirdPorker, forthPorker];
        console.log(pokerNodes);
        if(cc.Intersection.rectRect(this.node.getBoundingBoxToWorld(), pokerNode.getBoundingBoxToWorld())) {
            var poker = null;
            for(var i = 0; i < pokerNodes.length; i ++) {
                var pokerObj = pokerNodes[i];
                var pokerNodeCmp = pokerObj.getComponent("Porker");
                var key = pokerNodeCmp.key;
                if(key && key == this.key) {
                    poker = pokerObj;
                }
            }
            console.log(poker);
            var newkey = this.key;
            var newValue = this.value;
            console.log("newkey="+newkey+", newValue="+newValue);
            if(pokerNode.getComponent("Porker").key && poker) {
                cc.loader.loadRes("game/"+pokerNode.getComponent("Porker").key, cc.SpriteFrame, function (err, spriteFrame) {
                    poker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
                });
                poker.getComponent("Porker").key = pokerNode.getComponent("Porker").key;
                poker.getComponent("Porker").value = pokerNode.getComponent("Porker").value;
            }
            cc.loader.loadRes("game/"+newkey, cc.SpriteFrame, function (err, spriteFrame) {
                pokerNode.getComponent(cc.Sprite).spriteFrame = spriteFrame;
            });
            pokerNode.getComponent("Porker").key = newkey;
            pokerNode.getComponent("Porker").value = newValue;
        }
    }

    // update (dt) {},
});
