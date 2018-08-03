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
    turnUpBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type) {
        RoleSprite* role = static_cast<RoleSprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("role-11"));
        if(type == ui::Widget::TouchEventType::BEGAN) {
            //role->setFlippedX(true);
            role->walkUp();
            log("开始移动");
            schedule(schedule_selector(MoveLayer::doGoUp));
        } else if(type == ui::Widget::TouchEventType::MOVED) {
            log("移动中");
        } else if(type == ui::Widget::TouchEventType::ENDED) {
            role->standBack();
            unschedule(schedule_selector(MoveLayer::doGoUp));
            log("移动结束");
        }
    });

    ui::Button* turnRightBtn = ui::Button::create("images/common/move/turnRightLight.png");
    turnRightBtn->setPosition(Vec2(winSize.width*0.18, winSize.height*0.2));
    this->addChild(turnRightBtn);
    turnRightBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type) {
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
    turnDownBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type) {
        RoleSprite* role = static_cast<RoleSprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("role-11"));
        if(type == ui::Widget::TouchEventType::BEGAN) {
            //role->setFlippedX(true);
            role->walkDown();
            log("开始移动");
            schedule(schedule_selector(MoveLayer::doGoDown));
        } else if(type == ui::Widget::TouchEventType::MOVED) {
            log("移动中");
        } else if(type == ui::Widget::TouchEventType::ENDED) {
            role->standFront();
            unschedule(schedule_selector(MoveLayer::doGoDown));
            log("移动结束");
        }
    });
    return true;
}

void MoveLayer::doGoLeft(float t) {
    Size winSize = Director::getInstance()->getWinSize();
    RoleSprite* role = static_cast<RoleSprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("role-11"));
    Sprite* sprite = static_cast<Sprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map"));
    int roleToMap = sprite->getContentSize().width/2 - sprite->getPosition().x;
    log("地图宽：width/2=%f, 地图坐标x=%f", sprite->getContentSize().width/2, sprite->getPosition().x);
    if(role->getPosition().x > winSize.width/2) {
        role->setPosition(Vec2(role->getPosition().x-5, role->getPosition().y));
    } else if(roleToMap>=5) {
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
    Sprite* sprite = static_cast<Sprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map"));
    int mapDiff = winSize.width-sprite->getPosition().x;  //sprite.position.x为地图的中心原点距离屏幕的左边界的距离
    log("地图宽：width/2=%f, 地图坐标x=%f, 屏幕宽：winSize.width/2=%f", sprite->getContentSize().width/2, sprite->getPosition().x, winSize.width/2);
    if(role->getPosition().x<winSize.width/2) {
        role->setPosition(Vec2(role->getPosition().x+5, role->getPosition().y));
    } else if(mapDiff<=sprite->getContentSize().width/2) {
        sprite->setPosition(sprite->getPosition().x-5, sprite->getPosition().y);
        log("场景坐标：x=%f, y=%f", sprite->getPosition().x, sprite->getPosition().y);
    } else {
        if(role->getPosition().x+5<=winSize.width) {
            role->setPosition(Vec2(role->getPosition().x+5, role->getPosition().y));
        }
    }
}

void MoveLayer::doGoUp(float t) {
    Size winSize = Director::getInstance()->getWinSize();
    RoleSprite* role = static_cast<RoleSprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("role-11"));
    Sprite* sprite = static_cast<Sprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map"));
    int mapDiff = winSize.height-sprite->getPosition().y;  //sprite.position.x为地图的中心原点距离屏幕的左边界的距离
    log("地图宽：height/2=%f, 地图坐标x=%f, 屏幕宽：winSize.width/2=%f", sprite->getContentSize().height/2, sprite->getPosition().y, winSize.height/2);
    /*if(role->getPosition().y<winSize.height/2) {
        role->setPosition(Vec2(role->getPosition().x, role->getPosition().y+5));
    } else*/ if(mapDiff<=sprite->getContentSize().height/2) {
        sprite->setPosition(sprite->getPosition().x, sprite->getPosition().y-5);
        log("场景坐标：x=%f, y=%f", sprite->getPosition().x, sprite->getPosition().y);
    } else {
        if(role->getPosition().y+5<=winSize.height*0.4) {
            role->setPosition(Vec2(role->getPosition().x, role->getPosition().y+5));
        }
    }
}

void MoveLayer::doGoDown(float t) {
    Size winSize = Director::getInstance()->getWinSize();
    RoleSprite* role = static_cast<RoleSprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("role-11"));
    Sprite* sprite = static_cast<Sprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map"));
    int roleToMap = sprite->getContentSize().height/2 - sprite->getPosition().y;
    log("地图宽：width/2=%f, 地图坐标x=%f", sprite->getContentSize().width/2, sprite->getPosition().x);
    Vector<Node*> nodes = sprite->getChildren();
    bool stop = false;
    for(Vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter ++) {
        Node* node = *iter;
        log("判断物体与角色是否相交");
        log("有物体与角色相交");
        Node* building = node->getChildByName("building");
        Node* mask = node->getChildByName("mask");
        if(building && building->getBoundingBox().intersectsRect(role->getBoundingBox())) {
            log("物体与不可碰撞区域相交");
            stop = true;
            break;
        }
        if(mask && mask->getBoundingBox().intersectsRect(role->getBoundingBox())) {
            log("物体与遮罩区域相交");
            //mask->setLocalZOrder(role->getLocalZOrder()+1);
            this->getParent()->getChildByName("mainLayer")
                    ->reorderChild(node, role->getLocalZOrder()+1);
            break;
        }
        /*if(role->getBoundingBox().intersectsRect(node->getBoundingBox())) {

        }*/
    }
    if(stop) {
        return;
    }
    if(role->getPosition().y > winSize.height/2) {
        role->setPosition(Vec2(role->getPosition().x, role->getPosition().y-5));
    } else if(roleToMap>=5) {
        sprite->setPosition(sprite->getPosition().x, sprite->getPosition().y+5);
        log("场景坐标：x=%f, y=%f", sprite->getPosition().x, sprite->getPosition().y);
    } else if(roleToMap > 0) {
        sprite->setPosition(sprite->getPosition().x, sprite->getPosition().y+roleToMap);
    } else {
        if(role->getPosition().y-5>0) {
            role->setPosition(Vec2(role->getPosition().x, role->getPosition().y-5));
        }
    }
}

void MoveLayer::setTargetPosition(Vec2 vec2) {
    x = vec2.x;
    y = vec2.y;
}

void MoveLayer::autoWalk() {
    Size winSize = Director::getInstance()->getWinSize();
    RoleSprite* role = static_cast<RoleSprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("role-11"));
    if(x < winSize.width/2) {
        role->setFlippedX(false);
    } else {
        role->setFlippedX(true);
    }
}

Vec2 MoveLayer::parseSysCoordToMapCoord(Vec2 vec2) {
    Sprite* map = static_cast<Sprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map"));
    Size mapSize = map->getContentSize();

}