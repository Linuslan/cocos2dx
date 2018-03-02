//
// Created by LinusLan on 2018/3/1.
//

#ifndef PROJ_ANDROID_STUDIO_WEAPON_H
#define PROJ_ANDROID_STUDIO_WEAPON_H

#include "cocos2d.h"
USING_NS_CC;
class Weapon : public Sprite {
protected:
    SpriteFrameCache* sfc;
public:
    virtual bool init();
    CREATE_FUNC(Weapon);
    virtual void stand();
    virtual void fight();
    virtual void walk();
};
#endif //PROJ_ANDROID_STUDIO_WEAPON_H
