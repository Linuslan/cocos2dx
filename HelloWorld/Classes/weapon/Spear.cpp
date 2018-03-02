//
// Created by LinusLan on 2018/3/1.
//
#include "Spear.h"
bool Spear::init() {
    if(!Sprite::init()) {
        return false;
    }
    this->sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("role-stand.plist", "role-stand.png");
    this->createWithSpriteFrameName("");
    return true;
}

void Spear::stand() {
    Vector<SpriteFrame*> weaponFrames;
    weaponFrames.pushBack(sfc->getSpriteFrameByName("Weapon-1-1.png"));
    weaponFrames.pushBack(sfc->getSpriteFrameByName("Weapon-1-2.png"));
    weaponFrames.pushBack(sfc->getSpriteFrameByName("Weapon-1-3.png"));
    weaponFrames.pushBack(sfc->getSpriteFrameByName("Weapon-1-4.png"));
    Animation* animation = Animation::createWithSpriteFrames(weaponFrames, 0.17f);
    Animate* animate = Animate::create(animation);
    animate->setTag(3);
    this->runAction(RepeatForever::create(animate));
}

void Spear::fight() {
    Vector<SpriteFrame*> frames;
    frames.pushBack(sfc->getSpriteFrameByName("role-1.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-10.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-11.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-12.png"));
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.17f);
    Animate* animate = Animate::create(animation);
    animate->setTag(1);
    this->runAction(RepeatForever::create(animate));
}

void Spear::walk() {
    Vector<SpriteFrame*> frames;
    frames.pushBack(sfc->getSpriteFrameByName("role-1.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-10.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-11.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-12.png"));
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.17f);
    Animate* animate = Animate::create(animation);
    animate->setTag(1);
    this->runAction(RepeatForever::create(animate));
}
