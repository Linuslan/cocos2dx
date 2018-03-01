//
// Created by LinusLan on 2018/3/1.
//

#ifndef PROJ_ANDROID_STUDIO_WEAPON_H
#define PROJ_ANDROID_STUDIO_WEAPON_H

#include "cocos2d.h"
USING_NS_CC;
class Weapon : public Sprite {
public:
    virtual bool init();
    CREATE_FUNC(Weapon);
};
#endif //PROJ_ANDROID_STUDIO_WEAPON_H
