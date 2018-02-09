//
// Created by LinusLan on 2018/2/8.
//

#include "BirdMainLayer.h"
bool BirdMainLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    //添加背景
    Sprite* background = Sprite::create("pic/morning.png");
    background->setPosition(Vec2(winSize/2));
    background->setScale(1.5f, 2.0f);
    /*background->setPosition(Vec2(0, 0));
    background->setAnchorPoint(Vec2(1, 0));*/
    this->addChild(background);

    //添加地板
    Sprite* floor = Sprite::create("pic/floor.png");
    floor->setPosition(Vec2(winSize.width*0.5, winSize.height*0.05));
    /*floor->setPosition(Vec2(0, 0));
    floor->setAnchorPoint(Vec2(0, 0));*/
    floor->setScaleX(2);
    MoveBy* act1 = MoveBy::create(1, Vec2(108, 0));
    MoveTo* act2 = MoveTo::create(0, Vec2(winSize.width/2, winSize.height*0.05));
    Sequence* seq = Sequence::create(act1, act2, nullptr);
    floor->runAction(RepeatForever::create(seq));
    this->addChild(floor);
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("pic/bird.plist", "pic/birdP.png");
    Vector<SpriteFrame*> animeFrames;
    animeFrames.pushBack(sfc->getSpriteFrameByName("bird1.png"));
    animeFrames.pushBack(sfc->getSpriteFrameByName("bird2.png"));
    animeFrames.pushBack(sfc->getSpriteFrameByName("bird3.png"));
    Animation* animation = Animation::createWithSpriteFrames(animeFrames, 0.1f);
    Animate* animate = Animate::create(animation);
    Sprite* bird = Sprite::createWithSpriteFrame(sfc->getSpriteFrameByName("bird2.png"));
    bird->setPosition(Vec2(200, 100));
    bird->runAction(RepeatForever::create(animate));
    this->addChild(bird, 10);
    return true;
}
