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
        starPrefab: {
        	default: null,
        	type: cc.Prefab
        },
        maxStarDuration: 0,
        minStarDuration: 0,
        ground: {
        	default: null,
        	type: cc.Node
        },
        player: {
        	default: null,
        	type: cc.Node
        },
        scoreDisplay: {
        	default: null,
        	type: cc.Label
        },
        scoreAudio: {
            default: null,
            url: cc.AudioClip
        }
    },

    // LIFE-CYCLE CALLBACKS:

    onLoad: function() {
    	this.score = 0;
    	this.timer = 0;
    	this.starDuration = 0;
    	this.groundY = this.ground.y + this.ground.height/2;
    	this.spawnNewStar();
    },
    spawnNewStar: function() {
    	var star = cc.instantiate(this.starPrefab);
    	this.node.addChild(star);
    	star.setPosition(this.getNewStarPosition());
    	star.getComponent("Star").game = this;
    	this.starDuration = this.minStarDuration + Math.random() * (this.maxStarDuration - this.minStarDuration);
    	this.timer = 0;
    },
    getNewStarPosition: function() {
    	var randX = 0;
    	var randY = this.groundY + Math.random()*this.player.getComponent("Player").jumpHeight + 50;
    	var maxX = this.node.width/2;
    	randX = (Math.random()-0.5)*2*maxX;
    	return cc.v2(randX, randY);
    },
    start () {

    },
    gainScore: function() {
    	this.score += 1;
    	this.scoreDisplay.string = "Score: "+this.score;
    	cc.audioEngine.playEffect(this.scoreAudio, false);
    },
    update: function(dt) {
    	if(this.timer > this.starDuration) {
    		this.gameOver();
    		return;
    	}
    	this.timer += dt;
    },
    gameOver: function() {
    	this.player.stopAllActions();
    	cc.director.loadScene("EatStart");
    }
});
