//
// Created by LinusLan on 2018/5/21.
//

#include <cocos2d/cocos/ui/UIListView.h>
#include <cocos2d/cocos/ui/UIImageView.h>
#include "RoleLoginLayer.h"
bool RoleLoginLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    log("进入角色登录界面");
    Size winSize = Director::getInstance()->getWinSize();
    /*Sprite* bg = Sprite::create("images/scene/002.jpg");
    bg->setPosition(size/2);
    this->addChild(bg);*/
    ui::ListView* listView = ui::ListView::create();
    listView->setPosition(winSize/2);
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);//设置方向为垂直方向
    listView->setBounceEnabled(true);
    listView->setBackGroundImage("images/white_bg.jpg");
    listView->setBackGroundImageScale9Enabled(true);
    listView->setContentSize(Size(300, 640));
    ui::Layout* layout = ui::Layout::create();
    auto size = Size(300,100);
    layout->setContentSize(size);
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("images/scene/002.jpg");
    //Label* roleName = Label::createWithTTF("程序员", "fonts/Marker Felt.ttf", 20);
    //layout->addChild(roleName);
    //ui::ImageView* imageView = ui::ImageView::create("images/scene/002.jpg");
    //layout->addChild(imageView);
    ui::Button* loginBtn = ui::Button::create("images/login/login_btn.png", "images/login/login_btn.png", "images/login/login_btn.png");
    layout->addChild(loginBtn);
    loginBtn->setPosition(winSize/2);
    loginBtn->setScale9Enabled(true);
    listView->addChild(layout);
    this->addChild(listView);
    return true;
}