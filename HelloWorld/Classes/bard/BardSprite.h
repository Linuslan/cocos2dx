//
// Created by LinusLan on 2018/3/5.
//

#ifndef PROJ_ANDROID_STUDIO_BARDSPRITE_H
#define PROJ_ANDROID_STUDIO_BARDSPRITE_H

#include "HeroAnimation.h"
#include "cocos2d.h"
USING_NS_CC;
class BardSprite : public Sprite {
public:
    virtual bool init();
    CREATE_FUNC(BardSprite);
    virtual HeroAnimation* stand();
    virtual HeroAnimation* walk();
    virtual HeroAnimation* fight();
};
#endif //PROJ_ANDROID_STUDIO_BARDSPRITE_H
