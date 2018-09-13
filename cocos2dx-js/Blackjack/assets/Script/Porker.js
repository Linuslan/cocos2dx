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
            default: 1,
            type: cc.Integer
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
        }
    },

    // LIFE-CYCLE CALLBACKS:

    onLoad () {
        this.node.on(cc.Node.EventType.TOUCH_START, function(event) {
            console.log("获取到的位置为：x="+event.getLocation().x+", y="+event.getLocation().y);
            //this.node.position = cc.v2(event.getLocation().x, event.getLocation().y);
            this.originalX = this.node.position.x;
            this.originalY = this.node.position.y;
            //this.node.position = cc.v2(this.node.x-5, this.node.y-5);
        }, this);
        this.node.on(cc.Node.EventType.TOUCH_MOVE, function(event) {
            //将屏幕触摸的点的坐标转化为游戏内的坐标
            var touchX = event.getLocation().x - this.node.parent.position.x;
            var touchY = event.getLocation().y - this.node.parent.position.y;
            this.node.position = cc.v2(touchX, touchY);
            //console.log("touch.x="+touchX+", touch.y="+touchY+", porker.x="+this.node.parent.parent.position.x+", porker.y="+this.node.parent.parent.position.y);
            /*var x = touchX - this.originalX;
            var y = touchY - this.originalY;
            console.log("x="+x+", y="+y);
            var degree = Math.atan2(x, y)*180.0/Math.PI;
            var distance = 3.0;
            var offsetY = Math.sin(degree/180*Math.PI)*distance;   //将角度转化为弧度，再用三角函数求坐标
            var offsetX = Math.cos(degree/180*Math.PI)*distance;
            console.log("degree="+degree+", 当前节点位置：x="+this.node.position.x+", y="+this.node.position.y+", offsetX="+offsetX+", offsetY="+offsetY);
            var nodex = this.node.position.x;
            var nodey = this.node.position.y;
            if(degree > 90 || degree < -90) {
                nodex = this.node.position.x - offsetX;
            } else {
                nodex = this.node.position.x + offsetX;
            }
            if(degree > 0) {
                nodey = this.node.position.y + offsetY;
            } else {
                nodey = this.node.position.y - offsetY;
            }
            //var nodex = this.node.position.x + offsetX;
            //var nodey = this.node.position.y + offsetY;
            this.node.position = cc.v2(nodex, nodey);*/
        }, this);
        //移动结束，判断是否和需要计算卡牌的空格相交，如果相交，则复制一份副本到相交的卡牌中
        this.node.on(cc.Node.EventType.TOUCH_END, function(event) {
            var calculatePorker = this.node.parent;
            var firstPorker = calculatePorker.getChildByName("first_porker");
            var secondPorker = calculatePorker.getChildByName("second_porker");
            var thirdPorker = calculatePorker.getChildByName("third_porker");
            var forthPorker = calculatePorker.getChildByName("forth_porker");
            console.log("移动结束");
            console.log(this.node.getBoundingBoxToWorld());
            console.log(firstPorker.getBoundingBoxToWorld());
            if(cc.Intersection.rectRect(this.node.getBoundingBoxToWorld(), firstPorker.getBoundingBoxToWorld())) {
                console.log("和第一个底牌相交");
                firstPorker.getComponent(cc.Sprite).spriteFrame.setTexture("assets/Texture/game/poker_dipai");
                cc.loader.loadRes("test assets/Texture/game/poker_dipai", cc.SpriteFrame, function (err, spriteFrame) {
                    firstPorker.getComponent(cc.Sprite).spriteFrame = spriteFrame;
                });
            }
            console.log(secondPorker.getBoundingBoxToWorld());
            if(cc.Intersection.rectRect(this.node.getBoundingBoxToWorld(), secondPorker.getBoundingBoxToWorld())) {
                console.log("和第二个底牌相交");
                secondPorker.getComponent(cc.Sprite).spriteFrame.setTexture("assets/Texture/game/poker_dipai");
            }
            console.log(thirdPorker.getBoundingBoxToWorld());
            if(cc.Intersection.rectRect(this.node.getBoundingBoxToWorld(), thirdPorker.getBoundingBoxToWorld())) {
                console.log("和第三个底牌相交");
                thirdPorker.getComponent(cc.Sprite).spriteFrame.setTexture("assets/Texture/game/poker_dipai");
            }
            console.log(forthPorker.getBoundingBoxToWorld());
            if(cc.Intersection.rectRect(this.node.getBoundingBoxToWorld(), forthPorker.getBoundingBoxToWorld())) {
                console.log("和第四个底牌相交");
                forthPorker.getComponent(cc.Sprite).spriteFrame.setTexture("assets/Texture/game/poker_dipai");
            }
            this.node.position = cc.v2(this.positionX, this.positionY);
        }, this);
    },

    start () {

    },

    // update (dt) {},
});
