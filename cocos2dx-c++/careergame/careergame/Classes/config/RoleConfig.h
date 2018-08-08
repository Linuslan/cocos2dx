//
// Created by LinusLan on 2018/8/8.
//

#ifndef PROJ_ANDROID_STUDIO_ROLECONFIG_H
#define PROJ_ANDROID_STUDIO_ROLECONFIG_H

#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace rapidjson;
class RoleConfig {
public:
    static std::string DATA_KEY = "RoleConfig";
    static std::string init();
    static std::string getStringByName(std::string key);
    static int getIntByName(std::string key);
    static std::string getFilePath();
};
#endif //PROJ_ANDROID_STUDIO_ROLECONFIG_H
