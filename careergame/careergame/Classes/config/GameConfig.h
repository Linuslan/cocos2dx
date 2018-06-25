//
// Created by LinusLan on 2018/6/24.
//

#ifndef PROJ_ANDROID_STUDIO_BASECONFIG_H
#define PROJ_ANDROID_STUDIO_BASECONFIG_H

#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace rapidjson;
class GameConfig {
public:
    static std::string init();
    static std::string getStringByName(std::string level, std::string key);
    static int getIntByName(std::string level, std::string key);
};
#endif //PROJ_ANDROID_STUDIO_BASECONFIG_H
