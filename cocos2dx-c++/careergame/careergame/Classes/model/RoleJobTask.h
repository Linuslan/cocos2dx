//
// Created by LinusLan on 2018/7/2.
//

#ifndef PROJ_ANDROID_STUDIO_ROLEJOBTASK_H
#define PROJ_ANDROID_STUDIO_ROLEJOBTASK_H

#include "BaseEntity.h"
#include <iostream>
class RoleJobTask: public BaseEntity {
private:
    int id;
    int taskId;
    std::string name;
    int time;
    int exp;
    int money;
    int level;
    int timeSpend;
    int status;
public:
    int getId() {return id;}
    void setId(int id) {this->id = id;}
    int getTaskId() {return taskId;}
    void setTaskId(int taskId) {this->taskId = taskId;}
    std::string getName() {return name;}
    void setName(std::string name) {this->name = name;}
    int getTime() {return time;}
    void setTime(int time) {this->time = time;}
    int getExp() {return exp;}
    void setExp(int exp) {this->exp = exp;}
    int getMoney() {return money;}
    void setMoney(int money) {this->money = money;}
    int getLevel() {return level;}
    void setLevel(int level) {this->level = level;}
    int getTimeSpend() {return timeSpend;}
    void setTimeSpend(int timeSpend) {this->timeSpend = timeSpend;}
    int getStatus() {return status;}
    void setStatus(int status) {this->status = status;}
};
#endif //PROJ_ANDROID_STUDIO_ROLEJOBTASK_H
