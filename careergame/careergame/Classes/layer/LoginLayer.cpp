//
// Created by LinusLan on 2018/5/18.
//

#include <Classes/scene/RoleLoginScene.h>
#include "LoginLayer.h"
#include "RoleLoginLayer.h"

bool LoginLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    this->setTag(1000);
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
    loginBtn->setTag(1);
    this->addChild(loginBtn);
    //按钮点击事件，实现点击时放大缩小的效果
    loginBtn->addClickEventListener([this](Ref* ref){
        ui::Button* btn = static_cast<ui::Button*>(this->getChildByTag(1));
        ScaleTo* scaleTo = ScaleTo::create(0.1, 1);
        ScaleTo* scaleTo1 = ScaleTo::create(0.1, 0.8);
        //放大缩小的效果执行完成后，CallFunc为动作完成后需要执行的回调函数
        Sequence* sequence = Sequence::create(scaleTo, scaleTo1, CallFunc::create([](){
            //HomeScene* homeScene = HomeScene::create();
            //Director::getInstance()->replaceScene(homeScene);
            RoleLoginScene* roleLoginScene = RoleLoginScene::create();
            Director::getInstance()->replaceScene(roleLoginScene);
        }), nullptr);
        btn->runAction(sequence);
        log("login...%d", btn->getTag());
    });
    ui::Button* quitBtn = ui::Button::create("images/login/quit.png", "images/login/quit.png", "images/login/quit.png");
    quitBtn->setPosition(Vec2(winSize.width*0.71, winSize.height*0.66));
    this->addChild(quitBtn);
    quitBtn->addClickEventListener([](Ref* ref){
        exit(0);
    });
    return true;
}
