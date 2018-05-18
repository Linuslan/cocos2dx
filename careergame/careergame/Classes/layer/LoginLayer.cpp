//
// Created by LinusLan on 2018/5/18.
//

#include "LoginLayer.h"
bool LoginLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* bg = Sprite::create("images/login.jpg");
    this->addChild(bg);
    return true;
}
