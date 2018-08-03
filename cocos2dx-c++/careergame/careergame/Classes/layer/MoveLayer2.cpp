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
    //this->setName("moveLayer");
    Size winSize = Director::getInstance()->getWinSize();
    ui::Button* turnLeftBtn = ui::Button::create("images/common/move/turnLeftLight.png");
    turnLeftBtn->setPosition(Vec2(winSize.width*0.05, winSize.height*0.2));
    this->addChild(turnLeftBtn);
    turnLeftBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type){
        RoleSprite* role = static_cast<RoleSprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map")->getChildByName("role-11"));
        if(type == ui::Widget::TouchEventType::BEGAN) {
            role->setFlippedX(false);
            role->walk();
            //log("开始移动");
            schedule(schedule_selector(MoveLayer2::doGoLeft));
        } else if(type == ui::Widget::TouchEventType::MOVED) {
            //log("移动中");
        } else if(type == ui::Widget::TouchEventType::ENDED) {
            role->standSide();
            unschedule(schedule_selector(MoveLayer2::doGoLeft));
            //log("移动结束");
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
            //log("开始移动");
            schedule(schedule_selector(MoveLayer2::doGoUp));
        } else if(type == ui::Widget::TouchEventType::MOVED) {
            //log("移动中");
        } else if(type == ui::Widget::TouchEventType::ENDED) {
            role->standBack();
            unschedule(schedule_selector(MoveLayer2::doGoUp));
            //log("移动结束");
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
            //log("开始移动");
            schedule(schedule_selector(MoveLayer2::doGoRight));
        } else if(type == ui::Widget::TouchEventType::MOVED) {
            //log("移动中");
        } else if(type == ui::Widget::TouchEventType::ENDED) {
            role->standSide();
            unschedule(schedule_selector(MoveLayer2::doGoRight));
            //log("移动结束");
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
            //log("开始移动");
            schedule(schedule_selector(MoveLayer2::doGoDown));
        } else if(type == ui::Widget::TouchEventType::MOVED) {
            //log("移动中");
        } else if(type == ui::Widget::TouchEventType::ENDED) {
            role->standFront();
            unschedule(schedule_selector(MoveLayer2::doGoDown));
            //log("移动结束");
        }
    });
    return true;
}

void MoveLayer2::doGoLeft(float t) {
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* map = static_cast<Sprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map"));
    RoleSprite* role = static_cast<RoleSprite*>(map->getChildByName("role-11"));
    //log("角色zOrder=%d", role->getLocalZOrder());
    Vector<Node*> nodes = map->getChildren();
    bool stop = false;
    for(Vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter ++) {
        Node* node = *iter;
        //log("当前物体为：%s", node->getName().c_str());
        if(node->getName() == role->getName()){
            continue;
        }
        //log("判断物体与角色是否相交");
        Node* building = node->getChildByName("building");
        Node* mask = node->getChildByName("mask");
        if(mask == nullptr) {
            //log("物体无遮罩区域");
        }
        if(building) {
            float buildingX = building->getPosition().x;
            float buildingY = building->getPosition().y;
            float buildingPosX = node->getPosition().x-(node->getContentSize().width/2-buildingX);
            float buildingPosY = node->getPosition().y-(node->getContentSize().height/2-buildingY);
            //log("================打印建筑位置信息===============");
            /*log("node.size.width/2=%f, node.x=%f, node.size.height/2=%f,"
                        " node.y=%f, buildingX=%f, buildingY=%f, buildingPosX=%f, buildingPosY=%f"
                    , node->getContentSize().width/2, node->getPosition().x, node->getContentSize().height/2, node->getPosition().y
                    , buildingX, buildingY, buildingPosX, buildingPosY);
            log("预计建筑的位置为：x=%f, y=%f, width=%f, height=%f",
                buildingPosX-building->getContentSize().width/2,
                buildingPosY-building->getContentSize().height/2,
                building->getContentSize().width,
                building->getContentSize().height);*/
            Rect buildingRect(buildingPosX-building->getContentSize().width/2,
                              buildingPosY-building->getContentSize().height/2,
                              building->getContentSize().width,
                              building->getContentSize().height);
            /*log("建筑的位置为：x=%f, y=%f, x2=%f, y2=%f",
                buildingRect.getMinX(), buildingRect.getMinY(), buildingRect.getMaxX(), buildingRect.getMaxY());
            log("角色的位置为：x=%f, y=%f, x2=%f, y2=%f", role->getBoundingBox().getMinX()
                    , role->getBoundingBox().getMinY(), role->getBoundingBox().getMaxX()
                    , role->getBoundingBox().getMaxY());*/
            if(buildingRect.intersectsRect(role->getBoundingBox())
                    && buildingRect.getMinX() < role->getBoundingBox().getMaxX() - 5) {
                //log("物体与不可碰撞区域相交");
                stop = true;
                break;
            }
        } else {
            //log("物体最小x=%f, 角色最大x=%f", node->getBoundingBox().getMinX(), role->getBoundingBox().getMaxX() - 5);
            if(node->getBoundingBox().intersectsRect(role->getBoundingBox())
               && node->getBoundingBox().getMinX() < role->getBoundingBox().getMaxX() - 5) {
                stop = true;
                break;
            }
        }
        if(mask) {
            float maskX = mask->getPosition().x;
            float maskY = mask->getPosition().y;
            float maskPosX = node->getPosition().x-(node->getContentSize().width/2-maskX);
            float maskPosY = node->getPosition().y-(node->getContentSize().height/2-maskY);
            /*log("================打印遮罩位置信息===============");
            log("node.size.width/2=%f, node.x=%f, node.size.height/2=%f,"
                        " node.y=%f, maskX=%f, maskY=%f, maskPosX=%f, maskPosY=%f"
                    , node->getContentSize().width/2, node->getPosition().x, node->getContentSize().height/2, node->getPosition().y
                    , maskX, maskY, maskPosX, maskPosY);
            log("预计遮罩的位置为：x=%f, y=%f, width=%f, height=%f",
                maskPosX-mask->getContentSize().width/2,
                maskPosY-mask->getContentSize().height/2,
                mask->getContentSize().width,
                mask->getContentSize().height);*/
            Rect maskRect(maskPosX-mask->getContentSize().width/2,
                          maskPosY-mask->getContentSize().height/2,
                          mask->getContentSize().width,
                          mask->getContentSize().height);
            /*log("遮罩的位置为：x=%f, y=%f, x2=%f, y2=%f",
                maskRect.getMinX(), maskRect.getMinY(), maskRect.getMaxX(), maskRect.getMaxY());
            log("角色的位置为：x=%f, y=%f, x2=%f, y2=%f", role->getBoundingBox().getMinX()
                    , role->getBoundingBox().getMinY(), role->getBoundingBox().getMaxX()
                    , role->getBoundingBox().getMaxY());*/
            if(maskRect.intersectsRect(role->getBoundingBox())) {
                //log("物体与遮罩区域相交");
                //mask->setLocalZOrder(role->getLocalZOrder()+1);
                map->reorderChild(node, role->getLocalZOrder()+1);
                break;
            } else {
                //log("物体zOrder=%d", node->getLocalZOrder());
                map->reorderChild(node, role->getLocalZOrder()-1);
                //log("排序后物体zOrder=%d", node->getLocalZOrder());
            }
        } else {
            //log("物体zOrder=%d", node->getLocalZOrder());
            map->reorderChild(node, role->getLocalZOrder()-1);
            //log("排序后物体zOrder=%d", node->getLocalZOrder());
        }
        /*if(role->getBoundingBox().intersectsRect(node->getBoundingBox())) {

        }*/
    }
    if(stop || role->getPosition().x <= 0) {
        return ;
    }
    role->setPosition(Vec2(role->getPosition().x-5, role->getPosition().y));
    Size size = this->moveSize(role->getPosition());
    if(map->getPosition().x >= map->getContentSize().width/2) {
        return ;
    }
    if(map->getContentSize().width/2-map->getPosition().x + winSize.width >= map->getContentSize().width) {
        if(map->getContentSize().width - role->getPosition().x < winSize.width/2) {
            return ;
        }
    }
    map->setPosition(Vec2(map->getPosition().x-size.width, map->getPosition().y));
}

void MoveLayer2::doGoRight(float t) {
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* map = static_cast<Sprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map"));
    RoleSprite* role = static_cast<RoleSprite*>(map->getChildByName("role-11"));
    //log("角色zOrder=%d", role->getLocalZOrder());
    Vector<Node*> nodes = map->getChildren();
    bool stop = false;
    for(Vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter ++) {
        Node* node = *iter;
        //log("当前物体为：%s", node->getName().c_str());
        if(node->getName() == role->getName()){
            continue;
        }
        //log("判断物体与角色是否相交");
        Node* building = node->getChildByName("building");
        Node* mask = node->getChildByName("mask");
        if(mask == nullptr) {
            //log("物体无遮罩区域");
        }
        if(building) {
            float buildingX = building->getPosition().x;
            float buildingY = building->getPosition().y;
            float buildingPosX = node->getPosition().x-(node->getContentSize().width/2-buildingX);
            float buildingPosY = node->getPosition().y-(node->getContentSize().height/2-buildingY);
            /*log("================打印建筑位置信息===============");
            log("node.size.width/2=%f, node.x=%f, node.size.height/2=%f,"
                        " node.y=%f, buildingX=%f, buildingY=%f, buildingPosX=%f, buildingPosY=%f"
                    , node->getContentSize().width/2, node->getPosition().x, node->getContentSize().height/2, node->getPosition().y
                    , buildingX, buildingY, buildingPosX, buildingPosY);
            log("预计建筑的位置为：x=%f, y=%f, width=%f, height=%f",
                buildingPosX-building->getContentSize().width/2,
                buildingPosY-building->getContentSize().height/2,
                building->getContentSize().width,
                building->getContentSize().height);*/
            Rect buildingRect(buildingPosX-building->getContentSize().width/2,
                              buildingPosY-building->getContentSize().height/2,
                              building->getContentSize().width,
                              building->getContentSize().height);
            /*log("建筑的位置为：x=%f, y=%f, x2=%f, y2=%f",
                buildingRect.getMinX(), buildingRect.getMinY(), buildingRect.getMaxX(), buildingRect.getMaxY());
            log("角色的位置为：x=%f, y=%f, x2=%f, y2=%f", role->getBoundingBox().getMinX()
                    , role->getBoundingBox().getMinY(), role->getBoundingBox().getMaxX()
                    , role->getBoundingBox().getMaxY());*/
            if(buildingRect.intersectsRect(role->getBoundingBox())
                    && buildingRect.getMaxX() > role->getBoundingBox().getMinX() + 5) {
                //log("物体与不可碰撞区域相交");
                stop = true;
                break;
            }
        } else {
            if(node->getBoundingBox().intersectsRect(role->getBoundingBox())
               && node->getBoundingBox().getMaxX() > role->getBoundingBox().getMinX() + 5) {
                stop = true;
                break;
            }
        }
        if(mask) {
            float maskX = mask->getPosition().x;
            float maskY = mask->getPosition().y;
            float maskPosX = node->getPosition().x-(node->getContentSize().width/2-maskX);
            float maskPosY = node->getPosition().y-(node->getContentSize().height/2-maskY);
            /*log("================打印遮罩位置信息===============");
            log("node.size.width/2=%f, node.x=%f, node.size.height/2=%f,"
                        " node.y=%f, maskX=%f, maskY=%f, maskPosX=%f, maskPosY=%f"
                    , node->getContentSize().width/2, node->getPosition().x, node->getContentSize().height/2, node->getPosition().y
                    , maskX, maskY, maskPosX, maskPosY);
            log("预计遮罩的位置为：x=%f, y=%f, width=%f, height=%f",
                maskPosX-mask->getContentSize().width/2,
                maskPosY-mask->getContentSize().height/2,
                mask->getContentSize().width,
                mask->getContentSize().height);*/
            Rect maskRect(maskPosX-mask->getContentSize().width/2,
                          maskPosY-mask->getContentSize().height/2,
                          mask->getContentSize().width,
                          mask->getContentSize().height);
            /*log("遮罩的位置为：x=%f, y=%f, x2=%f, y2=%f",
                maskRect.getMinX(), maskRect.getMinY(), maskRect.getMaxX(), maskRect.getMaxY());
            log("角色的位置为：x=%f, y=%f, x2=%f, y2=%f", role->getBoundingBox().getMinX()
                    , role->getBoundingBox().getMinY(), role->getBoundingBox().getMaxX()
                    , role->getBoundingBox().getMaxY());*/
            if(maskRect.intersectsRect(role->getBoundingBox())) {
                //log("物体与遮罩区域相交");
                //mask->setLocalZOrder(role->getLocalZOrder()+1);
                map->reorderChild(node, role->getLocalZOrder()+1);
                break;
            } else {
                //log("物体zOrder=%d", node->getLocalZOrder());
                map->reorderChild(node, role->getLocalZOrder()-1);
                //log("排序后物体zOrder=%d", node->getLocalZOrder());
            }
        } else {
            //log("物体zOrder=%d", node->getLocalZOrder());
            map->reorderChild(node, role->getLocalZOrder()-1);
            //log("排序后物体zOrder=%d", node->getLocalZOrder());
        }
        /*if(role->getBoundingBox().intersectsRect(node->getBoundingBox())) {

        }*/
    }
    if(stop || role->getPosition().x >= map->getContentSize().width) {
        return ;
    }
    role->setPosition(Vec2(role->getPosition().x+5, role->getPosition().y));
    Size size = this->moveSize(role->getPosition());
    /*if(winSize.width-map->getPosition().x >= map->getContentSize().width/2) {
        return ;
    }*/
    if(map->getContentSize().width/2-map->getPosition().x + winSize.width >= map->getContentSize().width) {
        return ;
    }
    if(map->getPosition().x >= map->getContentSize().width/2) {
        if(role->getPosition().x <= winSize.width/2) {
            return ;
        }
    }

    map->setPosition(Vec2(map->getPosition().x-size.width, map->getPosition().y));
}

void MoveLayer2::doGoUp(float t) {
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* map = static_cast<Sprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map"));
    RoleSprite* role = static_cast<RoleSprite*>(map->getChildByName("role-11"));
    //log("角色zOrder=%d", role->getLocalZOrder());
    Vector<Node*> nodes = map->getChildren();
    bool stop = false;
    for(Vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter ++) {
        Node* node = *iter;
        //log("当前物体为：%s", node->getName().c_str());
        if(node->getName() == role->getName()){
            continue;
        }
        //log("判断物体与角色是否相交");
        Node* building = node->getChildByName("building");
        Node* mask = node->getChildByName("mask");
        if(mask == nullptr) {
            //log("物体无遮罩区域");
        }
        if(building) {
            float buildingX = building->getPosition().x;
            float buildingY = building->getPosition().y;
            float buildingPosX = node->getPosition().x-(node->getContentSize().width/2-buildingX);
            float buildingPosY = node->getPosition().y-(node->getContentSize().height/2-buildingY);
            /*log("================打印建筑位置信息===============");
            log("node.size.width/2=%f, node.x=%f, node.size.height/2=%f,"
                        " node.y=%f, buildingX=%f, buildingY=%f, buildingPosX=%f, buildingPosY=%f"
                    , node->getContentSize().width/2, node->getPosition().x, node->getContentSize().height/2, node->getPosition().y
                    , buildingX, buildingY, buildingPosX, buildingPosY);
            log("预计建筑的位置为：x=%f, y=%f, width=%f, height=%f",
                buildingPosX-building->getContentSize().width/2,
                buildingPosY-building->getContentSize().height/2,
                building->getContentSize().width,
                building->getContentSize().height);*/
            Rect buildingRect(buildingPosX-building->getContentSize().width/2,
                              buildingPosY-building->getContentSize().height/2,
                              building->getContentSize().width,
                              building->getContentSize().height);
            /*log("建筑的位置为：x=%f, y=%f, x2=%f, y2=%f",
                buildingRect.getMinX(), buildingRect.getMinY(), buildingRect.getMaxX(), buildingRect.getMaxY());
            log("角色的位置为：x=%f, y=%f, x2=%f, y2=%f", role->getBoundingBox().getMinX()
                    , role->getBoundingBox().getMinY(), role->getBoundingBox().getMaxX()
                    , role->getBoundingBox().getMaxY());*/
            if(buildingRect.intersectsRect(role->getBoundingBox())
                    && buildingRect.getMaxY() > role->getBoundingBox().getMinY() + 5) {
                //log("物体与不可碰撞区域相交");
                stop = true;
                break;
            }
        } else {
            if(node->getBoundingBox().intersectsRect(role->getBoundingBox())
               && node->getBoundingBox().getMaxY() > role->getBoundingBox().getMinY() + 5) {
                stop = true;
                break;
            }
        }
        if(mask) {
            float maskX = mask->getPosition().x;
            float maskY = mask->getPosition().y;
            float maskPosX = node->getPosition().x-(node->getContentSize().width/2-maskX);
            float maskPosY = node->getPosition().y-(node->getContentSize().height/2-maskY);
            /*log("================打印遮罩位置信息===============");
            log("node.size.width/2=%f, node.x=%f, node.size.height/2=%f,"
                        " node.y=%f, maskX=%f, maskY=%f, maskPosX=%f, maskPosY=%f"
                    , node->getContentSize().width/2, node->getPosition().x, node->getContentSize().height/2, node->getPosition().y
                    , maskX, maskY, maskPosX, maskPosY);
            log("预计遮罩的位置为：x=%f, y=%f, width=%f, height=%f",
                maskPosX-mask->getContentSize().width/2,
                maskPosY-mask->getContentSize().height/2,
                mask->getContentSize().width,
                mask->getContentSize().height);*/
            Rect maskRect(maskPosX-mask->getContentSize().width/2,
                          maskPosY-mask->getContentSize().height/2,
                          mask->getContentSize().width,
                          mask->getContentSize().height);
            /*log("遮罩的位置为：x=%f, y=%f, x2=%f, y2=%f",
                maskRect.getMinX(), maskRect.getMinY(), maskRect.getMaxX(), maskRect.getMaxY());
            log("角色的位置为：x=%f, y=%f, x2=%f, y2=%f", role->getBoundingBox().getMinX()
                    , role->getBoundingBox().getMinY(), role->getBoundingBox().getMaxX()
                    , role->getBoundingBox().getMaxY());*/
            if(maskRect.intersectsRect(role->getBoundingBox())) {
                //log("物体与遮罩区域相交");
                //mask->setLocalZOrder(role->getLocalZOrder()+1);
                map->reorderChild(node, role->getLocalZOrder()+1);
                break;
            } else {
                //log("物体zOrder=%d", node->getLocalZOrder());
                map->reorderChild(node, role->getLocalZOrder()-1);
                //log("排序后物体zOrder=%d", node->getLocalZOrder());
            }
        } else {
            //log("物体zOrder=%d", node->getLocalZOrder());
            map->reorderChild(node, role->getLocalZOrder()-1);
            //log("排序后物体zOrder=%d", node->getLocalZOrder());
        }
        /*if(role->getBoundingBox().intersectsRect(node->getBoundingBox())) {

        }*/
    }
    if(stop || role->getPosition().y >= map->getContentSize().height
            || role->getPosition().y >= this->unwalkableY) {
        return ;
    }
    role->setPosition(Vec2(role->getPosition().x, role->getPosition().y+5));
    Size size = this->moveSize(role->getPosition());
    if(map->getContentSize().height/2-map->getPosition().y + winSize.height >= map->getContentSize().height) {
        return ;
    }
    if(map->getPosition().y >= map->getContentSize().height/2) {
        if(role->getPosition().y <= winSize.height/2) {
            return ;
        }
    }

    map->setPosition(Vec2(map->getPosition().x, map->getPosition().y-size.height));
}

void MoveLayer2::doGoDown(float t) {
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* map = static_cast<Sprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map"));
    RoleSprite* role = static_cast<RoleSprite*>(map->getChildByName("role-11"));
    //log("角色zOrder=%d", role->getLocalZOrder());
    Vector<Node*> nodes = map->getChildren();
    bool stop = false;
    for(Vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter ++) {
        Node* node = *iter;
        //log("当前物体为：%s", node->getName().c_str());
        if(node->getName() == role->getName()){
            continue;
        }
        //log("判断物体与角色是否相交");
        Node* building = node->getChildByName("building");
        Node* mask = node->getChildByName("mask");
        if(mask == nullptr) {
            //log("物体无遮罩区域");
        }
        if(building) {
            float buildingX = building->getPosition().x;
            float buildingY = building->getPosition().y;
            float buildingPosX = node->getPosition().x-(node->getContentSize().width/2-buildingX);
            float buildingPosY = node->getPosition().y-(node->getContentSize().height/2-buildingY);
            /*log("================打印建筑位置信息===============");
            log("node.size.width/2=%f, node.x=%f, node.size.height/2=%f,"
                        " node.y=%f, buildingX=%f, buildingY=%f, buildingPosX=%f, buildingPosY=%f"
                    , node->getContentSize().width/2, node->getPosition().x, node->getContentSize().height/2, node->getPosition().y
                    , buildingX, buildingY, buildingPosX, buildingPosY);
            log("预计建筑的位置为：x=%f, y=%f, width=%f, height=%f",
                buildingPosX-building->getContentSize().width/2,
                buildingPosY-building->getContentSize().height/2,
                building->getContentSize().width,
                building->getContentSize().height);*/
            Rect buildingRect(buildingPosX-building->getContentSize().width/2,
                              buildingPosY-building->getContentSize().height/2,
                              building->getContentSize().width,
                              building->getContentSize().height);
            /*log("建筑的位置为：x=%f, y=%f, x2=%f, y2=%f",
                buildingRect.getMinX(), buildingRect.getMinY(), buildingRect.getMaxX(), buildingRect.getMaxY());
            log("角色的位置为：x=%f, y=%f, x2=%f, y2=%f", role->getBoundingBox().getMinX()
                    , role->getBoundingBox().getMinY(), role->getBoundingBox().getMaxX()
                    , role->getBoundingBox().getMaxY());*/
            if(buildingRect.intersectsRect(role->getBoundingBox())
                    && buildingRect.getMinY() < role->getBoundingBox().getMaxY() - 5) {
                //log("物体与不可碰撞区域相交");
                stop = true;
                break;
            }
        } else {
            if(node->getBoundingBox().intersectsRect(role->getBoundingBox())
               && node->getBoundingBox().getMinY() < role->getBoundingBox().getMaxY() - 5) {
                stop = true;
                break;
            }
        }
        if(mask) {
            float maskX = mask->getPosition().x;
            float maskY = mask->getPosition().y;
            float maskPosX = node->getPosition().x-(node->getContentSize().width/2-maskX);
            float maskPosY = node->getPosition().y-(node->getContentSize().height/2-maskY);
            /*log("================打印遮罩位置信息===============");
            log("node.size.width/2=%f, node.x=%f, node.size.height/2=%f,"
                        " node.y=%f, maskX=%f, maskY=%f, maskPosX=%f, maskPosY=%f"
                    , node->getContentSize().width/2, node->getPosition().x, node->getContentSize().height/2, node->getPosition().y
                    , maskX, maskY, maskPosX, maskPosY);
            log("预计遮罩的位置为：x=%f, y=%f, width=%f, height=%f",
                maskPosX-mask->getContentSize().width/2,
                maskPosY-mask->getContentSize().height/2,
                mask->getContentSize().width,
                mask->getContentSize().height);*/
            Rect maskRect(maskPosX-mask->getContentSize().width/2,
                          maskPosY-mask->getContentSize().height/2,
                          mask->getContentSize().width,
                          mask->getContentSize().height);
            /*log("遮罩的位置为：x=%f, y=%f, x2=%f, y2=%f",
                maskRect.getMinX(), maskRect.getMinY(), maskRect.getMaxX(), maskRect.getMaxY());
            log("角色的位置为：x=%f, y=%f, x2=%f, y2=%f", role->getBoundingBox().getMinX()
                    , role->getBoundingBox().getMinY(), role->getBoundingBox().getMaxX()
                    , role->getBoundingBox().getMaxY());*/
            if(maskRect.intersectsRect(role->getBoundingBox())) {
                //log("物体与遮罩区域相交");
                //mask->setLocalZOrder(role->getLocalZOrder()+1);
                map->reorderChild(node, role->getLocalZOrder()+1);
                break;
            } else {
                //log("物体zOrder=%d", node->getLocalZOrder());
                map->reorderChild(node, role->getLocalZOrder()-1);
                //log("排序后物体zOrder=%d", node->getLocalZOrder());
            }
        } else {
            //log("物体zOrder=%d", node->getLocalZOrder());
            map->reorderChild(node, role->getLocalZOrder()-1);
            //log("排序后物体zOrder=%d", node->getLocalZOrder());
        }
        /*if(role->getBoundingBox().intersectsRect(node->getBoundingBox())) {

        }*/
    }
    if(stop || role->getPosition().y <= 0) {
        return ;
    }
    role->setPosition(Vec2(role->getPosition().x, role->getPosition().y-5));
    Size size = this->moveSize(role->getPosition());
    if(map->getPosition().y >= map->getContentSize().height/2) {
        return ;
    }
    if(map->getContentSize().height/2-map->getPosition().y + winSize.height >= map->getContentSize().height) {
        if(map->getContentSize().height - role->getPosition().y < winSize.height/2) {
            return ;
        }
    }
    map->setPosition(Vec2(map->getPosition().x, map->getPosition().y-size.height));
}

Vec2 MoveLayer2::parseSysCoordToMapCoord(Vec2 vec2) {
    //log("物体原坐标为：x=%f, y=%f", vec2.x, vec2.y);
    Sprite* map = static_cast<Sprite*>(this->getParent()->getChildByName("mainLayer")->getChildByName("map"));
    Size mapSize = map->getContentSize();
    Vec2 mapPosition = map->getPosition();
    //log("地图中心宽为：mapSize.width/2=%f, 物体相对地图的坐标为：vec2.x=%f", mapSize.width/2, vec2.x);
    float xDiff = mapSize.width/2-vec2.x;
    //log("地图中心到物体坐标的水平距离为：%f", xDiff);
    float x = mapPosition.x - xDiff;
    //log("得到物体相对于屏幕的x坐标为：%f", x);

    //log("地图中心宽为：mapSize.height/2=%f, 物体相对地图的坐标为：vec2.y=%f", mapSize.height/2, vec2.y);
    float yDiff = mapSize.height/2-vec2.y;
    //log("地图中心到物体坐标的垂直距离为：%f", yDiff);
    float y = mapPosition.y - yDiff;
    //log("得到物体相对于屏幕的y坐标为：%f", y);
    return Vec2(x, y);
}

Size MoveLayer2::moveSize(Vec2 vec2) {
    Size winSize = Director::getInstance()->getWinSize();
    Vec2 pos = this->parseSysCoordToMapCoord(vec2);
    //log("得到的系统坐标为：x=%f, y=%f", pos.x, pos.y);
    float width = pos.x-winSize.width/2;
    float height = pos.y-winSize.height/2;
    //log("需要移动的距离为：width=%f, height=%f", width, height);
    return Size(width, height);
}