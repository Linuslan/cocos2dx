//
// Created by LinusLan on 2018/6/20.
//

#include "HomeComputerBtn.h"
bool HomeComputerBtn::init() {
    if(!ui::Button::init()) {
        return false;
    }
    this->loadTextureNormal("test/home_computer.png", TextureResType::LOCAL);
    this->addClickEventListener(CC_CALLBACK_1(HomeComputerBtn::callback, this));
    return true;
}

void HomeComputerBtn::callback(Ref* ref) {
    log("点击了电脑");
    HomeLayer* layer = static_cast<HomeLayer*>(this->getParent());
    DialogLayer* dialog = DialogLayer::create();
    layer->addChild(dialog);
}