//
// Created by LinusLan on 2018/3/5.
//

#include "WhiteBardSprite.h"

HeroAnimation* WhiteBardSprite::stand() {
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*>* spriteFrames = new Vector<SpriteFrame*>();
    for(int i = 0; i < 4; i ++) {
        spriteFrames->pushBack(sfc->getSpriteFrameByName(StringUtils::format("bard-stand-%d.png", (i+1))));
    }
    HeroAnimation* animation = HeroAnimation::createWithSpriteFrames(*spriteFrames);
    animation->setName("White bard");
    delete spriteFrames;
    animation->setTarget(this);
    return animation;
}