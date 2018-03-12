//
// Created by LinusLan on 2018/3/12.
//

#ifndef PROJ_ANDROID_STUDIO_HERO_H
#define PROJ_ANDROID_STUDIO_HERO_H

#include "RoleSprite.h"
#include "HeroAnimation.h"
#include "HeroAnimate.h"
#include "TileMapLayer.h"
USING_NS_CC;
class HeroSprite : public RoleSprite {
public:
    virtual bool init();
    CREATE_FUNC(HeroSprite);
    void walk(double degree);
    void stand();
    void update(float a);
};

#endif //PROJ_ANDROID_STUDIO_HERO_H
