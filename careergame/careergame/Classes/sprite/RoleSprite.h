//
// Created by LinusLan on 2018/6/13.
//

#ifndef PROJ_ANDROID_STUDIO_ROLESPRITE_H
#define PROJ_ANDROID_STUDIO_ROLESPRITE_H

#include "cocos2d.h"
USING_NS_CC;
class RoleSprite : public Sprite {
public:
    virtual bool init();
    CREATE_FUNC(RoleSprite);
    void walk();
    void standFront();
    void standBack();
    void standSide();
};
#endif //PROJ_ANDROID_STUDIO_ROLESPRITE_H
