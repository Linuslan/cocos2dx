//
// Created by LinusLan on 2018/7/18.
//

#include <ui/UIButton.h>
#include "MoveLayer.h"
#include "RoleSprite.h"
bool MoveLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    ui::Button* turnLeftBtn = ui::Button::create("images/common/move/turnLeftLight.png");
    turnLeftBtn->setPosition(Vec2(winSize.width*0.05, winSize.height*0.2));
    this->addChild(turnLeftBtn);
    turnLeftBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type){
        RoleSprite* role = static_cast<RoleSprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("role-11"));
        if(type == ui::Widget::TouchEventType::BEGAN) {
            role->setFlippedX(false);
            role->walk();
            log("开始移动");
            schedule(schedule_selector(MoveLayer::doGoLeft));
        } else if(type == ui::Widget::TouchEventType::MOVED) {
            log("移动中");
        } else if(type == ui::Widget::TouchEventType::ENDED) {
            role->standSide();
            unschedule(schedule_selector(MoveLayer::doGoLeft));
            log("移动结束");
        }
    });

    ui::Button* turnUpBtn = ui::Button::create("images/common/move/turnUpLight.png");
    turnUpBtn->setPosition(Vec2(winSize.width*0.115, winSize.height*0.3));
    this->addChild(turnUpBtn);

    ui::Button* turnRightBtn = ui::Button::create("images/common/move/turnRightLight.png");
    turnRightBtn->setPosition(Vec2(winSize.width*0.18, winSize.height*0.2));
    this->addChild(turnRightBtn);
    turnRightBtn->addTouchEventListener([](Ref* ref, ui::Widget::TouchEventType type) {
        RoleSprite* role = static_cast<RoleSprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("role-11"));
        if(type == ui::Widget::TouchEventType::BEGAN) {
            role->setFlippedX(true);
            role->walk();
            log("开始移动");
            schedule(schedule_selector(MoveLayer::doGoRight));
        } else if(type == ui::Widget::TouchEventType::MOVED) {
            log("移动中");
        } else if(type == ui::Widget::TouchEventType::ENDED) {
            role->standSide();
            unschedule(schedule_selector(MoveLayer::doGoRight));
            log("移动结束");
        }
    });

    ui::Button* turnDownBtn = ui::Button::create("images/common/move/turnDownLight.png");
    this->addChild(turnDownBtn);
    turnDownBtn->setPosition(Vec2(winSize.width*0.115, winSize.height*0.1));

    return true;
}

void MoveLayer::doGoLeft(float t) {
    RoleSprite* role = static_cast<RoleSprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("role-11"));
    Sprite* sprite = static_cast<Sprite*>(this->getParent()->getChildByName("map")->getChildByName("mapBg"));
    int roleToMap = sprite->getContentSize().width/2 - sprite->getPosition().x;
    log("地图宽：width/2=%f, 地图坐标x=%f", sprite->getContentSize().width/2, sprite->getPosition().x);
    if(roleToMap>=5) {
        sprite->setPosition(sprite->getPosition().x+5, sprite->getPosition().y);
        log("场景坐标：x=%f, y=%f", sprite->getPosition().x, sprite->getPosition().y);
    } else if(roleToMap > 0) {
        sprite->setPosition(sprite->getPosition().x+roleToMap, sprite->getPosition().y);
    } else {
        if(role->getPosition().x-5>0) {
            role->setPosition(Vec2(role->getPosition().x-5, role->getPosition().y));
        }
    }
}

void MoveLayer::doGoRight(float t) {
    Size winSize = Director::getInstance()->getWinSize();
    RoleSprite* role = static_cast<RoleSprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("role-11"));
    Sprite* sprite = static_cast<Sprite*>(this->getParent()->getChildByName("map")->getChildByName("mapBg"));
    int mapDiff = sprite->getContentSize().width/2 + sprite->getPosition().x;
    log("地图宽：width/2=%f, 地图坐标x=%f", sprite->getContentSize().width/2, sprite->getPosition().x);
    if(mapDiff<=sprite->getContentSize().width) {
        sprite->setPosition(sprite->getPosition().x-5, sprite->getPosition().y);
        log("场景坐标：x=%f, y=%f", sprite->getPosition().x, sprite->getPosition().y);
    } else {
        if(role->getPosition().x+5>winSize.width) {
            role->setPosition(Vec2(role->getPosition().x+5, role->getPosition().y));
        }
    }
}