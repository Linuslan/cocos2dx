//
// Created by LinusLan on 2018/7/24.
//

#ifndef PROJ_ANDROID_STUDIO_TASKLISTCONFIG_H
#define PROJ_ANDROID_STUDIO_TASKLISTCONFIG_H
/**
 * 系统生成的所有的任务列表
 */
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace rapidjson;
class TaskListConfig {
public:
    static std::string init();
    static std::string getData();
    static std::string getByLevel(std::string level);
    static std::string getStringByName(std::string level, std::string key);
    static int getIntByName(std::string level, std::string key);
    static std::string getFilePath();
    static bool updateTaskList(std::string data);
};
#endif //PROJ_ANDROID_STUDIO_TASKLISTCONFIG_H
