//
// Created by LinusLan on 2018/4/3.
//

#include "DialogLayer.h"
#include "cocos-ext.h"
#include "JniMethods.h"
bool DialogLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    auto frameSize = Director::getInstance()->getVisibleSize();
    auto listener1 = EventListenerTouchOneByOne::create();
    //这里设为true
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = [this](Touch *touch, Event *event){
        log("touch layer 1");
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);
    Sprite* bg = Sprite::create("dialog/bg.png");
    this->addChild(bg);
    bg->setScale(0.5);
    bg->setPosition(Vec2(winSize.width/2, winSize.height/2));
    Label* label = Label::createWithSystemFont("手机号：", "", 20);
    label->setColor(Color3B::BLACK);
    this->addChild(label);
    label->setPosition(Vec2(winSize.width/2-100, winSize.height/2));
    ui::EditBox* phoneIpt = ui::EditBox::create(Size(175, 35), "dialog/input.png");
    phoneIpt->setName("dialog-phone-11");
    this->addChild(phoneIpt);
    phoneIpt->setPosition(Vec2(winSize.width/2+50, winSize.height/2));

    log("生成sureBtn");
    ui::Button* sureBtn = ui::Button::create("dialog/sure.png");
    this->addChild(sureBtn);
    sureBtn->setPosition(Vec2(winSize.width/2, winSize.height/2-80));
    sureBtn->setScale(0.4);
    sureBtn->setName("dialog-sure-btn");
    sureBtn->addClickEventListener([this](Ref* ref) {
        ui::EditBox* phoneIpt = static_cast<ui::EditBox*>(this->getChildByName("dialog-phone-11"));
        const char* phone = phoneIpt->getText();
        JniMethods::setPhone(phone);
        CCLOG("设置手机号成功，开始调用支付接口");
        JniMethods::requestPayWith1(price);
        JniMethods::getInstance()->s_callfuncOnReceive = callback;
        this->removeFromParent();
    });
    log("生成sureBtn结束");
    ui::Button* quitBtn = ui::Button::create("dialog/quit.png");
    quitBtn->setPosition(Vec2(winSize.width*0.71, winSize.height*0.66));
    quitBtn->setScale(0.4);
    this->addChild(quitBtn);
    quitBtn->addClickEventListener([this](Ref* ref){
        this->removeFromParent();
    });
    log("DialogLayer调用结束");
    return true;
}

void DialogLayer::setCallback(const dialogCallback &f) {
    callback=f;
}