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
    this->addChild(background);

    //添加地板
    Sprite* floor = Sprite::create("pic/floor.png");
    floor->setPosition(Vec2(winSize.width*0.5, winSize.height*0.05));
    floor->setScaleX(2);
    MoveBy* act1 = MoveBy::create(1, Vec2(-108, 0));
    MoveTo* act2 = MoveTo::create(0, Vec2(winSize.width/2, winSize.height*0.05));
    Sequence* seq = Sequence::create(act1, act2, nullptr);
    floor->runAction(RepeatForever::create(seq));
    this->addChild(floor, 5);
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("pic/bird.plist", "pic/birdP.png");
    Vector<SpriteFrame*> animeFrames;
    animeFrames.pushBack(sfc->getSpriteFrameByName("bird1.png"));
    animeFrames.pushBack(sfc->getSpriteFrameByName("bird2.png"));
    animeFrames.pushBack(sfc->getSpriteFrameByName("bird3.png"));
    Animation* animation = Animation::createWithSpriteFrames(animeFrames, 0.1f);
    Animate* animate = Animate::create(animation);
    bird = Sprite::createWithSpriteFrame(sfc->getSpriteFrameByName("bird2.png"));
    bird->setPosition(Vec2(200, 200));
    bird->runAction(RepeatForever::create(animate));
    this->addChild(bird, 10, "bird");
    this->schedule(schedule_selector(BirdMainLayer::createTube), 2);

    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        Layer* layer = static_cast<Layer*>(event->getCurrentTarget());
        Sprite* bird = static_cast<Sprite*>(layer->getChildByName("bird"));
        //bird->stopActionByTag(0);
        bird->stopActionByTag(1);
        MoveBy* flyUp = MoveBy::create(0.25, Vec2(0, 25));
        MoveTo* flyDown = MoveTo::create(0.8, Vec2(200, 20));
        Sequence* seq = Sequence::create(flyUp, flyDown, nullptr);
        seq->setTag(1);
        bird->runAction(seq);
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    return true;
}

void BirdMainLayer::createTube(float a) {
    Size winSize = Director::getInstance()->getWinSize();
    log("可视区域的大小为width:%f, height:%f", winSize.width, winSize.height);
    int speed = 4.5;  //管子移动的速度
    int topMinHeight = 230; //上层管子距离屏幕底部最小的距离
    int topBottomDis = 50;  //上层管子和下层管子之间的距离
    //获取随机数
    srand((unsigned)time(nullptr));
    int randomNum = rand();
    log("本次生成的随机数为：%d", randomNum);
    int topY = (randomNum%(int(winSize.height)-topMinHeight))+topMinHeight;
    log("本次生成的topY的值为：%d", topY);
    int bottomY = topY - topBottomDis;
    log("本次生成的bottomY:%d", bottomY);

    //添加柱子的上部分
    topTube = Sprite::create("pic/column2.png");
    topTube->setPosition(Vec2(winSize.width, topY));
    topTube->setScaleY(2.0f);
    this->addChild(topTube);
    MoveBy* topTubeAct1 = MoveBy::create(speed, Vec2(-winSize.width, 0));
    Sequence* topTubeActSeq = Sequence::create(topTubeAct1, nullptr);
    topTube->runAction(topTubeActSeq);

    //添加柱子的下部分
    bottomTube = Sprite::create("pic/column1.png");
    bottomTube->setScaleY(2.0f);
    log("下部分管子的height:%f", bottomTube->getContentSize().height*2);
    bottomY = bottomY-int(bottomTube->getContentSize().height)*2;
    log("计算最终的bottomY:%d", bottomY);
    bottomTube->setPosition(Vec2(winSize.width, bottomY));
    this->addChild(bottomTube, 2);
    MoveBy* bottomTubeAct1 = MoveBy::create(speed, Vec2(-winSize.width, 0));
    Sequence* bottomTubeActSeq = Sequence::create(bottomTubeAct1, nullptr);
    bottomTube->runAction(bottomTubeActSeq);
}
