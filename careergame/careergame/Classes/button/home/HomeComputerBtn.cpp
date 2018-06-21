//
// Created by LinusLan on 2018/6/20.
//

#include "HomeComputerBtn.h"
#include "HomeLayer.h"
#include "HomeScene.h"
#include "DialogLayer.h"
bool HomeComputerBtn::init() {
    if(!ui::Button::init()) {
        return false;
    }
    this->loadTextureNormal("test/home_computer.png", TextureResType::LOCAL);
    this->addClickEventListener(CC_CALLBACK_1(HomeComputerBtn::doClick, this));
    return true;
}

void HomeComputerBtn::doClick(Ref* ref) {
    log("点击了电脑");
    BaseBtn::doClick(ref);
    Size winSize = Director::getInstance()->getWinSize();
    HomeLayer* layer = static_cast<HomeLayer*>(this->getParent());
    HomeScene* scene = static_cast<HomeScene*>(layer->getParent());
    DialogLayer* dialog = DialogLayer::create();
    scene->addChild(dialog);
    dialog->setLocalZOrder(11);
    this->workBtn = HomeComputerWorkBtn::create();
    dialog->addChild(workBtn);
    workBtn->setPosition(winSize/2);
    workBtn->setLocalZOrder(12);
    RoleSprite* sprite = static_cast<RoleSprite*>(layer->getChildByName("role-11"));
    sprite->setTargetObj(this);
    log("点击电脑结束");
}

void HomeComputerBtn::callback() {

}