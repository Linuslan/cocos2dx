//
// Created by LinusLan on 2018/6/13.
//

#include "RoleSprite.h"
bool RoleSprite::init() {
    log("进入角色初始化方法");
    if(!Sprite::init()) {
        return false;
    }
    try {
        log("开始初始化角色");
        SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
        sfc->addSpriteFramesWithFile("images/role/walk/role.plist", "images/role/walk/role.png");
        this->standFront();
        this->setName("role-11");
    } catch(std::exception& ex) {
        log("初始化角色异常，%s", ex.what());
    }
    return true;
}

void RoleSprite::standFront() {
    this->stopAllActionsByTag(2);
    Vector<SpriteFrame*> frames;
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    SpriteFrame* frame = sfc->getSpriteFrameByName("stand-front.png");
    this->setSpriteFrame(frame);
}

void RoleSprite::standBack() {
    this->stopAllActionsByTag(2);
    Vector<SpriteFrame*> frames;
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    SpriteFrame* frame = sfc->getSpriteFrameByName("stand-back.png");
    this->setSpriteFrame(frame);
}

void RoleSprite::standSide() {
    //log("开始侧面站立");
    //this->stopAllActionsByTag(2);
    this->stopAllActions();
    Vector<SpriteFrame*> frames;
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    SpriteFrame* frame = sfc->getSpriteFrameByName("stand-side.png");
    this->setSpriteFrame(frame);
}

void RoleSprite::walk() {
    this->stopAllActions();
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    Vec2 targetPos = this->targetObj->getPosition();
    float x = targetPos.x;
    float y = targetPos.y;
    Vec2 rolePos = this->getPosition();
    if(x < rolePos.x) {
        this->setFlippedX(false);
    } else {
        this->setFlippedX(true);
    }
    Vector<SpriteFrame*> frames;
    for(int i = 1; i < 9; i ++) {
        frames.pushBack(sfc->getSpriteFrameByName(StringUtils::format("%d.png", i)));
    }
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.10f);
    Animate* animate = Animate::create(animation);
    RepeatForever* action = RepeatForever::create(animate);
    action->setTag(2);
    this->runAction(action);
    scheduleUpdate();
}

void RoleSprite::update(float t) {
    try {
        float step = 0.5;
        float x = this->getPosition().x + step;
        if(targetObj == nullptr || nullptr == targetBtn) {
            return;
        }
        Vec2 targetPos = targetObj->getPosition();
        if(targetPos.x < this->getPosition().x) {
            x = this->getPosition().x - step;
        }
        if(this->getBoundingBox().intersectsRect(targetObj->getBoundingBox())) {
            this->standSide();
            this->callback();
            targetObj = nullptr;
            targetBtn = nullptr;
            this->targetBtn->callback();
            return;
        }
        this->setPosition(x, targetPos.y);
    } catch(const char* msg) {
        log("异常:%s", msg);
    } catch(std::exception& ex) {
        log("获取参数异常：%s", ex.what());
    }
}