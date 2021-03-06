//
// Created by LinusLan on 2018/6/22.
//

#include <cocos2d/cocos/ui/UIListView.h>
#include <cocos2d/cocos/ui/UIText.h>
#include <Classes/layer/DialogLayer.h>
#include "HomeWorkLayer.h"
bool HomeWorkLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    this->roleService = new RoleService();
    this->roleJobTaskService = new RoleJobTaskService();
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* sprite = Sprite::create("images/home/home_work_bg.png");
    this->addChild(sprite);
    sprite->setPosition(winSize/2);
    //任务按钮
    ui::Button* jobTaskBtn = ui::Button::create("images/home/work.png");
    this->addChild(jobTaskBtn);
    jobTaskBtn->setPosition(Vec2(winSize.width*0.1, winSize.height*0.8));
    jobTaskBtn->addClickEventListener([this, winSize](Ref* ref) {
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
        std::vector<RoleJobTask*>* taskList = this->roleJobTaskService->getTasks();
        //initial the data
        for(std::vector<RoleJobTask*>::iterator iter = taskList->begin(); iter != taskList->end(); iter++) {
            RoleJobTask* pTask = (*iter);
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
            button->addClickEventListener([this, pTask, dialog](Ref* ref){
                Document doc;
                log("点击了按钮开始工作, pvalue地址为：%0x, id=%d", pTask, pTask->getId());
                this->task = pTask;
                dialog->removeAllChildrenWithCleanup(true);
                dialog->removeFromParent();
            });
            listView->pushBackCustomItem(item);
        }
        dialog->addChild(listView);
        this->addChild(dialog);
    });
    schedule(schedule_selector(HomeWorkLayer::update), 10.0);
    return true;
}

/**
 * 玩家在工作界面内，则规定时间内获得一定的经验值
 * 将获得的经验值更新到角色属性中
 * @param t
 */
void HomeWorkLayer::update(float t) {
    log("准备开始执行任务");
    if(nullptr != task) {
        log("开始执行工作任务");
        Role* role = this->roleService->loadRoleById(1);
        if(role->getMp() >= 20) {
            role->mpReduce(20); //一分钟减20的体力
            this->roleService->updateRole(role);
            log("task地址为：%0x", task);
            log("开始计算时间");
            int spendTime = task->getTimeSpend() + 1;
            if(spendTime >= task->getTime()) {
                spendTime = task->getTime();

            }
            log("时间加1，得到时间为：%d", spendTime);
            task->setTimeSpend(spendTime);
            log("增加时间成功：%d", spendTime);
            this->roleJobTaskService->updateTask(task);
        }
    }
}