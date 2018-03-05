//
// Created by LinusLan on 2018/3/5.
//

#ifndef PROJ_ANDROID_STUDIO_NORMALHAIR_H
#define PROJ_ANDROID_STUDIO_NORMALHAIR_H

#include "HeroAnimation.h"
#include "HairSprite.h"
class NormalHairSprite : public HairSprite {
public:
    CREATE_FUNC(NormalHairSprite);
    HeroAnimation* stand();
    //HeroAnimation* fight();
    HeroAnimation* walk();
};
#endif //PROJ_ANDROID_STUDIO_NORMALHAIR_H
