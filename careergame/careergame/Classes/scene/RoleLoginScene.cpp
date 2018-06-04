//
// Created by LinusLan on 2018/5/21.
//

#include "RoleLoginScene.h"
bool RoleLoginScene::init() {
    if(!Scene::init()) {
        return false;
    }
    try {
        log("开始初始化角色场景");
        RoleLoginLayer* layer = RoleLoginLayer::create();
        this->addChild(layer);
    } catch (std::exception& ex) {
        log("初始化角色场景异常，%s", ex.what());
    }
    return true;
}