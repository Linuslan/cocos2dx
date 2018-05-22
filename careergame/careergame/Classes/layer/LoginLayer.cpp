//
// Created by LinusLan on 2018/5/18.
//

#include "LoginLayer.h"
bool LoginLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
    log("winSize.width=%f, winSize.height=%f, visible.width=%f, visible.height=%f, original.x=%f, original.y=%f",
        winSize.width, winSize.height, visibleSize.width, visibleSize.height, visibleOrigin.x, visibleOrigin.y);
    Sprite* bg = Sprite::create("images/login/login_bg.png");
    this->addChild(bg);
    bg->setPosition(winSize/2);
    Sprite* loginLbl = Sprite::create("images/login/login_label.png");
    this->addChild(loginLbl);
    loginLbl->setPosition(Vec2(winSize.width*0.4, winSize.height*0.55));
    ui::EditBox* loginNameIpt = ui::EditBox::create(Size(95, 15), "images/login/input.png");
    loginNameIpt->setInputMode(ui::EditBox::InputMode::ANY);
    loginNameIpt->setFontSize(14);
    this->addChild(loginNameIpt);
    loginNameIpt->setPosition(Vec2(winSize.width*0.53, winSize.height*0.58));
    ui::EditBox* passwordIpt = ui::EditBox::create(Size(95, 15), "images/login/input.png");
    passwordIpt->setInputMode(ui::EditBox::InputMode::ANY);
    passwordIpt->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    this->addChild(passwordIpt);
    passwordIpt->setPosition(Vec2(winSize.width*0.53, winSize.height*0.52));
    ui::Button* loginBtn = ui::Button::create("images/login/login_btn.png", "images/login/login_btn.png", "images/login/login_btn.png");
    loginBtn->setPosition(Vec2(winSize.width*0.5, winSize.height*0.4));
    loginBtn->setScale(0.8);
    this->addChild(loginBtn);
    loginBtn->addClickEventListener([](Ref* ref){
        log("login...");
        HomeScene* homeScene = HomeScene::create();
        Director::getInstance()->replaceScene(homeScene);
    });
    ui::Button* quitBtn = ui::Button::create("images/login/quit.png", "images/login/quit.png", "images/login/quit.png");
    quitBtn->setPosition(Vec2(winSize.width*0.71, winSize.height*0.66));
    this->addChild(quitBtn);
    quitBtn->addClickEventListener([](Ref* ref){
        exit(0);
    });
    return true;
}
