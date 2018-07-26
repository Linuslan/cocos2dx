//
// Created by LinusLan on 2018/7/2.
//

#ifndef PROJ_ANDROID_STUDIO_ROLEJOBTASKCONFIG_H
#define PROJ_ANDROID_STUDIO_ROLEJOBTASKCONFIG_H

#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace rapidjson;
class RoleJobTaskConfig {
public:
    static std::string init();
    static std::vector<rapidjson::Value*>* getTaskList();
    static std::string getFilePath();
};
#endif //PROJ_ANDROID_STUDIO_ROLEJOBTASKCONFIG_H
