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

HeroAnimation* Weapon::stand() {}

void Weapon::fight() {}

void Weapon::walk() {}

Vector<SpriteFrame*>* Weapon::getStandFrames() {
    return standFrames;
}

Vector<SpriteFrame*>* Weapon::getFightFrames() {
    return fightFrames;
}

Vector<SpriteFrame*>* Weapon::getWalkFrames() {
    return walkFrames;
}

