//
// Created by LinusLan on 2018/6/13.
//

#ifndef PROJ_ANDROID_STUDIO_ROLESPRITE_H
#define PROJ_ANDROID_STUDIO_ROLESPRITE_H

#include "cocos2d.h"
#include "BaseBtn.h"
#include <exception>
USING_NS_CC;
class RoleSprite : public Sprite {
private:
    //需要走向的坐标
    Vec2 targetPos;
    //走到坐标后需要执行的按钮
    BaseBtn* targetBtn;
public:
    virtual bool init();
    CREATE_FUNC(RoleSprite);
    void walk(Vec2 pos);
    void standFront();
    void standBack();
    void standSide();
    void update(float a);
    void setTargetBtn(BaseBtn* targetBtn) {this->targetBtn=targetBtn;}
};
#endif //PROJ_ANDROID_STUDIO_ROLESPRITE_H
