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
        scale: 0,
        index: {    //属于第几个算数符号，将Calculate中的值对应更新成对应的算数符号
            default: 0,
            type: cc.Integer
        },
        symbol: {
            default: 0,
            type: cc.Integer
        },
        gameContainer: {
            default: null,
            type: cc.Node
        }
    },

    // LIFE-CYCLE CALLBACKS:

    onLoad () {
        this.node.on(cc.Node.EventType.TOUCH_START, function(event) {
            var targetBtn = event.target;
            var calculateButtons = targetBtn.parent;
            var buttons = calculateButtons.children;
            for(var i = 0; i < buttons.length; i ++) {
                var button = buttons[i];
                button.runAction(cc.scaleTo(0.1, 1, 1));
            }
            targetBtn.runAction(cc.scaleTo(0.1, 0.8, 0.8));
        });
        this.node.on(cc.Node.EventType.TOUCH_END, function(event) {
            var calculateIndx = this.index;
            var symbolIndex = this.symbol;
            console.log("index="+calculateIndx+", symbol="+symbolIndex);
            var gameContainerCmp = this.gameContainer.getComponent("Game");
            switch (calculateIndx) {
                case 1: gameContainerCmp.firstBtn = this.node; break;
                case 2: gameContainerCmp.secondBtn = this.node; break;
                case 3: gameContainerCmp.thirdBtn = this.node; break;
            }
            this.gameContainer.getComponent("Game").calculate();
        }.bind(this));
    },

    start () {

    },

    // update (dt) {},
});
