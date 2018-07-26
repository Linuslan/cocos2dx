//
// Created by LinusLan on 2018/6/20.
//

#ifndef PROJ_ANDROID_STUDIO_HOMECOMPUTERBTN_H
#define PROJ_ANDROID_STUDIO_HOMECOMPUTERBTN_H

#include "BaseBtn.h"
#include "HomeComputerWorkBtn.h"
#include "RoleService.h"
#include "cocos-ext.h"
#include "RoleJobTaskService.h"
#include "RoleTaskListService.h"
class HomeComputerBtn:public BaseBtn {
private:
    HomeComputerWorkBtn* workBtn;
    RoleService* roleService = nullptr;
    RoleJobTaskService* roleJobTaskService = nullptr;
    RoleTask* task = nullptr;
    RoleTaskListService* roleTaskListService = nullptr;
public:
    virtual bool init();
    CREATE_FUNC(HomeComputerBtn);
    virtual void callback();
    virtual void doClick(Ref* ref);
    void update(float t);
};
#endif //PROJ_ANDROID_STUDIO_HOMECOMPUTERBTN_H
