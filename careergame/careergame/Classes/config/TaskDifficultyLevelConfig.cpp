//
// Created by LinusLan on 2018/7/25.
//

#include "TaskDifficultyLevelConfig.h"
std::string TaskDifficultyLevelConfig::init() {
    std::string data = FileUtils::getInstance()->getStringFromFile("config/task_difficulty_level_config.json");
    UserDefault::getInstance()->setStringForKey("TaskDifficultyLevelConfig", data);
    log("获取到的数据已设置到本地存储中为：%s", data.c_str());
    return data;
}

std::string TaskDifficultyLevelConfig::getByLevel(std::string level) {
    std::string data = UserDefault::getInstance()->getStringForKey("TaskDifficultyLevelConfig");
    if(data.empty()) {
        data = TaskDifficultyLevelConfig::init();
    }
    if(data.empty()) {
        return "";
    }
    Document doc;
    doc.Parse(data.c_str());
    if(doc[level.c_str()].IsNull()) {
        return "";
    }
    return doc[level.c_str()].GetString();
}

std::string TaskDifficultyLevelConfig::getStringByName(std::string level, std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("TaskDifficultyLevelConfig");
    if(data.empty()) {
        data = TaskDifficultyLevelConfig::init();
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

int TaskDifficultyLevelConfig::getIntByName(std::string level, std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("TaskDifficultyLevelConfig");
    if(data.empty()) {
        data = TaskDifficultyLevelConfig::init();
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