//
// Created by LinusLan on 2018/6/22.
//

#include "HomeWorkLayer.h"
bool HomeWorkLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    this->roleService = new RoleService();
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* sprite = Sprite::create("images/home/home_work_bg.png");
    this->addChild(sprite);
    sprite->setPosition(winSize/2);
    schedule(schedule_selector(HomeWorkLayer::update), 30000);
    return true;
}

/**
 * 玩家在工作界面内，则规定时间内获得一定的经验值
 * 将获得的经验值更新到角色属性中
 * @param t
 */
void HomeWorkLayer::update(float t) {
    Role* role = this->roleService->loadRoleById(1);
    role->expIncrease(20);
    this->roleService->updateRole(role);
}