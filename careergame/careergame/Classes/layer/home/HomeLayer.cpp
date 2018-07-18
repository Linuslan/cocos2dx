//
// Created by LinusLan on 2018/5/22.
//

#include "HomeLayer.h"
#include "HomeComputerBtn.h"
#include "KitchenTableBtn.h"
bool HomeLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    try {
        this->setName("HomeLayer");
        Size winSize = Director::getInstance()->getWinSize();
        log("winSize.width=%f, winSize.height=%f, 开始创建角色", winSize.width, winSize.height);
        RoleSprite* role = RoleSprite::create();
        role->setLocalZOrder(10);
        role->setPosition(Vec2(winSize.width*0.26, winSize.height*0.3));
        role->standFront();
        this->addChild(role);
        Sprite* bg = Sprite::create("images/home/home.png");
        Size bgSize = bg->getContentSize();
        log("bgSize.width=%f, bgSize.height=%f", bgSize.width, bgSize.height);
        //bg->setScale(0.5);
        bg->setPosition(winSize/2);
        this->addChild(bg);
        HomeComputerBtn* computer = HomeComputerBtn::create();
        //computer->setPosition(Vec2(winSize.width*0.026, winSize.height*0.35));
        computer->setPosition(Vec2(winSize.width*0.5, winSize.height*0.18));
        this->addChild(computer);

        KitchenTableBtn* kitchenTable = KitchenTableBtn::create();
        kitchenTable->setPosition(Vec2(winSize.width*0.05, winSize.height*0.95));
        this->addChild(kitchenTable);
        /*ui::Button* chair = ui::Button::create("test/home_chair.png");
        chair->setPosition(Vec2(winSize.width*0.1, winSize.height*0.33));
        this->addChild(chair);

        ui::Button* door = ui::Button::create("test/home_door.png");
        door->setPosition(Vec2(winSize.width*0.26, winSize.height*0.48));
        this->addChild(door);

        ui::Button* cabinet = ui::Button::create("test/home_cabinet.png");
        cabinet->setPosition(Vec2(winSize.width*0.55, winSize.height*0.45));
        this->addChild(cabinet);

        ui::Button* bed = ui::Button::create("test/home_bed.png");
        bed->setPosition(Vec2(winSize.width*0.87, winSize.height*0.33));
        this->addChild(bed);

        ui::Button* window = ui::Button::create("test/home_window.png");
        window->setPosition(Vec2(winSize.width*0.85, winSize.height*0.65));
        this->addChild(window);

        ui::Button* airConditioner = ui::Button::create("test/home_air_conditioner.png");
        airConditioner->setPosition(Vec2(winSize.width*0.014, winSize.height*0.65));
        this->addChild(airConditioner);*/

    } catch(std::exception& ex) {
        log("初始化家框架异常，%s", ex.what());
    }
    return true;
}