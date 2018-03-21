//
// Created by LinusLan on 2018/3/13.
//

#include "MonsterSprite.h"
#include "RoleSprite.h"

bool MonsterSprite::init() {
    if(!RoleSprite::init()) {
        return false;
    }
    return true;
}

void MonsterSprite::autoWalk() {
    TMXTiledMap* map = static_cast<TMXTiledMap*>(this->getParent());
    HeroSprite* hero = static_cast<HeroSprite*>(map->getChildByTag(100));
    Vec2 heroPosition = hero->getPosition();
}
