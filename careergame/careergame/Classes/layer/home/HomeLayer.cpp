//
// Created by LinusLan on 2018/5/22.
//

#include "HomeLayer.h"
#include "HomeComputerBtn.h"
#include "KitchenTableBtn.h"
#include "HomeBedBtn.h"
bool HomeLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    try {
        this->setName("mainLayer");
        Size winSize = Director::getInstance()->getWinSize();
        log("winSize.width=%f, winSize.height=%f, 开始创建角色", winSize.width, winSize.height);

        Sprite* bg = Sprite::create("images/home/home.png");
        bg->setName("map");
        Size bgSize = bg->getContentSize();
        log("bgSize.width=%f, bgSize.height=%f", bgSize.width, bgSize.height);
        bg->setPosition(winSize/2);
        this->addChild(bg);

        RoleSprite* role = RoleSprite::create();
        role->setName("role-11");
        role->setLocalZOrder(10);
        role->setPosition(Vec2(bgSize.width*0.5, bgSize.height*0.3));
        role->standFront();
        bg->addChild(role);

        HomeComputerBtn* computer = HomeComputerBtn::create();
        computer->setPosition(Vec2(bgSize.width*0.45, bgSize.height*0.18));
        bg->addChild(computer);

        KitchenTableBtn* kitchenTable = KitchenTableBtn::create();
        kitchenTable->setPosition(Vec2(bgSize.width*0.11, bgSize.height*0.35));
        bg->addChild(kitchenTable);

        HomeBedBtn* bed = HomeBedBtn::create();
        bed->setPosition(Vec2(bgSize.width*0.885, bgSize.height*0.305));
        bg->addChild(bed);


    } catch(std::exception& ex) {
        log("初始化家框架异常，%s", ex.what());
    }
    return true;
}