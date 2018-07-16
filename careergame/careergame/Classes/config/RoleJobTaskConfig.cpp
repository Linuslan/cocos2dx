//
// Created by LinusLan on 2018/7/2.
//

#include "RoleJobTaskConfig.h"
std::string RoleJobTaskConfig::init() {
    std::string filePath = FileUtils::getInstance()->fullPathForFilename("config/role_job_task_config.json");
    std::string writePath = RoleJobTaskConfig::getFilePath();
    FILE* file = fopen(writePath.c_str(), "r");
    //如果文件不存在，则创建一个新文件
    if(!file) {
        file = fopen(writePath.c_str(), "w");
    }
    fclose(file);
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
    Document doc;
    doc.Parse(data.c_str());
    for(SizeType i = 0; i < doc.Size(); i ++) {
        rapidjson::Value value = doc[i].GetObject();
        rapidjson::Value* val = new rapidjson::Value();
        val->CopyFrom(value, doc.GetAllocator());
        task->push_back(val);
    }
    return task;
}

std::string RoleJobTaskConfig::getFilePath() {
    std::string writePath = FileUtils::getInstance()->getWritablePath()+"/config/role_job_task_config.json";
    return writePath;
}