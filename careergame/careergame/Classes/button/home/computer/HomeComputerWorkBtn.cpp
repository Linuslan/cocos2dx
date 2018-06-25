//
// Created by LinusLan on 2018/6/20.
//

#include "HomeComputerWorkBtn.h"
#include "HomeLayer.h"
#include "RoleSprite.h"
#include "DialogLayer.h"
#include "HomeWorkScene.h"
bool HomeComputerWorkBtn::init() {
    if(!ui::Button::init()) {
        return false;
    }
    this->loadTextureNormal("images/home/work.png", TextureResType::LOCAL);
    this->addClickEventListener(CC_CALLBACK_1(HomeComputerWorkBtn::doClick, this));
    return true;
}

void HomeComputerWorkBtn::doClick(Ref* ref) {
    log("点击了工作按钮");
    DialogLayer* dialogLayer = static_cast<DialogLayer*>(this->getParent());

    HomeLayer* layer = static_cast<HomeLayer*>(this->getParent()->getParent()->getChildByName("HomeLayer"));
    RoleSprite* sprite = static_cast<RoleSprite*>(layer->getChildByName("role-11"));
    sprite->setTargetBtn(this);
    sprite->callback = [](){
        log("执行工作行数回调");
        HomeWorkScene* scene = HomeWorkScene::create();
        Director::getInstance()->replaceScene(scene);
    };
    dialogLayer->removeFromParent();
    sprite->walk();
}

void HomeComputerWorkBtn::callback() {
    log("执行工作回调函数");
}
