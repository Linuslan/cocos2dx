//
// Created by LinusLan on 2018/6/20.
//

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
        button->addClickEventListener([this, pTask, dialog, sprite](Ref* ref){
            Document doc;
            log("点击了按钮开始工作, pvalue地址为：%0x, id=%d", pTask, pTask->getId());
            this->task = pTask;
            dialog->removeAllChildrenWithCleanup(true);
            dialog->removeFromParent();
            sprite->setVisible(false);
        });
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
    log("准备开始执行任务");
    if(nullptr != task) {
        log("开始执行工作任务");
        Role* role = this->roleService->loadRoleById(1);
        if(role->getMp() >= 20) {
            role->mpReduce(20); //一分钟减20的体力
            this->roleService->updateRole(role);
            log("task地址为：%0x", task);
            log("开始计算时间");
            int spendTime = task->getTime() + 1;
            log("时间加1，得到时间为：%d", spendTime);
            task->setTime(spendTime);
            log("增加时间成功：%d", spendTime);
            this->roleTaskListService->updateTask(task);
        }
    }
}