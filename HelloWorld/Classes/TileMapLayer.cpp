//
// Created by LinusLan on 2018/2/23.
//

#include "TileMapLayer.h"
bool TileMapLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    TMXTiledMap* map = TMXTiledMap::create("tilemap/test1.tmx");
    this->addChild(map, 0, 99);
    Size size = Director::getInstance()->getWinSize();
    map->setPosition(Vec2(-50, -50));
    map->setAnchorPoint(Vec2::ZERO);
    Sprite* sprite = Sprite::create("tilemap/Player.png");
    sprite->setPosition(Vec2(50, 50));
    this->addChild(sprite, 100, "player");
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(TileMapLayer::onTouchesMoved, this);
    listener->onTouchesBegan = CC_CALLBACK_2(TileMapLayer::onTouchesBegan, this);
    listener->onTouchesEnded = CC_CALLBACK_2(TileMapLayer::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //角色移动触控版
    MoveSprite* moveSprite = MoveSprite::create();
    this->addChild(moveSprite);
    return true;
}

void TileMapLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
    log("touch size: %d", touches.size());
    TMXTiledMap* map = static_cast<TMXTiledMap*>(this->getChildByTag(99));
    //单点移动，则移动地图，否则缩放或者放大地图
    if(touches.size() == 1) {
        float x = map->getPositionX();
        float y = map->getPositionY();
        //移动地图
        auto touch = touches[0];
        auto diff = touch->getDelta();
        auto node = getChildByTag(99);
        auto currentPos = node->getPosition();
        float originalX = x + diff.x;
        float originalY = y + diff.y;
        float endedX = x + map->getContentSize().width;
        float endedY = y + map->getContentSize().height;
        Size winSize = Director::getInstance()->getWinSize();
        /*if(originalX > 0 || originalY > 0 || endedX < winSize.width || endedY < winSize.height) {    //边界检查
            return ;
        }*/
        if(originalX > 0 || originalY > 0) {    //边界检查
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
}