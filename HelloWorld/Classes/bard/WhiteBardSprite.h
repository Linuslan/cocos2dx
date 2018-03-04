//
// Created by LinusLan on 2018/3/5.
//

#ifndef PROJ_ANDROID_STUDIO_WHITEBARD_H
#define PROJ_ANDROID_STUDIO_WHITEBARD_H

#include "BardSprite.h"
#include "HeroAnimation.h"
class WhiteBardSprite : public BardSprite {
public:
    CREATE_FUNC(WhiteBardSprite);
    HeroAnimation* stand();
    //HeroAnimation* walk();
    //HeroAnimation* fight();
};
#endif //PROJ_ANDROID_STUDIO_WHITEBARD_H
