//
// Created by LinusLan on 2018/5/22.
//

#include <Classes/layer/DialogLayer.h>
#include <Classes/service/RoleTaskListService.h>
#include <Classes/config/RoleLevelConfig.h>
#include <Classes/common/NumberUtils.h>
#include "GameHeaderLayer.h"
#include "RoleService.h"
#include "RoleJobConfig.h"
#include "TaskListService.h"
#include "IdConfig.h"
bool GameHeaderLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    try {
        RoleService* roleService = new RoleService();
        Role* role = roleService->loadRoleById(1);
        std::string levelStr = StringUtils::format("%d", role->getLevel());
        Size winSize = Director::getInstance()->getWinSize();
        float headerHeight = winSize.height*0.9;
        int fontSize = 30;
        log("开始生成玩家属性栏");
        //玩家左侧属性栏内容
        Label* nameLbl = Label::createWithSystemFont("姓名："+role->getName(), "", fontSize);
        nameLbl->setColor(Color3B::BLACK);
        this->addChild(nameLbl);
        nameLbl->setName("nameLbl");
        nameLbl->setPosition(Vec2(winSize.width*0.1, headerHeight));

        Label* typeLbl = Label::createWithSystemFont("职业："+RoleJobConfig::getStringByName(StringUtils::format("%d", role->getType())), "", fontSize);
        typeLbl->setColor(Color3B::BLACK);
        typeLbl->setName("typeLbl");
        this->addChild(typeLbl);
        typeLbl->setPosition(Vec2(winSize.width*0.2, headerHeight));

        Label* lvLbl = Label::createWithSystemFont("等级："+levelStr, "", fontSize);
        lvLbl->setColor(Color3B::BLACK);
        lvLbl->setName("lvLbl");
        this->addChild(lvLbl);
        lvLbl->setPosition(Vec2(winSize.width*0.3, headerHeight));
        /*Label* lvDisplayLbl = Label::createWithSystemFont(StringUtils::format("%d", role->getLevel()), "", fontSize);
        lvDisplayLbl->setColor(Color3B::BLACK);
        lvDisplayLbl->setName("gameheader-lvLabel");
        this->addChild(lvDisplayLbl);
        lvDisplayLbl->setPosition(Vec2(winSize.width*0.35, headerHeight));*/

        int hp = RoleLevelConfig::getIntByName(levelStr, "hp");
        //float roleHp = linuslan::NumberUtils::formatDecimal(role->getHp(), 2);
        Label* hpLbl = Label::createWithSystemFont("HP："+StringUtils::format("%.2f", role->getHp())+"/"+StringUtils::format("%d", hp), "", fontSize);
        hpLbl->setColor(Color3B::BLACK);
        hpLbl->setName("hpLbl");
        this->addChild(hpLbl);
        hpLbl->setPosition(Vec2(winSize.width*0.4, headerHeight));

        int mp = RoleLevelConfig::getIntByName(levelStr, "mp");
        //float roleMp = linuslan::NumberUtils::formatDecimal(role->getMp(), 2);
        Label* mpLbl = Label::createWithSystemFont("MP："+StringUtils::format("%.2f", role->getMp())+"/"+StringUtils::format("%d", mp), "", fontSize);
        mpLbl->setColor(Color3B::BLACK);
        mpLbl->setName("mpLbl");
        this->addChild(mpLbl);
        mpLbl->setPosition(Vec2(winSize.width*0.55, headerHeight));

        int power = RoleLevelConfig::getIntByName(levelStr, "power");
        //float rolePower = linuslan::NumberUtils::formatDecimal(role->getPower(), 2);
        Label* powerLbl = Label::createWithSystemFont("POWER："+StringUtils::format("%.2f", role->getPower())+"/"+StringUtils::format("%d", power), "", fontSize);
        powerLbl->setColor(Color3B::BLACK);
        powerLbl->setName("powerLbl");
        this->addChild(powerLbl);
        powerLbl->setPosition(Vec2(winSize.width*0.7, headerHeight));

        ui::Button* email = ui::Button::create("images/gameheader/email.png");
        email->setPosition(Vec2(winSize.width*0.88, headerHeight));
        email->setScale(0.07);
        FadeIn* fadeIn = FadeIn::create(0.5);
        //FadeOut* fadeOut = FadeOut::create(0.5);
        //Sequence* sequence = Sequence::create(fadeIn, fadeOut, nullptr);
        Sequence* sequence = Sequence::create(fadeIn, nullptr);
        email->runAction(RepeatForever::create(sequence));
        email->addClickEventListener(CC_CALLBACK_1(GameHeaderLayer::showTaskList, this));
        this->addChild(email);
        ui::Button* quitBtn = ui::Button::create("CloseNormal.png", "CloseSelected.png");
        quitBtn->setPosition(Vec2(winSize.width*0.9, headerHeight));
        quitBtn->addClickEventListener([](Ref* ref) {
            HelloWorld* loginScene = HelloWorld::create();
            Director::getInstance()->replaceScene(loginScene);
        });
        this->addChild(quitBtn);
        schedule(schedule_selector(GameHeaderLayer::update), 1.0);
    } catch (std::exception& ex) {
        log("初始化游戏头异常，%s", ex.what());
    }
    return true;
}

void GameHeaderLayer::showTaskList(Ref* ref) {
    Size winSize = Director::getInstance()->getWinSize();
    TaskListService* taskListService = new TaskListService();
    std::vector<Task*>* taskList = taskListService->getTaskList();
    DialogLayer* dialog = DialogLayer::create();
    ui::ListView* listView = ui::ListView::create();
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    listView->setBounceEnabled(true);
    listView->setBackGroundImage("test/white_bg.png");
    listView->setBackGroundColorOpacity(200);
    listView->setBackGroundImageScale9Enabled(true);
    listView->setContentSize(Size(500, 500));
    listView->setPosition(Vec2(winSize.width*0.35, winSize.height*0.35));
    listView->setAnchorPoint(Vec2::ZERO);
    listView->setScrollBarPositionFromCorner(Vec2(7, 7));
    listView->setMagneticType(ui::ListView::MagneticType::BOTH_END);
    listView->setItemsMargin(0);
    ui::Button* default_button = ui::Button::create("images/login/sure.png");
    default_button->setName("btn");
    default_button->setScale(0.5);
    Size size = Size(450, 100);
    ui::Layout* default_item = ui::Layout::create();
    default_item->setTouchEnabled(true);
    default_item->setContentSize(size);
    default_item->setBackGroundImage("");
    default_button->setPosition(Vec2(default_item->getContentSize().width*0.7, default_item->getContentSize().height*0.5));
    default_item->addChild(default_button);
    ui::Text* text = ui::Text::create("", "fonts/黑体 simhei.ttf", 30);
    text->setTextColor(Color4B::BLACK);
    text->setName("label");
    text->setPosition(Vec2(default_item->getContentSize().width*0.3, default_item->getContentSize().height*0.5));
    default_item->addChild(text);

    // set model
    listView->setItemModel(default_item);

    // set all items layout gravity
    listView->setGravity(ui::ListView::Gravity::CENTER_VERTICAL);
    //std::vector<rapidjson::Value*>* jsonArray = RoleJobTaskConfig::getTaskList();
    //initial the data
    for(std::vector<Task*>::iterator iter = taskList->begin(); iter != taskList->end(); iter++) {
        Task* pTask = (*iter);
        log("原始value的地址为：%0x", pTask);
        //rapidjson::Value value = (*pvalue).GetObject();
        char* name = pTask->getName();
        log("系统任务名称为：%s", name);
        int id = pTask->getId();
        ui::Widget* item = default_item->clone();
        item->setContentSize(size);
        item->setTag(id);
        ui::Text* label = static_cast<ui::Text*>(item->getChildByName("label"));
        label->setString(name);
        ui::Button* button = static_cast<ui::Button*>(item->getChildByName("btn"));
        if(pTask->getStatus() == 1) {
            button->setVisible(false);
        } else {
            button->addClickEventListener([this, pTask, dialog](Ref* ref){
                log("领取系统任务id为：%d，任务名称为：%s", pTask->getId(), pTask->getName());
                Document doc;
                RoleTaskListService* roleTaskListService = new RoleTaskListService();
                RoleTask* roleTask = roleTaskListService->createRoleTask(pTask);
                log("领取系统任务，创建的角色任务id为：%d, 名称为：%s, taskId为：%d", roleTask->getId(), roleTask->getName(), roleTask->getTaskId());
                roleTaskListService->addTask(roleTask);
                //更新任务为已领取
                pTask->setStatus(1);
                TaskListService* taskListService = new TaskListService();
                taskListService->updateTask(pTask);
                delete roleTask;
                delete roleTaskListService;
                delete taskListService;
                log("点击了按钮开始工作, pvalue地址为：%0x, id=%d", pTask, pTask->getId());
            });
        }
        listView->pushBackCustomItem(item);
    }
    dialog->addChild(listView);
    this->addChild(dialog);
    log("系统任务展示成功，开始清楚内存对象");
    delete taskListService;
    log("taskListService删除成功");
    delete taskList;
    log("taskList删除成功");
}

void GameHeaderLayer::update(float t) {
    RoleService* roleService = new RoleService();
    Role* role = roleService->loadRoleById(1);
    std::string levelStr = StringUtils::format("%d", role->getLevel());
    Label* nameLbl = static_cast<Label*>(this->getChildByName("nameLbl"));
    Label* lvLbl = static_cast<Label*>(this->getChildByName("lvLbl"));
    Label* typeLbl = static_cast<Label*>(this->getChildByName("typeLbl"));
    Label* hpLbl = static_cast<Label*>(this->getChildByName("hpLbl"));
    Label* mpLbl = static_cast<Label*>(this->getChildByName("mpLbl"));
    Label* powerLbl = static_cast<Label*>(this->getChildByName("powerLbl"));
    nameLbl->setString("姓名："+role->getName());
    lvLbl->setString("等级："+levelStr);
    typeLbl->setString("职业："+RoleJobConfig::getStringByName(StringUtils::format("%d", role->getType())));
    int hp = RoleLevelConfig::getIntByName(levelStr, "hp");
    //float roleHp = linuslan::NumberUtils::formatDecimal(role->getHp(), 2);
    hpLbl->setString("HP："+StringUtils::format("%.2f", role->getHp())+"/"+StringUtils::format("%d", hp));
    int mp = RoleLevelConfig::getIntByName(levelStr, "mp");
    //float roleMp = linuslan::NumberUtils::formatDecimal(role->getMp(), 2);
    mpLbl->setString("MP："+StringUtils::format("%.2f", role->getMp())+"/"+StringUtils::format("%d", mp));
    int power = RoleLevelConfig::getIntByName(levelStr, "power");
    //float rolePower = linuslan::NumberUtils::formatDecimal(role->getPower(), 2);
    powerLbl->setString("POWER："+StringUtils::format("%.2f", role->getPower())+"/"+StringUtils::format("%d", power));
}