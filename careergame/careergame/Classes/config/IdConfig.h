//
// Created by LinusLan on 2018/7/25.
//

#ifndef PROJ_ANDROID_STUDIO_IDCONFIG_H
#define PROJ_ANDROID_STUDIO_IDCONFIG_H
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace rapidjson;
class IdConfig {
public:
    static std::string init();
    static std::string getStringByName(std::string key);
    static int getIntByName(std::string key);
    static std::string getFilePath();
    static void increaseIdByKey(std::string key);
    static int getIdByKey(std::string key);
};
#endif //PROJ_ANDROID_STUDIO_IDCONFIG_H
