//
// Created by LinusLan on 2018/6/20.
//


#include "BaseBtn.h"
#include "DialogLayer.h"
#include "RoleSprite.h"
bool BaseBtn::init() {
    if(!ui::Button::init()) {
        return false;
    }
    return true;
}

void BaseBtn::doClick(Ref *ref) {
    log("调用父类点击方法");
    /*RoleSprite* sprite = static_cast<RoleSprite*>(this->getParent()->getChildByName("role-11"));
    sprite->setTargetBtn(this);*/
}

void BaseBtn::callback() {

}