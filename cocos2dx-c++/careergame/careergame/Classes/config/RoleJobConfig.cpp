//
// Created by LinusLan on 2018/6/27.
//

#include "RoleJobConfig.h"
std::string RoleJobConfig::init() {
    std::string data = FileUtils::getInstance()->getStringFromFile("config/role_job_config.json");
    UserDefault::getInstance()->setStringForKey("RoleJobConfig", data);
    log("获取到的数据已设置到本地存储中为：%s", data.c_str());
    return data;
}

std::string RoleJobConfig::getStringByName(std::string jobType) {
    std::string data = UserDefault::getInstance()->getStringForKey("RoleJobConfig");
    if(data.empty()) {
        data = RoleJobConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[jobType.c_str()].GetString();
}