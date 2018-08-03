//
// Created by LinusLan on 2018/7/25.
//

#include "Task.h"
#include "cocos2d.h"
USING_NS_CC;
Task::~Task() {
    log("调用Task的析构函数");
    if(this->name != nullptr) {
        log("删除名称");
        delete[] name;
    }
}