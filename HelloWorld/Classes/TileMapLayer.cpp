//
// Created by LinusLan on 2018/2/23.
//

#include <Role/HeroSprite.h>
#include "TileMapLayer.h"
bool TileMapLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    TMXTiledMap* map = TMXTiledMap::create("tilemap/test2.tmx");
    this->addChild(map, 0, 99);
    Size size = Director::getInstance()->getWinSize();
    map->setPosition(Vec2(0, -150));
    /*Sprite* sprite = Sprite::create("tilemap/Player.png");
    sprite->setPosition(Vec2(100, 100));
    this->addChild(sprite, 100, "player");*/
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(TileMapLayer::onTouchesMoved, this);
    listener->onTouchesBegan = CC_CALLBACK_2(TileMapLayer::onTouchesBegan, this);
    listener->onTouchesEnded = CC_CALLBACK_2(TileMapLayer::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //角色移动触控版
    MoveSprite* moveSprite = MoveSprite::create();
    this->addChild(moveSprite, 0, 110);

    /*SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("tilemap/role.plist", "tilemap/role.png");
    Vector<SpriteFrame*> animeFrames;
    animeFrames.pushBack(sfc->getSpriteFrameByName("role-1.png"));
    animeFrames.pushBack(sfc->getSpriteFrameByName("role-2.png"));
    animeFrames.pushBack(sfc->getSpriteFrameByName("role-3.png"));
    animeFrames.pushBack(sfc->getSpriteFrameByName("role-4.png"));
    animeFrames.pushBack(sfc->getSpriteFrameByName("role-5.png"));
    animeFrames.pushBack(sfc->getSpriteFrameByName("role-6.png"));
    animeFrames.pushBack(sfc->getSpriteFrameByName("role-7.png"));
    animeFrames.pushBack(sfc->getSpriteFrameByName("role-8.png"));
    animeFrames.pushBack(sfc->getSpriteFrameByName("role-9.png"));
    animeFrames.pushBack(sfc->getSpriteFrameByName("role-2.png"));
    Animation* animation = Animation::createWithSpriteFrames(animeFrames, 0.12f);
    Animate* animate = Animate::create(animation);
    Sprite* hero = Sprite::createWithSpriteFrameName("role-1.png");
    hero->setPosition(Vec2(400, 400));
    hero->runAction(RepeatForever::create(animate));
    this->addChild(hero, 1, 100);
    hero->setFlippedX(true);*/
    HeroSprite* hero = HeroSprite::create();

    hero->setPosition(Vec2(400, 150));
    hero->setAnchorPoint(Vec2(0, 0));
    this->addChild(hero, 1, 100);
    hero->stand();
    /*Spear* spear = Spear::create();
    this->addChild(spear, 1, 200);
    spear->fight();
    spear->setPosition(Vec2(400, 150));*/
    return true;
}

void TileMapLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
    log("touch size: %d", touches.size());
    TMXTiledMap* map = static_cast<TMXTiledMap*>(this->getChildByTag(99));
    Size winSize = Director::getInstance()->getWinSize();
    //单点移动，则移动地图，否则缩放或者放大地图
    if(touches.size() == 1) {
        float x = map->getPositionX();
        float y = map->getPositionY();
        //移动地图
        auto touch = touches[0];
        Vec2 touchLocation = touch->getLocation();
        auto diff = touch->getDelta();
        auto node = getChildByTag(99);
        auto currentPos = node->getPosition();
        float originalX = x + diff.x;
        float originalY = y + diff.y;
        float endedX = abs(originalX)+winSize.width;
        float endedY = abs(originalY)+winSize.height;

        log("drag point: original_x=%f, original_y=%f, end_x=%f, end_y=%f, map.width=%f, map.height=%f, winSize.width=%f, winSize.height=%f",
            originalX, originalY, endedX, endedY, map->getContentSize().width, map->getContentSize().height, winSize.width, winSize.height);
        /*if(originalX > 0 || originalY > 0 || endedX < winSize.width || endedY < winSize.height) {    //边界检查
            return ;
        }*/
        if(originalX > 0 || originalY > -150 || endedX >= map->getContentSize().width || endedY >= map->getContentSize().height) {    //边界检查
            return ;
        }
        node->setPosition(currentPos + diff);
        return;
    }
    Touch* touch1 = touches[0];
    std::map<int, Vec2>::iterator iter = this->pMap.find(touch1->getID());
    Vec2 original1 = iter->second;
    Vec2 curr1 = touch1->getLocation();

    Touch* touch2 = touches[1];
    std::map<int, Vec2>::iterator iter2 = this->pMap.find(touch2->getID());
    Vec2 original2 = iter2->second;
    Vec2 curr2 = touch2->getLocation();
    log("touch original1.x=%f, original2.x=%f", original1.x, original2.x);
    float originalWidth = abs(original1.x-original2.x);
    if(originalWidth == 0) {
        original1 = curr1;
        original2 = curr2;
        this->pMap.insert(std::pair<int, Vec2>(touch1->getID(), original1));
        this->pMap.insert(std::pair<int, Vec2>(touch2->getID(), original2));
    }
    //float originalWidth = abs(original1.x - original2.x);
    //float currWidth = abs(curr1.x - curr2.x);
    float currWidth = abs(curr1.x-curr2.x);
    log("touch curr1.x=%f, curr2.x=%f", curr1.x, curr2.x);
    log("touch originalWidth=%f, currWidth=%f", originalWidth, currWidth);
    float scaleX = originalWidth == 0 ? 1 : currWidth/originalWidth;
    log("缩放比例：%f",scaleX);
    //缩放地图
    map->setScale(initScale*scaleX);
}

void TileMapLayer::onTouchesBegan(const std::vector<Touch *> &touches, Event *event) {
    log("touch began, size: %d", touches.size());
    if(touches.size() > 1) {
        Touch* touch1 = touches[0];
        Vec2 pos1 = touch1->getLocation();
        log("touch original1 x:%f, y:%f", pos1.x, pos1.y);
        Touch* touch2 = touches[1];
        Vec2 pos2 = touch2->getLocation();
        log("touch original2 x:%f, y:%f", pos2.x, pos2.y);
        this->pMap.insert(std::pair<int, Vec2>(touch1->getID(), pos1));
        this->pMap.insert(std::pair<int, Vec2>(touch2->getID(), pos2));
    }
}

void TileMapLayer::onTouchesEnded(const std::vector<Touch *> &touches, Event *unused_event) {
    this->pMap.clear();
    TMXTiledMap* map = static_cast<TMXTiledMap*>(this->getChildByTag(99));
    initScale = map->getScale();
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getChildByTag(110));
}