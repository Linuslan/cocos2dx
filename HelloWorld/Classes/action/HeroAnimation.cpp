//
// Created by LinusLan on 2018/3/2.
//

#include "HeroAnimation.h"
HeroAnimation* HeroAnimation::createWithSpriteFrames(const Vector<SpriteFrame *> &arrayOfSpriteFrameNames, float delay, unsigned int loops) {
    HeroAnimation* animation = new (std::nothrow) HeroAnimation();
    animation->initWithSpriteFrames(arrayOfSpriteFrameNames, delay, loops);
    animation->autorelease();
    animation->retain();
    AnimationCache::getInstance()->addAnimation(animation, "spearStand");

    animation->setId(999);
    //animation->autorelease();
    return animation;
}

HeroAnimation::HeroAnimation() {
    log("HeroAnimation Constructing");
}

HeroAnimation::~HeroAnimation() {
    log("HeroAnimation Destructing");
    /*if(frames) {
        std::vector<AnimationFrame*>::iterator iter;
        for(iter = frames->begin(); iter != frames->end(); iter ++) {
            CC_SAFE_RELEASE(*iter);
        }
        delete frames;
    }*/
}

void HeroAnimation::setTarget(Sprite *sprite) {
    this->target = sprite;
    this->target->retain();
}

Sprite* HeroAnimation::getTarget() {
    return this->target;
}