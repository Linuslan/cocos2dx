//
// Created by LinusLan on 2018/2/24.
//

#include "MoveSprite.h"

bool MoveSprite::init() {
    if(!Sprite::init()) {
        return false;
    }
    this->setPosition(200, 150);
    this->setTexture("tilemap/move_nav.png");
    EventListenerTouchAllAtOnce* moveListener = EventListenerTouchAllAtOnce::create();
    moveListener->onTouchesBegan = CC_CALLBACK_2(MoveSprite::onMoveTouchesBegan, this);
    moveListener->onTouchesMoved = CC_CALLBACK_2(MoveSprite::onMoveTouchesMoved, this);
    moveListener->onTouchesEnded = CC_CALLBACK_2(MoveSprite::onMoveTouchesEnded, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(moveListener, this);
    Sprite* icon = Sprite::create("tilemap/move_icon.png");
    icon->setPosition(this->getContentSize()/2);
    this->addChild(icon);
    icon->setTag(111);
    return true;
}

void MoveSprite::onMoveTouchesBegan(const std::vector<Touch *> &touches, Event *event) {
    if(touches.size() == 1) {
        Touch* touch = touches[0];
        Vec2 vec2 = touch->getLocation();
        Size size = this->getContentSize();
        float startedX = this->getPositionX()-size.width/2;
        float startedY = this->getPositionY()-size.height/2;
        float endedX = startedX + size.width;
        float endedY = startedY + size.height;
        log("vec2.x=%f, vec2.y=%f, startX=%f, startY=%f, endX=%f, endY=%f, size.width=%f, size.height=%f",
            vec2.x, vec2.y, startedX, startedY, endedX, endedY, size.width, size.height);
        if(vec2.x < startedX || vec2.x > endedX || vec2.y < startedY || vec2.y > endedY) {
            //event->stopPropagation();
            Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
            return;
        }
        Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this->getParent());
        Sprite* sprite = static_cast<Sprite*>(this->getChildByTag(111));
        Vec2 touchLocation = touches[0]->getLocation();
        float x = touchLocation.x - this->getPositionX();
        float y = touchLocation.y - this->getPositionY();
        sprite->setPosition(sprite->getPosition()+Vec2(x, y));
    }
    log("move started");
}

void MoveSprite::onMoveTouchesMoved(const std::vector<Touch *> &touches, Event *event) {
    float diameter = 140.0;  //圆的直径
    Touch* touch = touches[0];
    Vec2 vec = touch->getLocation();
    log("touch.x=%f, touch.y=%f", vec.x, vec.y);
    Vec2 circleVec = this->getPosition();
    //log("circle.x=%f, circle.y=%f",circleVec.x, circleVec.y);
    //求原点到触摸点间的距离
    double distance = sqrt((vec.y-circleVec.y)*(vec.y-circleVec.y) + (vec.x-circleVec.x)*(vec.x-circleVec.x));
    log("distance=%lf", distance);
    Sprite* sprite = static_cast<Sprite*>(this->getChildByTag(111));
    Vec2 pointVec = sprite->getPosition();
    //double distance = sqrt((pointVec.y-circleVec.y)*(pointVec.y-circleVec.y) + (pointVec.x-circleVec.x)*(pointVec.x-circleVec.x));
    if(distance <= diameter/2) {
        //log("touch: distance=%lf, diameter/2=%lf", distance, (diameter/2));
        //sprite->setPosition(sprite->getPosition()+touch->getDelta());
        //sprite->setPosition(vec);
        float x = vec.x - this->getPositionX();
        float y = vec.y - this->getPositionY();
        log("sprite.x=%f, sprite.y=%f", x, y);
        sprite->setPosition(Vec2(this->getContentSize()/2)+Vec2(x, y));
    } else {
        //触点超出时，按照移动的范围，在圆的边缘进行移动
        float radius = diameter/2;
        float x = radius*(vec.x-this->getPositionX())/distance;
        float y = radius*(vec.y-this->getPositionY())/distance;
        log("over circle x=%f, y=%f", x, y);
        sprite->setPosition(Vec2(this->getContentSize()/2)+Vec2(x,y));
    }
    log("moved");
}

void MoveSprite::onMoveTouchesEnded(const std::vector<Touch *> &touches, Event *event) {
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent());
    Sprite* sprite = static_cast<Sprite*>(this->getChildByTag(111));
    sprite->setPosition(this->getContentSize()/2);
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
    log("move ended");
}