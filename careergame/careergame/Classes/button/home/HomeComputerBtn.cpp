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

void HomeComputerBtn::doClick(Ref* ref) {
    log("点击了电脑");
    Size winSize = Director::getInstance()->getWinSize();
    HomeLayer* layer = static_cast<HomeLayer*>(this->getParent());
    HomeScene* scene = static_cast<HomeScene*>(layer->getParent());
    DialogLayer* dialog = DialogLayer::create();
    scene->addChild(dialog);
    dialog->setLocalZOrder(11);
    this->workBtn = HomeComputerWorkBtn::create();
    dialog->addChild(workBtn);
    workBtn->setPosition(winSize/2);
}