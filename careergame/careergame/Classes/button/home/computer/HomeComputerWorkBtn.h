//
// Created by LinusLan on 2018/6/20.
//

#ifndef PROJ_ANDROID_STUDIO_HOMECOMPUTERWORKBTN_H
#define PROJ_ANDROID_STUDIO_HOMECOMPUTERWORKBTN_H

#include "BaseBtn.h"
class HomeComputerWorkBtn:public BaseBtn {
public:
    virtual bool init();
    CREATE_FUNC(HomeComputerWorkBtn);
    virtual void callback();
    virtual void doClick(Ref* ref);
};
#endif //PROJ_ANDROID_STUDIO_HOMECOMPUTERWORKBTN_H
