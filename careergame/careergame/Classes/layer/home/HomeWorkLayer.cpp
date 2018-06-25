//
// Created by LinusLan on 2018/6/22.
//

#include "HomeWorkLayer.h"
bool HomeWorkLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* sprite = Sprite::create("images/home/home_work_bg.png");
    this->addChild(sprite);
    sprite->setPosition(winSize/2);
    return true;
}