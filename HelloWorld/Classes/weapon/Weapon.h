//
// Created by LinusLan on 2018/3/1.
//

#ifndef PROJ_ANDROID_STUDIO_WEAPON_H
#define PROJ_ANDROID_STUDIO_WEAPON_H

#include "cocos2d.h"
#include "HeroAnimation.h"
USING_NS_CC;
class Weapon : public Sprite {
protected:
    SpriteFrameCache* sfc;
    Vector<SpriteFrame*>* standFrames;
    Vector<SpriteFrame*>* fightFrames;
    Vector<SpriteFrame*>* walkFrames;
public:
    virtual bool init();
    CREATE_FUNC(Weapon);
    virtual HeroAnimation* stand();
    virtual void fight();
    virtual void walk();
    virtual Vector<SpriteFrame*>* getStandFrames();
    virtual Vector<SpriteFrame*>* getFightFrames();
    virtual Vector<SpriteFrame*>* getWalkFrames();
};
#endif //PROJ_ANDROID_STUDIO_WEAPON_H
