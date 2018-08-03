//
// Created by LinusLan on 2018/6/22.
//

#ifndef PROJ_ANDROID_STUDIO_HOMEWORKLAYER_H
#define PROJ_ANDROID_STUDIO_HOMEWORKLAYER_H

#include <Classes/service/RoleJobTaskService.h>
#include "cocos2d.h"
#include "RoleService.h"
#include "cocos-ext.h"
USING_NS_CC;
class HomeWorkLayer: public Layer {
private:
    RoleService* roleService = nullptr;
    RoleJobTaskService* roleJobTaskService = nullptr;
    RoleJobTask* task = nullptr;
public:
    virtual bool init();
    CREATE_FUNC(HomeWorkLayer);
    void update(float t);
};
#endif //PROJ_ANDROID_STUDIO_HOMEWORKLAYER_H
