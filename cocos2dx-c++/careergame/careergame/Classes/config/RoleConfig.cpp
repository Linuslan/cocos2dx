//
// Created by LinusLan on 2018/8/8.
//

#include "RoleConfig.h"
std::string RoleConfig::init() {
    std::string writePath = RoleConfig::getFilePath();
    std::string data = FileUtils::getInstance()->getStringFromFile(writePath);
    UserDefault::getInstance()->setStringForKey(DATA_KEY.c_str(), data);
    return data;
}

std::string RoleConfig::getStringByName(std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey(DATA_KEY.c_str());
    if(data.empty()) {
        data = RoleConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[key.c_str()].GetString();
}

int RoleConfig::getIntByName(std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey(DATA_KEY.c_str());
    if(data.empty()) {
        data = RoleConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    if(!doc.HasMember(key.c_str())) {
        doc.AddMember(rapidjson::Value(key.c_str(), doc.GetAllocator()), rapidjson::Value(1), doc.GetAllocator());
    }
}

std::string RoleConfig::getFilePath() {
    std::string writePath = FileUtils::getInstance()->getWritablePath()+"config/role_config.json";
    try {
        std::string directoryPath = FileUtils::getInstance()->getWritablePath()+"config/";

        bool isDirectoryExist = FileUtils::getInstance()->isDirectoryExist(directoryPath.c_str());
        if(!isDirectoryExist) {
            FileUtils::getInstance()->createDirectory(directoryPath.c_str());
        }
        std::string filePath = directoryPath+"/role_config.json";
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