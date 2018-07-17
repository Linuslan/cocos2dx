//
// Created by LinusLan on 2018/7/17.
//

#ifndef PROJ_ANDROID_STUDIO_KITCHENTABLEBTN_H
#define PROJ_ANDROID_STUDIO_KITCHENTABLEBTN_H

#include "RoleService.h"
#include "cocos2d.h"
#include "BaseBtn.h"

USING_NS_CC;
class KitchenTableBtn:public BaseBtn {
private:
    RoleService* roleService = nullptr;
public:
    virtual bool init();
    CREATE_FUNC(KitchenTableBtn);
    virtual void callback();
    virtual void doClick(Ref* ref);
    void update(float t);
};
#endif //PROJ_ANDROID_STUDIO_KITCHENTABLEBTN_H
