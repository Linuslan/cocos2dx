//
// Created by LinusLan on 2018/6/20.
//

#include <Classes/config/RoleLevelConfig.h>
#include "HomeComputerBtn.h"
#include "HomeLayer.h"
#include "HomeScene.h"
#include "DialogLayer.h"
bool HomeComputerBtn::init() {
    if(!ui::Button::init()) {
        return false;
    }
    this->loadTextureNormal("images/home/computer_table_blank.png", TextureResType::LOCAL);
    this->addClickEventListener(CC_CALLBACK_1(HomeComputerBtn::doClick, this));
    this->setName("computer");
    this->roleService = new RoleService();
    this->roleJobTaskService = new RoleJobTaskService();
    this->roleTaskListService = new RoleTaskListService();
    Size size = this->getContentSize();
    Sprite* computerTable1 = Sprite::create("images/home/computer_table_1.png");
    computerTable1->setName("mask");
    this->addChild(computerTable1);
    computerTable1->setPosition(Vec2(size.width/2, size.height*0.55));
    Sprite* computerTable2 = Sprite::create("images/home/computer_table_2.png");
    computerTable2->setName("building");
    this->addChild(computerTable2);
    computerTable2->setPosition(Vec2(size.width/2, size.height*0.05));
    return true;
}

void HomeComputerBtn::doClick(Ref* ref) {
    log("点击了电脑");
    BaseBtn::doClick(ref);
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* map = static_cast<Sprite*>(this->getParent());
    HomeLayer* layer = static_cast<HomeLayer*>(map->getParent());
    /*DialogLayer* dialog = DialogLayer::create();
    scene->addChild(dialog);
    dialog->setLocalZOrder(11);
    this->workBtn = HomeComputerWorkBtn::create();
    dialog->addChild(workBtn);
    workBtn->setPosition(winSize/2);
    workBtn->setLocalZOrder(12);*/
    RoleSprite* sprite = static_cast<RoleSprite*>(map->getChildByName("role-11"));
    sprite->setTargetObj(this);

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
    std::vector<RoleTask*>* taskList = this->roleTaskListService->getTaskList();
    //initial the data
    for(std::vector<RoleTask*>::iterator iter = taskList->begin(); iter != taskList->end(); iter++) {
        RoleTask* pTask = (*iter);
        log("原始value的地址为：%0x", pTask);
        //rapidjson::Value value = (*pvalue).GetObject();
        std::string name = pTask->getName();
        int id = pTask->getId();
        ui::Widget* item = default_item->clone();
        item->setContentSize(size);
        item->setTag(id);
        ui::Text* label = static_cast<ui::Text*>(item->getChildByName("label"));
        label->setString(name.c_str());
        ui::Button* button = static_cast<ui::Button*>(item->getChildByName("btn"));
        if(pTask->getStatus() == 1) {
            button->setVisible(false);
        } else {
            button->addClickEventListener([this, pTask, dialog, sprite](Ref* ref){
                Document doc;
                log("点击了按钮开始工作, pvalue地址为：%0x, id=%d", pTask, pTask->getId());
                this->task = pTask;
                this->isWork = true;
                dialog->removeAllChildrenWithCleanup(true);
                dialog->removeFromParent();
                sprite->setVisible(false);
                schedule(schedule_selector(HomeComputerBtn::update), 60.0);
                sprite->unscheduleAllCallbacks();
            });
        }
        listView->pushBackCustomItem(item);
    }
    dialog->addChild(listView);
    layer->addChild(dialog);
    log("点击电脑结束");
}

void HomeComputerBtn::callback() {
    schedule(schedule_selector(HomeComputerBtn::update), 10.0);
}

/**
 * 玩家在工作界面内，则规定时间内获得一定的经验值
 * 将获得的经验值更新到角色属性中
 * @param t
 */
void HomeComputerBtn::update(float t) {
    log("HomeComputerBtn 准备开始执行工作任务");
    if(nullptr != task && isWork) {
        log("HomeComputerBtn 开始执行工作任务");
        Role* role = this->roleService->loadRoleById(1);
        std::string levelStr = StringUtils::format("%d", role->getLevel());
        int totalMp = RoleLevelConfig::getIntByName(levelStr, "mp");
        int totalPower = RoleLevelConfig::getIntByName(levelStr, "power");
        int totalExp = RoleLevelConfig::getIntByName(levelStr, "exp");
        log("HomeComputerBtn 开始计算时间");
        int spendTime = task->getTimeSpend() + 1;
        log("HomeComputerBtn 时间加1，得到时间为：%d，游戏需要花费的时间为：%d", spendTime, task->getTime());
        if(spendTime >= task->getTime()) {
            spendTime = task->getTime();
            isWork = false;
            log("HomeComputerBtn 提醒玩家任务完成，并给玩家增加经验和资金");
            role->expIncrease(task->getExp());
            role->addMoney(task->getMoney());
            if(role->getExp()>= totalExp) {
                role->levelUp();
                float restExp = role->getExp()-totalExp;
                log("HomeComputerBtn 升级后的玩家等级为：%d，剩余经验为：%f", role->getLevel(), restExp);
                role->setExp(restExp);
            }
            task->setStatus(1); //将状态改为已完成
        }
        task->setTimeSpend(spendTime);
        log("HomeComputerBtn 增加时间成功：%d", spendTime);
        log("HomeComputerBtn 玩家等级为：%d, 升级需要的经验为：%d，玩家当前经验：%f", role->getLevel(), totalExp, role->getExp());
        int mpReduce = totalMp*task->getMp()/100;
        int powerReduce = totalPower*task->getPower()/100;
        if(role->getMp() < mpReduce || role->getPower() < powerReduce) {
            log("HomeComputerBtn 精力和体力不足，提醒用户补充食物和睡眠，同时中断任务");
            isWork = false;
            return ;
        }
        role->mpReduce(mpReduce); //一分钟减20的体力
        role->powerReduce(powerReduce);
        this->roleTaskListService->updateTask(task);
        this->roleService->updateRole(role);
    }
}