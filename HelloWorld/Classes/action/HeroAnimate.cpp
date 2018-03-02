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
    log("~HeroAnimate");
    std::vector<HeroAnimation*>::iterator iter;
    for(iter = actions->begin(); iter != actions->end(); iter ++) {
        CC_SAFE_RELEASE((*iter));
    }
    delete actions;
}

void HeroAnimate::addAction(HeroAnimation *animation) {
    this->actions->push_back(animation);
    log("HeroAnimate 子动作数：%d", actions->size());
    Vector<AnimationFrame*> vector = animation->getFrames();
    log("HeroAnimate get frames size:%d", vector.size());
}

void HeroAnimate::update(float a) {
    log("HeroAnimate update start");
    Animate::update(a);
    int index = this->getCurrentFrameIndex();
    log("HeroAnimate current frame index: %d, 子动作数：%d", index, actions->size());
    Vector<AnimationFrame*> frames = actions->at(0)->getFrames();
    log("HeroAnimate get frames, first size:%d", frames.size());
    std::vector<HeroAnimation*>::iterator iter;
    for(iter = actions->begin(); iter != actions->end(); iter ++) {
        HeroAnimation* animation = *iter;
        log("HeroAnimate loop start");
        Weapon* sprite = static_cast<Weapon*> (animation->getTarget());
        log("HeroAnimate get target");
        Vector<AnimationFrame*> frames = animation->getFrames();
        log("HeroAnimate get frames, size:%d", frames.size());
        if(frames.size() > index) {
            AnimationFrame* frame = frames.at(index);
            log("HeroAnimate get frames index");
            sprite->setSpriteFrame(frame->getSpriteFrame());
            log("HeroAnimate loop end");
        }
    }
    log("HeroAnimate update end");
}