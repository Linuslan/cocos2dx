//
// Created by LinusLan on 2018/2/24.
//

#include "MoveSprite.h"

bool MoveSprite::init() {
    if(!Sprite::init()) {
        return false;
    }
    this->setPosition(50, 50);
    this->setTexture("tilemap/move_nav.png");
    EventListenerTouchAllAtOnce* moveListener = EventListenerTouchAllAtOnce::create();
    moveListener->onTouchesBegan = CC_CALLBACK_2(MoveSprite::onMoveTouchesBegan, this);
    moveListener->onTouchesMoved = CC_CALLBACK_2(MoveSprite::onMoveTouchesMoved, this);
    moveListener->onTouchesEnded = CC_CALLBACK_2(MoveSprite::onMoveTouchesEnded, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(moveListener, this);

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
            event->stopPropagation();
            return;
        }
        Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this->getParent());
    }
    log("move started");
}

void MoveSprite::onMoveTouchesMoved(const std::vector<Touch *> &touches, Event *event) {
    log("moved");
}

void MoveSprite::onMoveTouchesEnded(const std::vector<Touch *> &touches, Event *event) {
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent());
    log("move ended");
}