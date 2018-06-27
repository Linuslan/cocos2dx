//
// Created by LinusLan on 2018/5/22.
//

#include "GameHeaderLayer.h"
#include "RoleService.h"
bool GameHeaderLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    try {
        RoleService* roleService = new RoleService();
        Role* role = roleService->loadRoleById(1);
        Size winSize = Director::getInstance()->getWinSize();
        float headerHeight = winSize.height*0.9;
        //玩家左侧属性栏内容
        Label* nameLbl = Label::createWithSystemFont("姓名："+role->getName(), "", 20);
        this->addChild(nameLbl);
        nameLbl->setPosition(Vec2(winSize.width*0.1, headerHeight));

        Label* typeLbl = Label::createWithSystemFont("职业：");

        Sprite* email = Sprite::create("images/gameheader/email.png");
        email->setPosition(Vec2(winSize.width*0.88, headerHeight));
        email->setScale(0.1);
        FadeIn* fadeIn = FadeIn::create(0.5);
        //FadeOut* fadeOut = FadeOut::create(0.5);
        //Sequence* sequence = Sequence::create(fadeIn, fadeOut, nullptr);
        Sequence* sequence = Sequence::create(fadeIn, nullptr);
        email->runAction(RepeatForever::create(sequence));
        this->addChild(email);
        ui::Button* quitBtn = ui::Button::create("CloseNormal.png", "CloseSelected.png");
        quitBtn->setPosition(Vec2(winSize.width*0.9, headerHeight));
        quitBtn->addClickEventListener([](Ref* ref) {
            HelloWorld* loginScene = HelloWorld::create();
            Director::getInstance()->replaceScene(loginScene);
        });
        this->addChild(quitBtn);
    } catch (std::exception& ex) {
        log("初始化游戏头异常，%s", ex.what());
    }
    return true;
}
