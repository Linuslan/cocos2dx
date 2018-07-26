//
// Created by LinusLan on 2018/7/24.
//

#include "TaskListConfig.h"
#include <cocos2d/external/json/stringbuffer.h>
#include <cocos2d/external/json/writer.h>
std::string TaskListConfig::init() {
    std::string writePath = TaskListConfig::getFilePath();
    std::string data = FileUtils::getInstance()->getStringFromFile(writePath);
    UserDefault::getInstance()->setStringForKey("TaskListConfig", data);
    log("获取到的数据已设置到本地存储中为：%s", data.c_str());
    return data;
}

std::string TaskListConfig::getData() {
    std::string data = UserDefault::getInstance()->getStringForKey("TaskListConfig");
    if(data.empty()) {
        data = TaskListConfig::init();
    }
    return data;
}

std::string TaskListConfig::getByLevel(std::string level) {
    std::string data = UserDefault::getInstance()->getStringForKey("TaskListConfig");
    if(data.empty()) {
        data = TaskListConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    doc[level.c_str()].Accept(writer);
    log("得到的系统已生成的任务列表字符串为：%s", buffer.GetString());
    return buffer.GetString();
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

std::string TaskListConfig::getFilePath() {
    std::string writePath = FileUtils::getInstance()->getWritablePath()+"config/task_list_config.json";
    try {
        std::string directoryPath = FileUtils::getInstance()->getWritablePath()+"config/";

        bool isDirectoryExist = FileUtils::getInstance()->isDirectoryExist(directoryPath.c_str());
        if(!isDirectoryExist) {
            FileUtils::getInstance()->createDirectory(directoryPath.c_str());
        }
        std::string filePath = directoryPath+"/task_list_config.json";
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

bool TaskListConfig::updateTaskList(std::string data) {
    std::string filePath = TaskListConfig::getFilePath();
    log("配置路径为：%s", filePath.c_str());
    bool isWrited = FileUtils::getInstance()->writeStringToFile(data, filePath);
    log("写入到文件成功, %d", isWrited);
    UserDefault::getInstance()->setStringForKey("TaskListConfig", data);
    return isWrited;
}