//
// Created by LinusLan on 2018/7/19.
//

#include "MoveLayer2.h"
#include <ui/UIButton.h>
#include "MoveLayer.h"
#include "RoleSprite.h"
bool MoveLayer2::init() {
    if(!Layer::init()) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    ui::Button* turnLeftBtn = ui::Button::create("images/common/move/turnLeftLight.png");
    turnLeftBtn->setPosition(Vec2(winSize.width*0.05, winSize.height*0.2));
    this->addChild(turnLeftBtn);
    turnLeftBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type){
        RoleSprite* role = static_cast<RoleSprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map")->getChildByName("role-11"));
        if(type == ui::Widget::TouchEventType::BEGAN) {
            role->setFlippedX(false);
            role->walk();
            log("开始移动");
            schedule(schedule_selector(MoveLayer2::doGoLeft));
        } else if(type == ui::Widget::TouchEventType::MOVED) {
            log("移动中");
        } else if(type == ui::Widget::TouchEventType::ENDED) {
            role->standSide();
            unschedule(schedule_selector(MoveLayer2::doGoLeft));
            log("移动结束");
        }
    });

    ui::Button* turnUpBtn = ui::Button::create("images/common/move/turnUpLight.png");
    turnUpBtn->setPosition(Vec2(winSize.width*0.115, winSize.height*0.3));
    this->addChild(turnUpBtn);
    turnUpBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type) {
        RoleSprite* role = static_cast<RoleSprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map")->getChildByName("role-11"));
        if(type == ui::Widget::TouchEventType::BEGAN) {
            //role->setFlippedX(true);
            role->walkUp();
            log("开始移动");
            schedule(schedule_selector(MoveLayer2::doGoUp));
        } else if(type == ui::Widget::TouchEventType::MOVED) {
            log("移动中");
        } else if(type == ui::Widget::TouchEventType::ENDED) {
            role->standBack();
            unschedule(schedule_selector(MoveLayer2::doGoUp));
            log("移动结束");
        }
    });

    ui::Button* turnRightBtn = ui::Button::create("images/common/move/turnRightLight.png");
    turnRightBtn->setPosition(Vec2(winSize.width*0.18, winSize.height*0.2));
    this->addChild(turnRightBtn);
    turnRightBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type) {
        RoleSprite* role = static_cast<RoleSprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map")->getChildByName("role-11"));
        if(type == ui::Widget::TouchEventType::BEGAN) {
            role->setFlippedX(true);
            role->walk();
            log("开始移动");
            schedule(schedule_selector(MoveLayer2::doGoRight));
        } else if(type == ui::Widget::TouchEventType::MOVED) {
            log("移动中");
        } else if(type == ui::Widget::TouchEventType::ENDED) {
            role->standSide();
            unschedule(schedule_selector(MoveLayer2::doGoRight));
            log("移动结束");
        }
    });

    ui::Button* turnDownBtn = ui::Button::create("images/common/move/turnDownLight.png");
    this->addChild(turnDownBtn);
    turnDownBtn->setPosition(Vec2(winSize.width*0.115, winSize.height*0.1));
    turnDownBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type) {
        RoleSprite* role = static_cast<RoleSprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map")->getChildByName("role-11"));
        if(type == ui::Widget::TouchEventType::BEGAN) {
            //role->setFlippedX(true);
            role->walkDown();
            log("开始移动");
            schedule(schedule_selector(MoveLayer2::doGoDown));
        } else if(type == ui::Widget::TouchEventType::MOVED) {
            log("移动中");
        } else if(type == ui::Widget::TouchEventType::ENDED) {
            role->standFront();
            unschedule(schedule_selector(MoveLayer2::doGoDown));
            log("移动结束");
        }
    });
    return true;
}

void MoveLayer2::doGoLeft(float t) {
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* map = static_cast<Sprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map"));
    RoleSprite* role = static_cast<RoleSprite*>(map->getChildByName("role-11"));
    role->setPosition(Vec2(role->getPosition().x-5, role->getPosition().y));
    Size size = this->moveSize(role->getPosition());
    map->setPosition(Vec2(map->getPosition().x-size.width, map->getPosition().y));
}

void MoveLayer2::doGoRight(float t) {
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* map = static_cast<Sprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map"));
    RoleSprite* role = static_cast<RoleSprite*>(map->getChildByName("role-11"));
    role->setPosition(Vec2(role->getPosition().x+5, role->getPosition().y));
    Size size = this->moveSize(role->getPosition());
    map->setPosition(Vec2(map->getPosition().x-size.width, map->getPosition().y));
}

void MoveLayer2::doGoUp(float t) {
    /*Size winSize = Director::getInstance()->getWinSize();
    Sprite* map = static_cast<Sprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map"));
    RoleSprite* role = static_cast<RoleSprite*>(map->getChildByName("role-11"));
    role->setPosition(Vec2(role->getPosition().x-5, role->getPosition().y));
    Size size = this->moveSize(role->getPosition());
    map->setPosition(Vec2(map->getPosition().x+size.width, map->getPosition().y+size.height));*/
}

void MoveLayer2::doGoDown(float t) {
    /*Size winSize = Director::getInstance()->getWinSize();
    Sprite* map = static_cast<Sprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map"));
    RoleSprite* role = static_cast<RoleSprite*>(map->getChildByName("role-11"));
    role->setPosition(Vec2(role->getPosition().x-5, role->getPosition().y));
    Size size = this->moveSize(role->getPosition());
    map->setPosition(Vec2(map->getPosition().x+size.width, map->getPosition().y+size.height));*/
}

Vec2 MoveLayer2::parseSysCoordToMapCoord(Vec2 vec2) {
    log("物体原坐标为：x=%f, y=%f", vec2.x, vec2.y);
    Sprite* map = static_cast<Sprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map"));
    Size mapSize = map->getContentSize();
    Vec2 mapPosition = map->getPosition();
    log("地图中心宽为：mapSize.width/2=%f, 物体相对地图的坐标为：vec2.x=%f", mapSize.width/2, vec2.x);
    float xDiff = mapSize.width/2-vec2.x;
    log("地图中心到物体坐标的水平距离为：%f", xDiff);
    float x = mapPosition.x - xDiff;
    log("得到物体相对于屏幕的x坐标为：%f", x);

    log("地图中心宽为：mapSize.height/2=%f, 物体相对地图的坐标为：vec2.y=%f", mapSize.height/2, vec2.y);
    float yDiff = mapSize.height/2-vec2.y;
    log("地图中心到物体坐标的垂直距离为：%f", yDiff);
    float y = mapPosition.y - yDiff;
    log("得到物体相对于屏幕的y坐标为：%f", y);
    return Vec2(x, y);
}

Size MoveLayer2::moveSize(Vec2 vec2) {
    Size winSize = Director::getInstance()->getWinSize();
    Vec2 pos = this->parseSysCoordToMapCoord(vec2);
    log("得到的系统坐标为：x=%f, y=%f", pos.x, pos.y);
    float width = pos.x-winSize.width/2;
    float height = pos.y-winSize.height/2;
    log("需要移动的距离为：width=%f, height=%f", width, height);
    return Size(width, height);
}