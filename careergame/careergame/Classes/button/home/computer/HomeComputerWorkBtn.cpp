//
// Created by LinusLan on 2018/6/20.
//

#include "HomeComputerWorkBtn.h"
bool HomeComputerWorkBtn::init() {
    if(!ui::Button::init()) {
        return false;
    }
    this->loadTextureNormal("test/home_computer.png", TextureResType::LOCAL);
    this->addClickEventListener(CC_CALLBACK_1(HomeComputerWorkBtn::doClick, this));
    return true;
}

void HomeComputerWorkBtn::doClick(Ref* ref) {
    log("点击了工作按钮");
}
