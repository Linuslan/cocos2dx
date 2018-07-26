//
// Created by LinusLan on 2018/7/24.
//

#include "RoleTaskListConfig.h"
#include <cocos2d/external/json/stringbuffer.h>
#include <cocos2d/external/json/writer.h>
std::string RoleTaskListConfig::init() {
    std::string writePath = RoleTaskListConfig::getFilePath();
    std::string data = FileUtils::getInstance()->getStringFromFile(writePath);
    UserDefault::getInstance()->setStringForKey("RoleTaskListConfig", data);
    log("获取到的数据已设置到本地存储中为：%s", data.c_str());
    return data;
}

std::string RoleTaskListConfig::getData() {
    std::string data = UserDefault::getInstance()->getStringForKey("TaskListConfig");
    if(data.empty()) {
        data = RoleTaskListConfig::init();
    }
    return data;
}

std::string RoleTaskListConfig::getByLevel(std::string level) {
    std::string data = getData();
    if(data.empty()) {
        return "";
    }
    Document doc;
    doc.Parse(data.c_str());
    if(doc[level.c_str()].IsNull()) {
        return "";
    }
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> write(buffer);
    doc[level.c_str()].Accept(write);
    log("得到玩家等级%s已领取的任务列表为：%s", level.c_str(), buffer.GetString());
    return buffer.GetString();
}

std::string RoleTaskListConfig::getStringByName(std::string level, std::string key) {
    std::string data = getData();
    if(data.empty()) {
        return "";
    }
    Document doc;
    doc.Parse(data.c_str());
    if(!doc[level.c_str()].IsNull() && !doc[level.c_str()].GetObject()[key.c_str()].IsNull()) {
        return doc[level.c_str()].GetObject()[key.c_str()].GetString();
    } else {
        return "";
    }
}

int RoleTaskListConfig::getIntByName(std::string level, std::string key) {
    std::string data = getData();
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

bool RoleTaskListConfig::updateTaskList(std::string data) {
    std::string filePath = RoleTaskListConfig::getFilePath();
    log("配置路径为：%s", filePath.c_str());
    bool isWrited = FileUtils::getInstance()->writeStringToFile(data, filePath);
    log("写入到文件成功, %d", isWrited);
    UserDefault::getInstance()->setStringForKey("RoleTaskListConfig", data);
    return isWrited;
}