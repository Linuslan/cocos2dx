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
    //background->setScale(1.5f, 2.0f);
    this->addChild(background);

    //添加地板
    Sprite* floor = Sprite::create("pic/floor.png");
    floor->setPosition(Vec2(winSize.width*0.5, winSize.height*0.02));
    //floor->setScaleX(2);
    MoveBy* act1 = MoveBy::create(1, Vec2(-108, 0));
    MoveTo* act2 = MoveTo::create(0, Vec2(winSize.width/2, winSize.height*0.02));
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
    bird->setPosition(Vec2(200, 300));
    bird->runAction(RepeatForever::create(animate));
    this->addChild(bird, 10, "bird");
    this->schedule(schedule_selector(BirdMainLayer::createTube), 2);


    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        Layer* layer = static_cast<Layer*>(event->getCurrentTarget());
        Sprite* bird = static_cast<Sprite*>(layer->getChildByName("bird"));
        bird->stopActionByTag(1);
        MoveBy* flyUp = MoveBy::create(0.25, Vec2(0, 25));
        MoveTo* flyDown = MoveTo::create(0.8, Vec2(200, 20));
        Sequence* seq = Sequence::create(flyUp, flyDown, nullptr);
        seq->setTag(1);
        bird->runAction(seq);
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    scheduleUpdate();
    return true;
}

void BirdMainLayer::createTube(float a) {
    Size winSize = Director::getInstance()->getWinSize();
    //log("可视区域的大小为width:%f, height:%f", winSize.width, winSize.height);
    int speed = 4.5;  //管子移动的速度
    int topMinHeight = 700; //上层管子距离屏幕底部最小的距离
    int topBottomDis = 150;  //上层管子和下层管子之间的距离
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
    //topTube->setScaleY(2.0f);
    this->addChild(topTube);
    MoveBy* topTubeAct1 = MoveBy::create(speed, Vec2(-winSize.width-20, 0));
    Sequence* topTubeActSeq = Sequence::create(topTubeAct1, nullptr);
    topTube->runAction(topTubeActSeq);
    topTube->setName("topTube");

    //添加柱子的下部分
    bottomTube = Sprite::create("pic/column1.png");
    //bottomTube->setScaleY(2.0f);
    log("下部分管子的height:%f", bottomTube->getContentSize().height);
    bottomY = bottomY-int(bottomTube->getContentSize().height);
    log("计算最终的bottomY:%d", bottomY);
    bottomTube->setPosition(Vec2(winSize.width, bottomY));
    this->addChild(bottomTube, 2);
    MoveBy* bottomTubeAct1 = MoveBy::create(speed, Vec2(-winSize.width-20, 0));
    Sequence* bottomTubeActSeq = Sequence::create(bottomTubeAct1, nullptr);
    bottomTube->runAction(bottomTubeActSeq);
    bottomTube->setName("bottomTube");
}

void BirdMainLayer::update(float a) {
    log("执行碰撞检测");
    if(nullptr != bird && nullptr != topTube && nullptr != bottomTube) {
        log("所有对象都不为空，进入碰撞检测逻辑判断");
        Rect birdRect = bird->getBoundingBox();
        Rect topTubeRect = topTube->getBoundingBox();
        Rect bottomTubeRect = bottomTube->getBoundingBox();
        if(birdRect.intersectsRect(topTubeRect) || birdRect.intersectsRect(bottomTubeRect)) {
            log("精灵碰撞，小鸟死亡");
            bird->stopAllActions();
            bird->setRotation(90);
            MoveTo* act1 = MoveTo::create(1.5, Vec2(bird->getPosition().x, 0));
            bird->runAction(act1);
            log("abcdefg");
        }
        Vector<Node*> sprites = this->getChildren();
        for(Node* node : sprites) {
            if(node->getName() == "topTube" || node->getName() == "bottomTube") {
                if(node->getPosition().x < 0) {
                    node->removeFromParent();
                }
            }
        }
    }
}

void BirdMainLayer::detectCollisionByRect() {
    log("执行碰撞检测");
    if(nullptr != bird && nullptr != topTube && nullptr != bottomTube) {
        log("所有对象都不为空，进入碰撞检测逻辑判断");
        Rect birdRect = bird->getBoundingBox();
        Rect topTubeRect = topTube->getBoundingBox();
        float topMaxX = topTubeRect.getMaxX();
        float topMinX = topTubeRect.getMinX();
        float topMidX = topTubeRect.getMidX();
        float topMaxY = topTubeRect.getMaxY();
        float topMinY = topTubeRect.getMinY();
        float topMidY = topTubeRect.getMidY();
        float birdMaxX = birdRect.getMaxX();
        float birdMinX = birdRect.getMinX();
        float birdMidX = birdRect.getMidX();
        float birdMaxY = birdRect.getMaxY();
        float birdMinY = birdRect.getMinY();
        float birdMidY = birdRect.getMidY();
        log("上层管子 maxX = %f, midX = %f, minX = %f, maxY = %f, midY = %f, minY = %f", topMaxX, topMidX, topMinX, topMaxY, topMidY, topMinY);
        log("小鸟位置 maxX = %f, midX = %f, minX = %f, maxY = %f, midY = %f, minY = %f", birdMaxX, birdMidX, birdMinX, birdMaxY, birdMidY, birdMinY);

        Rect bottomTubeRect = bottomTube->getBoundingBox();
        if(topTubeRect.intersectsRect(birdRect) || bottomTubeRect.intersectsRect(birdRect)) {
            log("精灵碰撞，小鸟死亡");
            bird->stopAllActions();
            bird->setRotation(90);
            MoveTo* act1 = MoveTo::create(1.5, Vec2(bird->getPosition().x, 0));
            bird->runAction(act1);
            log("abcdefg");
        }
    }
}

void BirdMainLayer::detectCollisionByPosition() {
    Vec2 birdPosition = bird->getPosition();
    float birdMaxX = birdPosition.x+bird->getContentSize().width/2;
    float birdMinX = birdMaxX-bird->getContentSize().width;
    float birdMaxY = birdPosition.y + bird->getContentSize().height/2;
    float birdMinY = birdMaxY - bird->getContentSize().height;

    Vec2 topTubePosition = topTube->getPosition();
    float topTubeMaxX = topTubePosition.x + topTube->getContentSize().width/2;
    float topTubeMinX = topTubeMaxX-topTube->getContentSize().width;
    float topTubeMaxY = topTubePosition.y + topTube->getContentSize().height/2;
    float topTubeMinY = topTubeMaxY - topTube->getContentSize().height;
}