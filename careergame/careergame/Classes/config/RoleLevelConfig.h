//
// Created by LinusLan on 2018/7/23.
//

#ifndef PROJ_ANDROID_STUDIO_ROLELEVELCONFIG_H
#define PROJ_ANDROID_STUDIO_ROLELEVELCONFIG_H

/**
 * 玩家角色等级配置信息，每个等级的属性最大值多少，都在这边
 */
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace rapidjson;
class RoleLevelConfig {
public:
    static std::string init();
    static std::string getStringByName(std::string level, std::string key);
    static int getIntByName(std::string level, std::string key);
};
#endif //PROJ_ANDROID_STUDIO_ROLELEVELCONFIG_H
