//
// Created by LinusLan on 2018/7/24.
//

#include "RoleTaskListConfig.h"
std::string RoleTaskListConfig::init() {
    std::string data = FileUtils::getInstance()->getStringFromFile("config/role_task_list_config.json");
    UserDefault::getInstance()->setStringForKey("RoleTaskListConfig", data);
    log("获取到的数据已设置到本地存储中为：%s", data.c_str());
    return data;
}

std::string RoleTaskListConfig::getByLevel(std::string level) {
    std::string data = UserDefault::getInstance()->getStringForKey("RoleTaskListConfig");
    if(data.empty()) {
        data = RoleTaskListConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[level.c_str()].GetString();
}

std::string RoleTaskListConfig::getStringByName(std::string level, std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("RoleTaskListConfig");
    if(data.empty()) {
        data = RoleTaskListConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[level.c_str()].GetObject()[key.c_str()].GetString();
}

int RoleTaskListConfig::getIntByName(std::string level, std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("RoleTaskListConfig");
    if(data.empty()) {
        data = RoleTaskListConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[level.c_str()].GetObject()[key.c_str()].GetInt();
}

std::string RoleTaskListConfig::getFilePath() {
    std::string writePath = FileUtils::getInstance()->getWritablePath()+"config/role_task_list_config.json";
    try {
        std::string directoryPath = FileUtils::getInstance()->getWritablePath()+"config/";

        bool isDirectoryExist = FileUtils::getInstance()->isDirectoryExist(directoryPath.c_str());
        if(!isDirectoryExist) {
            FileUtils::getInstance()->createDirectory(directoryPath.c_str());
        }
        std::string filePath = directoryPath+"/role_task_list_config.json";
        FILE* file = fopen(filePath.c_str(), "r");
        if(!file) {
            file = fopen(filePath.c_str(), "w");
        }
        fclose(file);
    } catch(std::exception& ex) {
        log("创建文件异常：%s", ex.what());
    } catch(std::runtime_error& error) {
        log("创建文件错误：%s", error.what());
    }
    return writePath;
}