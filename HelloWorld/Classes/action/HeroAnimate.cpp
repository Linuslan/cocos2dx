//
// Created by LinusLan on 2018/3/2.
//

#include "HeroAnimate.h"
HeroAnimate* HeroAnimate::create(Animation* animation) {
    HeroAnimate* animate = new (std::nothrow) HeroAnimate();
    if (animate && animate->initWithAnimation(animation))
    {
        animate->autorelease();
        return animate;
    }

    delete animate;
    return nullptr;
}

HeroAnimate::HeroAnimate() {
    actions = new std::vector<HeroAnimation*> ();
}

HeroAnimate::~HeroAnimate() {
    std::vector<HeroAnimation*>::iterator iter;
    for(iter = actions->begin(); iter != actions->end(); iter ++) {
        //delete *iter;
        CC_SAFE_RELEASE(*iter);
    }
    delete actions;
}

void HeroAnimate::addAction(HeroAnimation *animation) {
    this->actions->push_back(animation);
}

void HeroAnimate::update(float a) {
    Animate::update(a);
    int index = this->getCurrentFrameIndex();
    std::vector<HeroAnimation*>::iterator iter;
    for(iter = actions->begin(); iter != actions->end(); iter ++) {
        HeroAnimation* animation = *iter;
        Sprite* sprite = animation->getTarget();
        Vector<AnimationFrame*> frames = animation->getFrames();
        if(frames.size() > index) {
            AnimationFrame* frame = frames.at(index);
            SpriteFrame* spriteFrame = frame->getSpriteFrame();
            sprite->setSpriteFrame(spriteFrame);
        }
    }
}