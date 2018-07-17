//
// Created by LinusLan on 2018/7/17.
//

#include "KitchenTableBtn.h"
bool KitchenTableBtn::init() {
    if(!ui::Button::init()) {
        return false;
    }
    this->loadTextureNormal("images/home/kitchen_table.png", TextureResType::LOCAL);
    this->addClickEventListener(CC_CALLBACK_1(KitchenTableBtn::doClick, this));
    this->roleService = new RoleService();
    return true;
}

void KitchenTableBtn::doClick(Ref *ref) {
    log("点击了厨房");
}

void KitchenTableBtn::callback() {
    schedule(schedule_selector(KitchenTableBtn::update), 10.0);
}

void KitchenTableBtn::update(float t) {

}
