//
// Created by LinusLan on 2018/5/21.
//

#include "RoleLoginScene.h"
bool RoleLoginScene::init() {
    if(!Scene::init()) {
        return false;
    }
    RoleLoginLayer* layer = RoleLoginLayer::create();
    this->addChild(layer);
    return true;
}