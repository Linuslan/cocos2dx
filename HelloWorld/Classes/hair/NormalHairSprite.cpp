//
// Created by LinusLan on 2018/3/5.
//

#include "NormalHairSprite.h"

HeroAnimation* NormalHairSprite::stand() {
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*>* spriteFrames = new Vector<SpriteFrame*>();
    for(int i = 0; i < 4; i ++) {
        spriteFrames->pushBack(sfc->getSpriteFrameByName(StringUtils::format("hair-stand-%d.png", (i+1))));
    }
    HeroAnimation* animation = HeroAnimation::createWithSpriteFrames(*spriteFrames);
    animation->setName("Normal hair stand animation");
    delete spriteFrames;
    animation->setTarget(this);
    return animation;
}

HeroAnimation* NormalHairSprite::walk() {
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*>* spriteFrames = new Vector<SpriteFrame*>();
    for(int i = 0; i < 8; i ++) {
        spriteFrames->pushBack(sfc->getSpriteFrameByName(StringUtils::format("hair-walk-%d.png", (i+1))));
    }
    HeroAnimation* animation = HeroAnimation::createWithSpriteFrames(*spriteFrames);
    animation->setName("Normal hair walk animation");
    delete spriteFrames;
    animation->setTarget(this);
    return animation;
}