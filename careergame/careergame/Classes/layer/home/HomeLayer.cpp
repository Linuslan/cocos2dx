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
        Sprite* bg = Sprite::create("test/home_wall.png");
        //bg->setScale(0.5);
        bg->setPosition(winSize/2);
        this->addChild(bg);
        Sprite* computer = Sprite::create("test/home_computer.png");
        computer->setPosition(Vec2(winSize.width*0.026, winSize.height*0.35));
        this->addChild(computer);
        Sprite* chair = Sprite::create("test/home_chair.png");
        chair->setPosition(Vec2(winSize.width*0.026, winSize.height*0.35));
    } catch(std::exception& ex) {
        log("初始化家框架异常，%s", ex.what());
    }
    return true;
}