//
// Created by LinusLan on 2018/6/27.
//

#ifndef PROJ_ANDROID_STUDIO_ROLEJOBCONFIG_H
#define PROJ_ANDROID_STUDIO_ROLEJOBCONFIG_H
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace rapidjson;
class RoleJobConfig {
public:
    static std::string init();
    static std::string getStringByName(std::string jobType);
};
#endif //PROJ_ANDROID_STUDIO_ROLEJOBCONFIG_H
