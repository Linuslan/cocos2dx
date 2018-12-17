//
// Created by LinusLan on 2018/8/8.
//

#include "GoodsConfig.h"
std::string GoodsConfig::DATA_KEY = "GoodsConfig";
std::string GoodsConfig::init() {
    std::string writePath = GoodsConfig::getFilePath();
    std::string data = FileUtils::getInstance()->getStringFromFile(writePath);
    UserDefault::getInstance()->setStringForKey(DATA_KEY.c_str(), data);
    return data;
}

std::string GoodsConfig::getStringByName(std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey(DATA_KEY.c_str());
    if(data.empty()) {
        data = GoodsConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[key.c_str()].GetString();
}

int GoodsConfig::getIntByName(std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey(DATA_KEY.c_str());
    if(data.empty()) {
        data = GoodsConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    if(!doc.HasMember(key.c_str())) {
        doc.AddMember(rapidjson::Value(key.c_str(), doc.GetAllocator()), rapidjson::Value(1), doc.GetAllocator());
    }
}

std::string GoodsConfig::getFilePath() {
    std::string writePath = FileUtils::getInstance()->getWritablePath()+"config/goods_config.json";
    try {
        std::string directoryPath = FileUtils::getInstance()->getWritablePath()+"config/";

        bool isDirectoryExist = FileUtils::getInstance()->isDirectoryExist(directoryPath.c_str());
        if(!isDirectoryExist) {
            FileUtils::getInstance()->createDirectory(directoryPath.c_str());
        }
        std::string filePath = directoryPath+"/goods_config.json";
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