//
// Created by LinusLan on 2018/3/1.
//

#include "Weapon.h"

bool Weapon::init() {
    if(!Sprite::init()) {
        return false;
    }
    this->setAnchorPoint(Vec2(0, 0));
    this->setPosition(Vec2(0, 0));
    return true;
}

HeroAnimation* Weapon::stand() {return nullptr;}

HeroAnimation* Weapon::fight() {return nullptr;}

HeroAnimation* Weapon::walk() {return nullptr;}

