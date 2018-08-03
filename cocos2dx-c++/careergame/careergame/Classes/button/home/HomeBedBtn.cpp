//
// Created by LinusLan on 2018/7/19.
//

#include "HomeBedBtn.h"
bool HomeBedBtn::init() {
    if(!BaseBtn::init()) {
        return false;
    }
    this->loadTextureNormal("images/home/bed.png", TextureResType::LOCAL);
    this->addClickEventListener(CC_CALLBACK_1(HomeBedBtn::doClick, this));
    this->roleService = new RoleService();
    this->setName("bed");
    return true;
}

void HomeBedBtn::doClick(Ref *ref) {
    log("点击了床");
    BaseBtn::doClick(ref);
    log("当前床的位置为：x=%f, y=%f", this->getPosition().x, this->getPosition().y);
}

void HomeBedBtn::callback() {
    schedule(schedule_selector(HomeBedBtn::update), 10.0);
}

void HomeBedBtn::update(float t) {
    log("准备开始执行睡觉进程");
}