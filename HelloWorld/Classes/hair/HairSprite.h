//
// Created by LinusLan on 2018/3/5.
//

#ifndef PROJ_ANDROID_STUDIO_HAIRSPRITE_H
#define PROJ_ANDROID_STUDIO_HAIRSPRITE_H

#include "cocos2d.h"
#include "HeroAnimation.h"
USING_NS_CC;
class HairSprite : public Sprite {
public:
    virtual bool init();
    CREATE_FUNC(HairSprite);
    virtual HeroAnimation* stand();
    virtual HeroAnimation* walk();
    virtual HeroAnimation* fight();
};
#endif //PROJ_ANDROID_STUDIO_HAIRSPRITE_H
