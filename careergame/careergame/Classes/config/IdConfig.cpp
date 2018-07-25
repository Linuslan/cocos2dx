//
// Created by LinusLan on 2018/7/25.
//

#include "IdConfig.h"
#include <cocos2d/external/json/stringbuffer.h>
#include <cocos2d/external/json/writer.h>
std::string IdConfig::init() {
    std::string writePath = IdConfig::getFilePath();
    std::string data = FileUtils::getInstance()->getStringFromFile(writePath);
    UserDefault::getInstance()->setStringForKey("IdConfig", data);
    log("获取到的数据已设置到本地存储中为：%s", data.c_str());
    return data;
}

std::string IdConfig::getStringByName(std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("IdConfig");
    if(data.empty()) {
        data = IdConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[key.c_str()].GetString();
}

int IdConfig::getIntByName(std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("IdConfig");
    if(data.empty()) {
        data = IdConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[key.c_str()].GetInt();
}

std::string IdConfig::getFilePath() {
    std::string writePath = FileUtils::getInstance()->getWritablePath()+"config/id.json";
    try {
        std::string directoryPath = FileUtils::getInstance()->getWritablePath()+"config/";

        bool isDirectoryExist = FileUtils::getInstance()->isDirectoryExist(directoryPath.c_str());
        if(!isDirectoryExist) {
            FileUtils::getInstance()->createDirectory(directoryPath.c_str());
        }
        std::string filePath = directoryPath+"/id.json";
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

void IdConfig::increaseIdByKey(std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("IdConfig");
    if(data.empty()) {
        data = IdConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    rapidjson::Value value = doc[key.c_str()].GetObject();
    value = value.GetInt() + 1;
    doc.RemoveMember(key.c_str());
    doc.AddMember(rapidjson::Value(key.c_str(), doc.GetAllocator()), value, doc.GetAllocator());
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);
    log("角色任务更新后的json：%s", buffer.GetString());
    std::string filePath = IdConfig::getFilePath();
    log("配置路径为：%s", filePath.c_str());
    bool isWrited = FileUtils::getInstance()->writeStringToFile(buffer.GetString(), filePath);
    log("写入到文件成功, %d", isWrited);
    UserDefault::getInstance()->setStringForKey("IdConfig", buffer.GetString());
}

int IdConfig::getIdByKey(std::string key) {
    int id = IdConfig::getIntByName(key);
    increaseIdByKey(key);
    return id;
}