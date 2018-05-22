//
// Created by LinusLan on 2018/5/22.
//

#include "HomeScene.h"

bool HomeScene::init() {
    if(!Scene::init()) {
        return false;
    }
    try {
        HomeLayer* homeLayer = HomeLayer::create();
        this->addChild(homeLayer);
        GameHeaderLayer* headerLayer = GameHeaderLayer::create();
        this->addChild(headerLayer);
    } catch(std::exception& ex) {
        log("初始化家场景异常，%s", ex.what());
    }
    return true;
}