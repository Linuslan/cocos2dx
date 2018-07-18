//
// Created by LinusLan on 2018/5/22.
//

#include "HomeScene.h"

bool HomeScene::init() {
    if(!Scene::init()) {
        return false;
    }
    try {
        Size winSize = Director::getInstance()->getWinSize();
        log("winSize.width=%f, winSize.height=%f", winSize.width, winSize.height);
        GameHeaderLayer* headerLayer = GameHeaderLayer::create();
        this->addChild(headerLayer);
        headerLayer->setLocalZOrder(10);
        MoveLayer* moveLayer = MoveLayer::create();
        this->addChild(moveLayer);
        moveLayer->setLocalZOrder(10);
        Layer* mapLayer = Layer::create();
        mapLayer->setName("map");
        this->addChild(mapLayer);
        Sprite* mapBg = Sprite::create("images/home/home.png");
        mapBg->setName("mapBg");
        mapLayer->addChild(mapBg);
        mapBg->setPosition(winSize/2);
        Size bgSize = mapBg->getContentSize();
        log("bgSize.width=%f, bgSize.height=%f", bgSize.width, bgSize.height);
        HomeLayer* homeLayer = HomeLayer::create();
        homeLayer->setName("mainLayer");
        this->addChild(homeLayer);
    } catch(std::exception& ex) {
        log("初始化家场景异常，%s", ex.what());
    }
    return true;
}