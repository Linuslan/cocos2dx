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
    sfc->addSpriteFramesWithFile("tilemap/role-walk.plist", "tilemap/role-walk.png");
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
    int size = this->getNumberOfRunningActionsByTag(2);
    log("tag 2 action number is: %d", size);
    this->stopAllActionsByTag(2);
    Vector<SpriteFrame*> frames;
    frames.pushBack(sfc->getSpriteFrameByName("role-stand-1.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-stand-2.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-stand-3.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-stand-4.png"));
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.17f);
    log("start weapon stand");
    HeroAnimation* weaponAnimation = this->weapon->stand();
    HeroAnimation* bardAnimation = this->bard->stand();
    HeroAnimation* hairAnimation = this->hair->stand();
    HeroAnimate* animate = HeroAnimate::create(animation);
    animate->addAction(weaponAnimation);
    animate->addAction(bardAnimation);
    animate->addAction(hairAnimation);
    animate->setTag(1);
    RepeatForever* repeat = RepeatForever::create(animate);
    repeat->setTag(1);
    this->runAction(repeat);
    log("start stand end");
}

void HeroSprite::walk(double degree) {
    int size = this->getNumberOfRunningActionsByTag(1);
    log("tag 1 action number is: %d", size);
    this->stopAllActionsByTag(1);
    Vector<SpriteFrame*> frames;
    for(int i = 1; i < 9; i ++) {
        frames.pushBack(sfc->getSpriteFrameByName(StringUtils::format("role-walk-%d.png", i)));
    }

    Animation* animation = Animation::createWithSpriteFrames(frames, 0.15f);
    HeroAnimation* weaponAnimation = this->weapon->walk();
    HeroAnimation* bardAnimation = this->bard->walk();
    HeroAnimation* hairAnimation = this->hair->walk();
    HeroAnimate* animate = HeroAnimate::create(animation);
    animate->addAction(weaponAnimation);
    animate->addAction(bardAnimation);
    animate->addAction(hairAnimation);
    animate->setTag(2);
    RepeatForever* repeat = RepeatForever::create(animate);
    repeat->setTag(2);
    this->runAction(repeat);

    float distance = 2.5;
    //offsetY = sin(degree)*distance;
    //offsetX = cos(degree)*distance;
    offsetY = sin(degree/180*3.14159265758)*distance;   //将角度转化为弧度，再用三角函数求坐标
    offsetX = cos(degree/180*3.14159265758)*distance;   //同上
    if(degree > 90 || degree < -90) {
        this->setFlippedX(true);
        this->weapon->setFlippedX(true);
        this->bard->setFlippedX(true);
        this->hair->setFlippedX(true);
    } else {
        this->setFlippedX(false);
        this->weapon->setFlippedX(false);
        this->bard->setFlippedX(false);
        this->hair->setFlippedX(false);
    }
    log("hero: offsetX=%f, offsetY=%f", offsetX, offsetY);
    this->setPosition(this->getPositionX()+offsetX, this->getPositionY()+offsetY);
}

void HeroSprite::update(float t) {
    this->setPosition(this->getPositionX()+offsetX, this->getPositionY()+offsetY);
}