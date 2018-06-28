//
// Created by LinusLan on 2018/5/22.
//

#include "GameHeaderLayer.h"
#include "RoleService.h"
#include "RoleJobConfig.h"
bool GameHeaderLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    try {
        RoleService* roleService = new RoleService();
        Role* role = roleService->loadRoleById(1);
        Size winSize = Director::getInstance()->getWinSize();
        float headerHeight = winSize.height*0.9;
        int fontSize = 30;
        log("开始生成玩家属性栏");
        //玩家左侧属性栏内容
        Label* nameLbl = Label::createWithSystemFont("姓名："+role->getName(), "", fontSize);
        nameLbl->setColor(Color3B::BLACK);
        this->addChild(nameLbl);
        nameLbl->setPosition(Vec2(winSize.width*0.1, headerHeight));

        Label* typeLbl = Label::createWithSystemFont("职业："+RoleJobConfig::getStringByName(StringUtils::format("%d", role->getType())), "", fontSize);
        typeLbl->setColor(Color3B::BLACK);
        this->addChild(typeLbl);
        typeLbl->setPosition(Vec2(winSize.width*0.2, headerHeight));

        Label* lvLbl = Label::createWithSystemFont("等级：", "", fontSize);
        lvLbl->setColor(Color3B::BLACK);
        this->addChild(lvLbl);
        lvLbl->setPosition(Vec2(winSize.width*0.3, headerHeight));
        Label* lvDisplayLbl = Label::createWithSystemFont(StringUtils::format("%d", role->getLevel()), "", fontSize);
        lvDisplayLbl->setColor(Color3B::BLACK);
        lvDisplayLbl->setName("gameheader-lvLabel");
        this->addChild(lvDisplayLbl);
        lvDisplayLbl->setPosition(Vec2(winSize.width*0.35, headerHeight));

        Sprite* email = Sprite::create("images/gameheader/email.png");
        email->setPosition(Vec2(winSize.width*0.88, headerHeight));
        email->setScale(0.07);
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
