//
// Created by LinusLan on 2018/3/1.
//

#include "Weapon.h"
bool Weapon::init() {
    if(!Sprite::init()) {
        return false;
    }
    return true;
}

void Weapon::stand() {}

void Weapon::fight() {}

void Weapon::walk() {}