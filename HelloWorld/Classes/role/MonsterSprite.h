//
// Created by LinusLan on 2018/3/13.
//

#ifndef PROJ_ANDROID_STUDIO_MONSTER_H
#define PROJ_ANDROID_STUDIO_MONSTER_H

#include "cocos2d.h"
#include "RoleSprite.h"
#include "TileMapLayer.h"
USING_NS_CC;
class MonsterSprite : public RoleSprite {
public:
    virtual bool init();
    CREATE_FUNC(MonsterSprite);
    virtual void walk();
    virtual void stand();
    virtual void autoWalk();
};
#endif //PROJ_ANDROID_STUDIO_MONSTER_H
