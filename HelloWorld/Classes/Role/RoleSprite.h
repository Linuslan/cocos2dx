//
// Created by LinusLan on 2018/3/12.
//

#ifndef PROJ_ANDROID_STUDIO_ROLESPRITE_H
#define PROJ_ANDROID_STUDIO_ROLESPRITE_H

#include "cocos2d.h"
#include "NormalHairSprite.h"
#include "Spear.h"
#include "WhiteBardSprite.h"
USING_NS_CC;
class RoleSprite : public Sprite {
protected:
    std::string name;
    std::string resource;
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    Weapon* weapon;
    BardSprite* bard;
    HairSprite* hair;
    bool flippedX = false;
    bool flippedY = false;
public:
    virtual bool init();
    CREATE_FUNC(RoleSprite);
    virtual void walk(double degree);
    virtual void stand();
    virtual void update(float a);
};
#endif //PROJ_ANDROID_STUDIO_ROLESPRITE_H
