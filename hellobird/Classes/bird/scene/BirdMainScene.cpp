//
// Created by LinusLan on 2018/2/8.
//

#include "BirdMainScene.h"
bool BirdMainScene::init() {
    if(!Scene::init()) {
        return false;
    }
    UserDefault::getInstance()->setIntegerForKey("score", 0);
    UserDefault::getInstance()->setBoolForKey("isAlive", true);
    UserDefault::getInstance()->setIntegerForKey("scoreIdx", -1);
    Size winSize = Director::getInstance()->getWinSize();
    BirdMainLayer* mainLayer = BirdMainLayer::create();
    //mainLayer->setAnchorPoint(Vec2(0, 0));
    //mainLayer->setPosition(Vec2(0, 0));
    this->addChild(mainLayer);
    return true;
}