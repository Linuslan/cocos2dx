//
// Created by LinusLan on 2018/7/3.
//

#ifndef PROJ_ANDROID_STUDIO_ROLEJOBTASKSERVICE_H
#define PROJ_ANDROID_STUDIO_ROLEJOBTASKSERVICE_H

#include "BaseService.h"
#include "RoleJobTask.h"
#include "cocos2d.h"
#include "RoleJobTaskConfig.h"
USING_NS_CC;

class RoleJobTaskService : public BaseService {
public:
    std::vector<RoleJobTask*>* getTasks();
    void updateTask(RoleJobTask* task);
};
#endif //PROJ_ANDROID_STUDIO_ROLEJOBTASKSERVICE_H
