//
// Created by LinusLan on 2018/7/24.
//

#include "TaskListConfig.h"
std::string TaskListConfig::init() {
    std::string data = FileUtils::getInstance()->getStringFromFile("config/task_list_config.json");
    UserDefault::getInstance()->setStringForKey("TaskListConfig", data);
    log("获取到的数据已设置到本地存储中为：%s", data.c_str());
    return data;
}

std::string TaskListConfig::getByLevel(std::string level) {
    std::string data = UserDefault::getInstance()->getStringForKey("TaskListConfig");
    if(data.empty()) {
        data = TaskListConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[level.c_str()].GetString();
}

std::string TaskListConfig::getStringByName(std::string level, std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("TaskListConfig");
    if(data.empty()) {
        data = TaskListConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[level.c_str()].GetObject()[key.c_str()].GetString();
}

int TaskListConfig::getIntByName(std::string level, std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("TaskListConfig");
    if(data.empty()) {
        data = TaskListConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[level.c_str()].GetObject()[key.c_str()].GetInt();
}