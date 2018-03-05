//
// Created by LinusLan on 2018/3/5.
//

#include "HairSprite.h"
bool HairSprite::init() {
    if(!Sprite::init()) {
        return false;
    }
    this->setAnchorPoint(Vec2(0, 0));
    this->setPosition(Vec2(0, 0));
    return true;
}

HeroAnimation* HairSprite::stand() {
    return nullptr;
}

HeroAnimation* HairSprite::walk() {
    return nullptr;
}

HeroAnimation* HairSprite::fight() {
    return nullptr;
}