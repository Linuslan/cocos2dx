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
        ui::Button* computer = ui::Button::create("test/home_computer.png");
        computer->setPosition(Vec2(winSize.width*0.026, winSize.height*0.35));
        this->addChild(computer);
        computer->addClickEventListener([this](Ref* ref){
            log("点击了电脑");
        });

        ui::Button* chair = ui::Button::create("test/home_chair.png");
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
        this->addChild(airConditioner);
        log("开始创建角色");
        RoleSprite* role = RoleSprite::create();
        role->setPosition(Vec2(winSize.width*0.26, winSize.height*0.3));
        role->standFront();
        this->addChild(role);
        Vec2 pos = computer->getPosition();
        role->walk(pos);
    } catch(std::exception& ex) {
        log("初始化家框架异常，%s", ex.what());
    }
    return true;
}