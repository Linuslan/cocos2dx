//
// Created by LinusLan on 2018/3/2.
//

#ifndef PROJ_ANDROID_STUDIO_HEROANIMATE_H
#define PROJ_ANDROID_STUDIO_HEROANIMATE_H

#include "cocos2d.h"
#include "HeroAnimation.h"
#include "Weapon.h"
USING_NS_CC;
class HeroAnimate : public Animate {
private:
    std::vector<HeroAnimation*>* actions;
public:
    static HeroAnimate* create(Animation* animation);
    HeroAnimate();
    ~HeroAnimate();
    void update(float a);
    void addAction(HeroAnimation* animation);
};
#endif //PROJ_ANDROID_STUDIO_HEROANIMATE_H
