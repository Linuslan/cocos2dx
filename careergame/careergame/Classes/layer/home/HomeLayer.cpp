//
// Created by LinusLan on 2018/5/22.
//

#include "HomeLayer.h"
bool HomeLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    try {
        Size winSize = Director::getInstance()->getWinSize();
        Sprite* bg = Sprite::create("images/scene/002.jpg");
        //bg->setScale(0.5);
        bg->setPosition(winSize/2);
        this->addChild(bg);
    } catch(std::exception& ex) {
        log("初始化家框架异常，%s", ex.what());
    }
    return true;
}