//
// Created by LinusLan on 2018/7/24.
//

#ifndef PROJ_ANDROID_STUDIO_ROLETASKLEVELCONFIG_H
#define PROJ_ANDROID_STUDIO_ROLETASKLEVELCONFIG_H
/**
 * 玩家任务等级配置，每个等级的任务奖励的数量的基础值以及完成任务需要消耗的power和mp的数值设置
 */
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace rapidjson;
class RoleTaskLevelConfig {
public:
    static std::string init();
    static std::string getByLevel(std::string level);
    static std::string getStringByName(std::string level, std::string key);
    static int getIntByName(std::string level, std::string key);
};
#endif //PROJ_ANDROID_STUDIO_ROLETASKLEVELCONFIG_H
