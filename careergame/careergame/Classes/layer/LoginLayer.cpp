//
// Created by LinusLan on 2018/5/18.
//

#include "LoginLayer.h"
bool LoginLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* bg = Sprite::create("images/login.jpg");
    this->addChild(bg);
    ui::EditBox* loginNameIpt = ui::EditBox::create(Size(200, 25), "");
    loginNameIpt->setInputMode(ui::EditBox::InputMode::ANY);
    this->addChild(loginNameIpt);
    loginNameIpt->setPosition(Vec2(200, 300));
    ui::EditBox* passwordIpt = ui::EditBox::create(Size(200, 25), "");
    passwordIpt->setInputMode(ui::EditBox::InputMode::ANY);
    passwordIpt->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    this->addChild(passwordIpt);
    passwordIpt->setPosition(Vec2(200, 400));
    ui::Button* loginBtn = ui::Button::create("normalImage", "selectedImage", "disableImage");
    loginBtn->setPosition(Vec2(200, 500));
    loginBtn->setContentSize(Size(50, 30));
    this->addChild(loginBtn);
    loginBtn->addClickEventListener([](Ref* ref){
        
    });
    return true;
}
