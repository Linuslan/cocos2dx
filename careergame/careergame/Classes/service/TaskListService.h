//
// Created by LinusLan on 2018/7/25.
//

#ifndef PROJ_ANDROID_STUDIO_TASKLISTSERVICE_H
#define PROJ_ANDROID_STUDIO_TASKLISTSERVICE_H

#include <vector>
#include "BaseService.h"
#include "Task.h"
class TaskListService: public BaseService {
public:
    void addTask(Task* task);
    std::vector<Task*>* getTaskList();
};
#endif //PROJ_ANDROID_STUDIO_TASKLISTSERVICE_H
