//
// Created by LinusLan on 2018/7/26.
//

#ifndef PROJ_ANDROID_STUDIO_ROLETASK_H
#define PROJ_ANDROID_STUDIO_ROLETASK_H


#include "Task.h"

class RoleTask : public Task {
private:
    int taskId;
public:
    void setTaskId(int taskId) {this->taskId = taskId;}
    int getTaskId() {return this->taskId;}
};


#endif //PROJ_ANDROID_STUDIO_ROLETASK_H
