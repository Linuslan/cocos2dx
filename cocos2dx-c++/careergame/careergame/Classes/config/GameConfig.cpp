//
// Created by LinusLan on 2018/6/24.
//

#include "GameConfig.h"
std::string GameConfig::init() {
    std::string data = FileUtils::getInstance()->getStringFromFile("config/game_config.json");
    UserDefault::getInstance()->setStringForKey("GameConfig", data);
    log("获取到的数据已设置到本地存储中为：%s", data.c_str());
    return data;
}

std::string GameConfig::getStringByName(std::string level, std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("GameConfig");
    if(data.empty()) {
        data = GameConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[level.c_str()].GetObject()[key.c_str()].GetString();
}

int GameConfig::getIntByName(std::string level, std::string key) {
    std::string data = UserDefault::getInstance()->getStringForKey("GameConfig");
    if(data.empty()) {
        data = GameConfig::init();
    }
    Document doc;
    doc.Parse(data.c_str());
    return doc[level.c_str()].GetObject()[key.c_str()].GetInt();
}