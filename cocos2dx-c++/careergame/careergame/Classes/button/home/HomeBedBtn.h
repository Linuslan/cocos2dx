//
// Created by LinusLan on 2018/7/19.
//

#ifndef PROJ_ANDROID_STUDIO_HOMEBEDBTN_H
#define PROJ_ANDROID_STUDIO_HOMEBEDBTN_H

#include "BaseBtn.h"
#include "RoleService.h"
class HomeBedBtn:public BaseBtn {
private:
    RoleService* roleService = nullptr;
public:
    virtual bool init();
    CREATE_FUNC(HomeBedBtn);
    virtual void callback();
    virtual void doClick(Ref* ref);
    void update(float t);
};
#endif //PROJ_ANDROID_STUDIO_HOMEBEDBTN_H
