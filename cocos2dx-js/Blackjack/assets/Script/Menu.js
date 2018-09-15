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
        this.bgAudioId = cc.audioEngine.play(this.bgAudio, true, 1);
        cc.director.preloadScene("Game", function() {
            console.log("预加载游戏场景");
        });
        var quickStartBtn = this.node.getChildByName("quickStartBtn");
        var advanceBtn = this.node.getChildByName("advanceBtn");
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
    },

    onDestroy() {
        cc.audioEngine.stop(this.bgAudioId);
    }

    // called every frame, uncomment this function to activate update callback
    // update: function (dt) {

    // },
});
