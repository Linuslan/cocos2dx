//
// Created by LinusLan on 2018/6/20.
//

#include "DialogLayer.h"
bool DialogLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    float headerHeight = winSize.height*0.9;
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
    ui::Button* quitBtn = ui::Button::create("CloseNormal.png", "CloseSelected.png");
    quitBtn->setPosition(Vec2(winSize.width*0.9, headerHeight));
    quitBtn->addClickEventListener([this](Ref* ref) {
        this->removeAllChildrenWithCleanup(true);
        this->removeFromParent();
    });
    this->addChild(quitBtn);
    return true;
}
