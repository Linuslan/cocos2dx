//
// Created by LinusLan on 2018/6/13.
//

#ifndef PROJ_ANDROID_STUDIO_ROLESPRITE_H
#define PROJ_ANDROID_STUDIO_ROLESPRITE_H

#include "cocos2d.h"
#include <exception>
USING_NS_CC;
class RoleSprite : public Sprite {
private:
    Vec2 targetPos;
public:
    virtual bool init();
    CREATE_FUNC(RoleSprite);
    void walk(Vec2 pos);
    void standFront();
    void standBack();
    void standSide();
    void update(float a);
};
#endif //PROJ_ANDROID_STUDIO_ROLESPRITE_H
