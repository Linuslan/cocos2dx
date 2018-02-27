//
// Created by LinusLan on 2018/2/27.
//

#include "HeroSprite.h"
bool HeroSprite::init() {
    if(!Sprite::init()) {
        return false;
    }
    sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("tilemap/role.plist", "tilemap/role.png");
    this->createWithSpriteFrameName("role-1.png");
    scheduleUpdate();
    return true;
}

void HeroSprite::stand() {
    this->stopAllActions();
    Vector<SpriteFrame*> frames;
    frames.pushBack(sfc->getSpriteFrameByName("role-1.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-10.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-11.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-12.png"));
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.17f);
    Animate* animate = Animate::create(animation);
    this->runAction(RepeatForever::create(animate));
}

void HeroSprite::walk() {
    this->stopAllActions();
    Vector<SpriteFrame*> frames;
    for(int i = 2; i < 10; i ++) {
        frames.pushBack(sfc->getSpriteFrameByName(StringUtils::format("role-%d.png", i)));
    }
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.13f);
    Animate* animate = Animate::create(animation);
    /*MoveBy* move = MoveBy::create(10.0f, Vec2(100, 0));
    Spawn* spawn = Spawn::create(animate, move, nullptr);*/
    this->runAction(RepeatForever::create(animate));
}

void HeroSprite::update(float t) {
    this->setPosition(this->getPositionX()+1.7, this->getPositionY());
}
