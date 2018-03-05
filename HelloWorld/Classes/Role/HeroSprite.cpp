//
// Created by LinusLan on 2018/2/27.
//

#include "HeroSprite.h"
bool HeroSprite::init() {
    if(!Sprite::init()) {
        return false;
    }
    sfc = SpriteFrameCache::getInstance();
    //sfc->addSpriteFramesWithFile("tilemap/role.plist", "tilemap/role.png");
    sfc->addSpriteFramesWithFile("tilemap/role-stand.plist", "tilemap/role-stand.png");
    this->createWithSpriteFrameName("role-stand-1.png");
    log("start create weapon");
    this->weapon = Spear::create();
    this->addChild(this->weapon);
    this->hair = NormalHairSprite::create();
    this->addChild(this->hair);
    this->bard = WhiteBardSprite::create();
    this->addChild(this->bard);
    log("weapon create ended");
    scheduleUpdate();
    return true;
}

HeroSprite::~HeroSprite() {
    this->weapon->release();
}

void HeroSprite::stand() {
    log("start stand");
    offsetX = 0.0f;
    offsetY = 0.0f;
    this->stopActionByTag(2);
    Vector<SpriteFrame*> frames;
    /*frames.pushBack(sfc->getSpriteFrameByName("role-1.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-10.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-11.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-12.png"));*/
    frames.pushBack(sfc->getSpriteFrameByName("role-stand-1.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-stand-2.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-stand-3.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-stand-4.png"));
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.17f);
    //Animate* animate = Animate::create(animation);
    //animate->setTag(1);
    //this->runAction(RepeatForever::create(animate));
    log("start weapon stand");
    HeroAnimation* weaponAnimation = this->weapon->stand();
    HeroAnimation* bardAnimation = this->bard->stand();
    HeroAnimation* hairAnimation = this->hair->stand();
    HeroAnimate* animate = HeroAnimate::create(animation);
    animate->addAction(weaponAnimation);
    animate->addAction(bardAnimation);
    animate->addAction(hairAnimation);
    animate->setTag(1);
    this->runAction(RepeatForever::create(animate));
    log("start stand end");
}

void HeroSprite::walk(double degree) {
    this->stopActionByTag(1);
    Vector<SpriteFrame*> frames;
    for(int i = 2; i < 10; i ++) {
        frames.pushBack(sfc->getSpriteFrameByName(StringUtils::format("role-%d.png", i)));
    }
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.15f);
    Animate* animate = Animate::create(animation);
    /*MoveBy* move = MoveBy::create(10.0f, Vec2(100, 0));
    Spawn* spawn = Spawn::create(animate, move, nullptr);*/
    animate->setTag(2);
    this->runAction(RepeatForever::create(animate));

    float distance = 2.5;
    //offsetY = sin(degree)*distance;
    //offsetX = cos(degree)*distance;
    offsetY = sin(degree/180*3.14159265758)*distance;   //将角度转化为弧度，再用三角函数求坐标
    offsetX = cos(degree/180*3.14159265758)*distance;   //同上
    if(degree > 90 || degree < -90) {
        this->setFlippedX(true);
    } else {
        this->setFlippedX(false);
    }
    log("hero: offsetX=%f, offsetY=%f", offsetX, offsetY);
    this->setPosition(this->getPositionX()+offsetX, this->getPositionY()+offsetY);
}

void HeroSprite::update(float t) {
    this->setPosition(this->getPositionX()+offsetX, this->getPositionY()+offsetY);
}