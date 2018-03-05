//
// Created by LinusLan on 2018/3/1.
//
#include "Spear.h"

HeroAnimation* Spear::stand() {
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> weaponFrames;
    for(int i = 0; i < 4; i ++) {
        weaponFrames.pushBack(sfc->getSpriteFrameByName(StringUtils::format("weapon-stand-%d.png", (i+1))));
    }
    HeroAnimation* animation = HeroAnimation::createWithSpriteFrames(weaponFrames, 0.17f);
    animation->setName("Spear stand animation");
    animation->setTarget(this);
    return animation;
}

HeroAnimation* Spear::walk() {
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> weaponFrames;
    for(int i = 0; i < 4; i ++) {
        weaponFrames.pushBack(sfc->getSpriteFrameByName(StringUtils::format("weapon-walk-%d.png", (i+1))));
    }
    HeroAnimation* animation = HeroAnimation::createWithSpriteFrames(weaponFrames, 0.17f);
    animation->setName("Spear walk animation");
    animation->setTarget(this);
    return animation;
}