//
// Created by LinusLan on 2018/6/21.
//

#include "HomeWorkScene.h"
#include "HomeWorkLayer.h"
bool HomeWorkScene::init() {
    if(!Scene::init()) {
        return false;
    }
    HomeWorkLayer* bg = HomeWorkLayer::create();
    this->addChild(bg);
    return true;
}