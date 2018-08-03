//
// Created by LinusLan on 2018/7/2.
//

#include "RoleJobTaskConfig.h"
std::string RoleJobTaskConfig::init() {
    std::string filePath = FileUtils::getInstance()->fullPathForFilename("config/role_job_task_config.json");
    std::string writePath = RoleJobTaskConfig::getFilePath();
    log("配置路径为：%s, writePath:%s", filePath.c_str(), writePath.c_str());
    std::string data = FileUtils::getInstance()->getStringFromFile(writePath);
    //FileUtils::getInstance()->writeStringToFile(data, writePath);
    UserDefault::getInstance()->setStringForKey("RoleJobTaskConfig", data);
    log("获取到的数据已设置到本地存储中为：%s", data.c_str());
    return data;
}

std::vector<rapidjson::Value*>* RoleJobTaskConfig::getTaskList() {
    std::vector<rapidjson::Value*>* task = new std::vector<rapidjson::Value*>();
    std::string data = UserDefault::getInstance()->getStringForKey("RoleJobTaskConfig");
    if(data.empty()) {
        data = RoleJobTaskConfig::init();
    }
    if(!data.empty()) {
        Document doc;
        doc.Parse(data.c_str());
        for(SizeType i = 0; i < doc.Size(); i ++) {
            rapidjson::Value value = doc[i].GetObject();
            rapidjson::Value* val = new rapidjson::Value();
            val->CopyFrom(value, doc.GetAllocator());
            task->push_back(val);
        }
    }
    return task;
}

std::string RoleJobTaskConfig::getFilePath() {
    std::string writePath = FileUtils::getInstance()->getWritablePath()+"config/role_job_task_config.json";
    try {
        std::string directoryPath = FileUtils::getInstance()->getWritablePath()+"config/";

        bool isDirectoryExist = FileUtils::getInstance()->isDirectoryExist(directoryPath.c_str());
        if(!isDirectoryExist) {
            FileUtils::getInstance()->createDirectory(directoryPath.c_str());
        }
        std::string filePath = directoryPath+"/role_job_task_config.json";
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