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
    /*Size size = Director::getInstance()->getWinSize();
    map->setPosition(Vec2(size.width/2, size.height*0.5));*/
    Sprite* sprite = Sprite::create("tilemap/Player.png");
    sprite->setPosition(Vec2(50, 50));
    this->addChild(sprite, 100, "player");
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(TileMapLayer::onTouchesMoved, this);
    listener->onTouchesBegan = CC_CALLBACK_2(TileMapLayer::onTouchesBegan, this);
    listener->onTouchesEnded = CC_CALLBACK_2(TileMapLayer::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void TileMapLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
    log("touch size: %d", touches.size());
    //单点移动，则移动地图，否则缩放或者放大地图
    if(touches.size() == 1) {
        auto touch = touches[0];
        auto diff = touch->getDelta();
        auto node = getChildByTag(99);
        auto currentPos = node->getPosition();
        node->setPosition(currentPos + diff);
        return;
    }
    Touch* touch1 = touches[0];
    std::map<int, Vec2>::iterator iter = this->pMap.find(touch1->getID());
    Vec2 original1 = iter->second;
    Vec2 curr1 = touch1->getLocation();

    Touch* touch2 = touches[1];
    std::map<int, Vec2>::iterator iter2 = this->pMap.find(touch1->getID());
    Vec2 original2 = iter2->second;
    Vec2 curr2 = touch2->getLocation();

    float originalWidth = abs(original1.x - original2.x);
    float currWidth = abs(curr1.x - curr2.x);
    float scaleX = currWidth/originalWidth;
    TMXTiledMap* map = static_cast<TMXTiledMap*>(this->getChildByTag(99));
    map->setScale(scaleX);
}

void TileMapLayer::onTouchesBegan(const std::vector<Touch *> &touches, Event *event) {
    log("touch began");
    if(touches.size() > 1) {
        Touch* touch1 = touches[0];
        Vec2 pos1 = touch1->getLocation();
        Touch* touch2 = touches[1];
        Vec2 pos2 = touch2->getLocation();
        this->pMap.insert(std::pair<int, Vec2>(touch1->getID(), pos1));
        this->pMap.insert(std::pair<int, Vec2>(touch2->getID(), pos2));
    }
}

void TileMapLayer::onTouchesEnded(const std::vector<Touch *> &touches, Event *unused_event) {

}