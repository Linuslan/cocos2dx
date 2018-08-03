//
// Created by LinusLan on 2018/7/25.
//

#ifndef PROJ_ANDROID_STUDIO_TASKDIFFICULTYLEVELCONFIG_H
#define PROJ_ANDROID_STUDIO_TASKDIFFICULTYLEVELCONFIG_H
/**
 * 难度等级配置
 */
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace rapidjson;
class TaskDifficultyLevelConfig {
public:
    static std::string init();
    static std::string getByLevel(std::string level);
    static std::string getStringByName(std::string level, std::string key);
    static int getIntByName(std::string level, std::string key);
};
#endif //PROJ_ANDROID_STUDIO_TASKDIFFICULTYLEVELCONFIG_H
