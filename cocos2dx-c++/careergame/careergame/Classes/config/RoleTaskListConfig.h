//
// Created by LinusLan on 2018/7/24.
//

#ifndef PROJ_ANDROID_STUDIO_ROLETASKLISTCONFIG_H
#define PROJ_ANDROID_STUDIO_ROLETASKLISTCONFIG_H

/**
 * 玩家已领取的任务列表
 */
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace rapidjson;
class RoleTaskListConfig {
public:
    static std::string init();
    static std::string getData();
    static std::string getByLevel(std::string level);
    static std::string getStringByName(std::string level, std::string key);
    static int getIntByName(std::string level, std::string key);
    static std::string getFilePath();
    static bool updateTaskList(std::string data);
};
#endif //PROJ_ANDROID_STUDIO_ROLETASKLISTCONFIG_H
