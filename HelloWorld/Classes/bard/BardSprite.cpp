//
// Created by LinusLan on 2018/3/5.
//

#include "BardSprite.h"
bool BardSprite::init() {
    if(!Sprite::init()) {
        return false;
    }
    this->setAnchorPoint(Vec2(0, 0));
    this->setPosition(Vec2(0, 0));
    return true;
}

HeroAnimation* BardSprite::stand() {
    return nullptr;
}

HeroAnimation* BardSprite::walk() {
    return nullptr;
}

HeroAnimation* BardSprite::fight() {
    return nullptr;
}