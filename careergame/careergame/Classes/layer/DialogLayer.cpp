//
// Created by LinusLan on 2018/6/20.
//

#include "DialogLayer.h"
bool DialogLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    auto listener1 = EventListenerTouchOneByOne::create();
    //这里设为true
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = [this](Touch *touch, Event *event){
        log("touch layer 1");
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);
    LayerColor* color = LayerColor::create(Color4B(0, 0, 0, 150), winSize.width, winSize.height);
    this->setCascadeColorEnabled(true);
    this->addChild(color);
    return true;
}
