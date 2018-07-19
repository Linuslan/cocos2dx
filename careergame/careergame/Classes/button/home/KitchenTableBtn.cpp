//
// Created by LinusLan on 2018/7/17.
//

#include "KitchenTableBtn.h"
bool KitchenTableBtn::init() {
    if(!ui::Button::init()) {
        return false;
    }
    this->loadTextureNormal("images/home/kitchen_table_blank.png", TextureResType::LOCAL);
    this->addClickEventListener(CC_CALLBACK_1(KitchenTableBtn::doClick, this));
    this->roleService = new RoleService();
    Size size = this->getContentSize();
    Sprite* kitchenTable1 = Sprite::create("images/home/kitchen_table_1.png");
    kitchenTable1->setName("mask");
    this->addChild(kitchenTable1);
    kitchenTable1->setPosition(Vec2(size.width/2, size.height*0.55));
    Sprite* kitchenTable2 = Sprite::create("images/home/kitchen_table_2.png");
    kitchenTable2->setName("building");
    this->addChild(kitchenTable2);
    kitchenTable2->setPosition(Vec2(size.width/2, size.height*0.05));
    return true;
}

void KitchenTableBtn::doClick(Ref *ref) {
    log("点击了厨房");
    BaseBtn::doClick(ref);
    log("当前厨房的位置为：x=%f, y=%f", this->getPosition().x, this->getPosition().y);
}

void KitchenTableBtn::callback() {
    schedule(schedule_selector(KitchenTableBtn::update), 10.0);
}

void KitchenTableBtn::update(float t) {

}
