//
// Created by LinusLan on 2018/6/20.
//

#ifndef PROJ_ANDROID_STUDIO_HOMECOMPUTERBTN_H
#define PROJ_ANDROID_STUDIO_HOMECOMPUTERBTN_H

#include "BaseBtn.h"
#include "HomeComputerWorkBtn.h"
class HomeComputerBtn:public BaseBtn {
private:
    HomeComputerWorkBtn* workBtn;
public:
    virtual bool init();
    CREATE_FUNC(HomeComputerBtn);
    virtual void callback();
    virtual void doClick(Ref* ref);
};
#endif //PROJ_ANDROID_STUDIO_HOMECOMPUTERBTN_H
