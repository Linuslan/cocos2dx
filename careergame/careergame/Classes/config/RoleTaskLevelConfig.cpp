//
// Created by LinusLan on 2018/7/24.
//

#include "RoleTaskLevelConfig.h"
std::string RoleTaskLevelConfig::init() {
    std::string data = FileUtils::getInstance()->getStringFromFile("config/role_task_level_config.json");
    UserDefault::getInstance()->setStringForKey("RoleTaskLevelConfig", data);
    log("获取到的数据已设置到本地存储中为：%s", data.c_str());
    return data;
}

std::string RoleTaskLevelConfig::getByLevel(std::string level) {
    std::string data = UserDefault::getInstance()->getStringForKey("RoleTaskLevelConfig");
    if(data.empty()) {
        data = RoleTaskLevelConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[level.c_str()].GetString();
}

std::string RoleTaskLevelConfig::getStringByName(std::string level, std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("RoleTaskLevelConfig");
    if(data.empty()) {
        data = RoleTaskLevelConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[level.c_str()].GetObject()[key.c_str()].GetString();
}

int RoleTaskLevelConfig::getIntByName(std::string level, std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("RoleTaskLevelConfig");
    if(data.empty()) {
        data = RoleTaskLevelConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[level.c_str()].GetObject()[key.c_str()].GetInt();
}