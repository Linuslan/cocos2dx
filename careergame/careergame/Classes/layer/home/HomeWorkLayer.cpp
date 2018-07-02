//
// Created by LinusLan on 2018/6/22.
//

#include <cocos2d/cocos/ui/UIListView.h>
#include <cocos2d/cocos/ui/UIText.h>
#include <Classes/config/RoleJobTaskConfig.h>
#include <Classes/layer/DialogLayer.h>
#include "HomeWorkLayer.h"
bool HomeWorkLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    this->roleService = new RoleService();
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* sprite = Sprite::create("images/home/home_work_bg.png");
    this->addChild(sprite);
    sprite->setPosition(winSize/2);
    //任务按钮
    ui::Button* jobTaskBtn = ui::Button::create("images/home/work.png");
    this->addChild(jobTaskBtn);
    jobTaskBtn->setPosition(Vec2(winSize.width*0.1, winSize.height*0.8));
    jobTaskBtn->addClickEventListener([this, winSize](Ref* ref) {
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
        std::vector<rapidjson::Value*>* jsonArray = RoleJobTaskConfig::getTaskList();
        //initial the data
        for(std::vector<rapidjson::Value*>::iterator iter = jsonArray->begin(); iter != jsonArray->end(); iter++) {
            rapidjson::Value* pvalue = (*iter);
            log("原始value的地址为：%0x", pvalue);
            rapidjson::Value value = (*pvalue).GetObject();
            std::string name = value["name"].GetString();
            int id = value["id"].GetInt();
            ui::Widget* item = default_item->clone();
            item->setContentSize(size);
            item->setTag(id);
            ui::Text* label = static_cast<ui::Text*>(item->getChildByName("label"));
            label->setString(name.c_str());
            ui::Button* button = static_cast<ui::Button*>(item->getChildByName("btn"));
            button->addClickEventListener([this, value](Ref* ref){
                Document doc;
                log("点击了按钮开始工作, pvalue地址为：%0x, 是否对对象：%d, id=%d", pvalue, (*pvalue).IsObject(), (*pvalue)["id"].GetInt());
                if(nullptr == this->task) {
                    log("删除旧任务");
                    delete task;
                }
                rapidjson::Value* val = new rapidjson::Value();
                val->SetObject();
                val->AddMember(rapidjson::Value("id", doc.GetAllocator()), rapidjson::Value(1), doc.GetAllocator());
                val->AddMember(rapidjson::Value("name", doc.GetAllocator()), rapidjson::Value("测试", doc.GetAllocator()), doc.GetAllocator());
                val->AddMember(rapidjson::Value("spendTime", doc.GetAllocator()), rapidjson::Value(60), doc.GetAllocator());
                log("创建新对象成功, 对象地址：%0x", val);
                //val->CopyFrom(*pvalue, doc.GetAllocator());
                //log("复制对象成功");
                this->task = val;
            });
            listView->pushBackCustomItem(item);
        }
        DialogLayer* dialog = DialogLayer::create();
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
            /*role->mpReduce(20); //一分钟减20的体力
            this->roleService->updateRole(role);*/
            log("判断task是否为对象：%d, 地址为：%0x", (*task).IsObject(), task);
            rapidjson::Value val = (*task).GetObject();
            log("开始计算时间");
            int spendTime = val["spendTime"].GetInt() + 1;
            log("时间加1，得到时间为：%d", spendTime);
            val["spendTime"].SetInt(spendTime);
            log("增加时间成功：%d", spendTime);
            //RoleJobTaskConfig::updateTask(task);
        }
    }
}