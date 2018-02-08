//
// Created by LinusLan on 2018/2/8.
//

#include "BirdMainScene.h"
bool BirdMainScene::init() {
    if(!Scene::init()) {
        return false;
    }
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("pic/bird.plist", "pic/birdP.png");
    Vector<SpriteFrame*> animeFrames;
    animeFrames.pushBack(sfc->getSpriteFrameByName("bird1.png"));
    animeFrames.pushBack(sfc->getSpriteFrameByName("bird2.png"));
    animeFrames.pushBack(sfc->getSpriteFrameByName("bird3.png"));
    Animation* animation = Animation::createWithSpriteFrames(animeFrames, 0.1f);
    Animate* animate = Animate::create(animation);
    Sprite* bird = Sprite::createWithSpriteFrame(sfc->getSpriteFrameByName("bird2.png"));
    bird->setPosition(Vec2(200, 200));
    bird->runAction(RepeatForever::create(animate));
    this->addChild(bird);
    return true;
}