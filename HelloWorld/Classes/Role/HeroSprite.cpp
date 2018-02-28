//
// Created by LinusLan on 2018/2/27.
//

#include "HeroSprite.h"
bool HeroSprite::init() {
    if(!Sprite::init()) {
        return false;
    }
    sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("tilemap/role.plist", "tilemap/role.png");
    this->createWithSpriteFrameName("role-1.png");
    scheduleUpdate();
    return true;
}

void HeroSprite::stand() {
    offsetX = 0.0f;
    offsetY = 0.0f;
    this->stopActionByTag(2);
    Vector<SpriteFrame*> frames;
    frames.pushBack(sfc->getSpriteFrameByName("role-1.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-10.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-11.png"));
    frames.pushBack(sfc->getSpriteFrameByName("role-12.png"));
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.17f);
    Animate* animate = Animate::create(animation);
    animate->setTag(1);
    this->runAction(RepeatForever::create(animate));
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
