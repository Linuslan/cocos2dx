//
// Created by LinusLan on 2018/6/22.
//

#include "HomeWorkLayer.h"
bool HomeWorkLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    Sprite* sprite = Sprite::create("");
    return true;
}