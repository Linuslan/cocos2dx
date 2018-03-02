//
// Created by LinusLan on 2018/3/2.
//

#include "HeroAnimation.h"
HeroAnimation* HeroAnimation::createWithSpriteFrames(const Vector<SpriteFrame *> &arrayOfSpriteFrameNames, float delay, unsigned int loops) {
    HeroAnimation* animation = new (std::nothrow) HeroAnimation();
    animation->initWithSpriteFrames(arrayOfSpriteFrameNames, delay, loops);
    animation->autorelease();

    return animation;
}

void HeroAnimation::setTarget(Sprite *sprite) {
    this->target = sprite;
}

Sprite* HeroAnimation::getTarget() {
    return this->target;
}