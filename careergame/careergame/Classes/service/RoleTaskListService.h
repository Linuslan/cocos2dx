//
// Created by LinusLan on 2018/7/26.
//

#ifndef PROJ_ANDROID_STUDIO_ROLETASKLISTSERVICE_H
#define PROJ_ANDROID_STUDIO_ROLETASKLISTSERVICE_H
#include <vector>
#include "BaseService.h"
#include "Task.h"
#include "RoleTask.h"
class RoleTaskListService: public BaseService {
public:
    RoleTask* createRoleTask(Task* task);
    void addTask(RoleTask* task);
    std::vector<RoleTask*>* getTaskList();
    bool updateTask(RoleTask* task);
};
#endif //PROJ_ANDROID_STUDIO_ROLETASKLISTSERVICE_H
