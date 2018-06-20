//
// Created by LinusLan on 2018/5/22.
//

#include "HomeScene.h"

bool HomeScene::init() {
    if(!Scene::init()) {
        return false;
    }
    try {
        GameHeaderLayer* headerLayer = GameHeaderLayer::create();
        this->addChild(headerLayer);
        headerLayer->setLocalZOrder(10);
        HomeLayer* homeLayer = HomeLayer::create();
        this->addChild(homeLayer);
    } catch(std::exception& ex) {
        log("初始化家场景异常，%s", ex.what());
    }
    return true;
}