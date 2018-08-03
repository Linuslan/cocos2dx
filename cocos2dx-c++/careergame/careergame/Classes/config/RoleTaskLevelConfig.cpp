//
// Created by LinusLan on 2018/7/24.
//

#include "RoleTaskLevelConfig.h"
#include <cocos2d/external/json/stringbuffer.h>
#include <cocos2d/external/json/writer.h>
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
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    doc[level.c_str()].Accept(writer);
    log("得到角色等级%s配置的信息为：%s", level.c_str(), buffer.GetString());
    return buffer.GetString();
}

std::string RoleTaskLevelConfig::getStringByName(std::string level, std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("RoleTaskLevelConfig");
    if(data.empty()) {
        data = RoleTaskLevelConfig::init();
    }
    if(data.empty()) {
        return "";
    }
    Document doc;
    doc.Parse(data.c_str());
    if(doc[level.c_str()].IsNull() || doc[level.c_str()].GetObject()[key.c_str()].IsNull()) {
        return "";
    }
    return doc[level.c_str()].GetObject()[key.c_str()].GetString();
}

int RoleTaskLevelConfig::getIntByName(std::string level, std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("RoleTaskLevelConfig");
    if(data.empty()) {
        data = RoleTaskLevelConfig::init();
    }
    if(data.empty()) {
        return 0;
    }
    Document doc;
    doc.Parse(data.c_str());
    if(doc[level.c_str()].IsNull() || doc[level.c_str()].GetObject()[key.c_str()].IsNull()) {
        return 0;
    }
    return doc[level.c_str()].GetObject()[key.c_str()].GetInt();
}