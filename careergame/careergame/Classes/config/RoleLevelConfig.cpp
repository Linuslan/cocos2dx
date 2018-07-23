//
// Created by LinusLan on 2018/7/23.
//

#include "RoleLevelConfig.h"
std::string RoleLevelConfig::init() {
    std::string data = FileUtils::getInstance()->getStringFromFile("config/role_level_config.json");
    UserDefault::getInstance()->setStringForKey("RoleLevelConfig", data);
    log("获取到的数据已设置到本地存储中为：%s", data.c_str());
    return data;
}

std::string RoleLevelConfig::getStringByName(std::string level, std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("RoleLevelConfig");
    if(data.empty()) {
        data = RoleLevelConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[level.c_str()].GetObject()[key.c_str()].GetString();
}

int RoleLevelConfig::getIntByName(std::string level, std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("RoleLevelConfig");
    if(data.empty()) {
        data = RoleLevelConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[level.c_str()].GetObject()[key.c_str()].GetInt();
}