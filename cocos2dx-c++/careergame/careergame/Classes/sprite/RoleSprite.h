//
// Created by LinusLan on 2018/6/13.
//

#ifndef PROJ_ANDROID_STUDIO_ROLESPRITE_H
#define PROJ_ANDROID_STUDIO_ROLESPRITE_H

#include "cocos2d.h"
#include "BaseBtn.h"
#include <exception>
#include "RoleService.h"
#include "Role.h"
USING_NS_CC;
class RoleSprite : public Sprite {
private:
    //需要角色走过去的对象
    BaseBtn* targetObj;
    //走到坐标后需要执行的按钮
    BaseBtn* targetBtn;
    Role* role = nullptr;
    RoleService* roleService = nullptr;
    bool turnY = false;
    bool startDo = false;
public:
    virtual bool init();
    CREATE_FUNC(RoleSprite);
    void walk();
    void walkUp();
    void walkDown();
    void standFront();
    void standBack();
    void standSide();
    void update(float a);
    void setTargetBtn(BaseBtn* targetBtn) {this->targetBtn=targetBtn;}
    void setTargetObj(BaseBtn* targetObj) {this->targetObj = targetObj;}
    void (*callback)();
    void sleep();
    void sleepUpdate(float a);
    void walkUpdate(float a);
    void standUpdate(float a);
};
#endif //PROJ_ANDROID_STUDIO_ROLESPRITE_H
