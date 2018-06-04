//
// Created by LinusLan on 2018/5/21.
//

#include <cocos2d/cocos/ui/UIListView.h>
#include "RoleLoginLayer.h"
bool RoleLoginLayer::init() {
    if(!RoleLoginLayer::init()) {
        return false;
    }
    Size size = Director::getInstance()->getWinSize();
    Sprite* bg = Sprite::create("images/scene/002.jpg");
    bg->setPosition(size/2);
    this->addChild(bg);
    ui::ListView* listView = ui::ListView::create();
    listView->setPosition(Vec2(size.width*0.6, size.height*0.8));
    ui::Layout* layout = ui::Layout::create();
    Label* roleName = Label::createWithTTF("程序员", "fonts/Marker Felt.ttf", 20);
    layout->addChild(roleName);
    listView->addChild(layout);
    this->addChild(listView);
    return true;
}