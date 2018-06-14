//
// Created by LinusLan on 2018/6/13.
//

#include "RoleSprite.h"
bool RoleSprite::init() {
    if(Sprite::init()) {
        return false;
    }
    try {
        log("开始初始化角色");
        SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
        sfc->addSpriteFramesWithFile("images/role/walk/role.plist", "images/role/walk/role.png");
    } catch(std::exception& ex) {
        log("初始化角色异常，%s", ex.what());
    }
    return true;
}

void RoleSprite::standFront() {
    this->stopAllActions();
    Vector<SpriteFrame*> frames;
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    frames.pushBack(sfc->getSpriteFrameByName("stand-front.png"));
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.17f);
}