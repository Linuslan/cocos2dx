//
// Created by LinusLan on 2018/5/21.
//

#include <unistd.h>
#include "RoleLoginLayer.h"
#include "RoleJobTaskConfig.h"
#include "time.h"
#include "RoleTaskLevelConfig.h"
#include "RoleService.h"
#include "Role.h"
bool RoleLoginLayer::init() {
    std::string occupation[] = {"程序员", "画家", "设计师", "教师", "投资人"};
    if(!Layer::init()) {
        return false;
    }
    log("进入角色登录界面");
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* bg = Sprite::create("test/background.png");
    bg->setPosition(winSize/2);
    this->addChild(bg);

    Sprite* programmer = Sprite::create("images/role/programmer.png");
    programmer->setPosition(winSize/2);
    programmer->setScale(0.5);
    this->addChild(programmer);

    ui::ListView* listView = ui::ListView::create();
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    listView->setBounceEnabled(true);
    listView->setBackGroundImage("test/white_bg.png");
    listView->setBackGroundColorOpacity(200);
    listView->setBackGroundImageScale9Enabled(true);
    listView->setContentSize(Size(420, 800));
    listView->setPosition(Vec2(winSize.width*0.75, winSize.height*0.1));
    listView->setAnchorPoint(Vec2::ZERO);
    listView->setScrollBarPositionFromCorner(Vec2(7, 7));
    listView->setMagneticType(ui::ListView::MagneticType::BOTH_END);
    listView->setItemsMargin(0);
    ui::Button* default_button = ui::Button::create("images/login/login_btn.png", "images/login/login_btn.png", "images/login/login_btn.png");
    default_button->setName("Title Button");
    default_button->setScale(0.5);
    Size size = Size(400, 100);
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

    //initial the data
    for (int i = 0; i < 5; ++i) {
        ui::Widget* item = default_item->clone();
        item->setContentSize(size);
        item->setTag(i);
        ui::Text* label = static_cast<ui::Text*>(item->getChildByName("label"));
        log("%s", occupation[i].c_str());
        label->setString(occupation[i].c_str());
        listView->pushBackCustomItem(item);
    }
    this->addChild(listView);

    ui::Button* loginBtn = ui::Button::create("images/login/login_btn.png", "images/login/login_btn.png", "images/login/login_btn.png");
    loginBtn->setPosition(Vec2(winSize.width*0.5, winSize.height*0.2));
    //loginBtn->setScale(0.8);
    loginBtn->setTag(1);
    this->addChild(loginBtn);
    //按钮点击事件，实现点击时放大缩小的效果
    loginBtn->addClickEventListener([this](Ref* ref){
        ui::Button* btn = static_cast<ui::Button*>(this->getChildByTag(1));
        ScaleTo* scaleTo = ScaleTo::create(0.1, 1);
        ScaleTo* scaleTo1 = ScaleTo::create(0.1, 0.8);
        //放大缩小的效果执行完成后，CallFunc为动作完成后需要执行的回调函数
        Sequence* sequence = Sequence::create(scaleTo, scaleTo1, CallFunc::create([](){
            HomeScene* homeScene = HomeScene::create();
            Director::getInstance()->replaceScene(homeScene);
        }), nullptr);
        btn->runAction(sequence);
        log("login...%d", btn->getTag());
        this->threadStart();
    });
    RoleJobTaskConfig::getTaskList();
    return true;
}

int RoleLoginLayer::threadStart() {
    int errCode = 0;
    do {
        pthread_attr_t attr;
        errCode = pthread_attr_init(&attr);
        CC_BREAK_IF(errCode != 0);
        errCode = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        if(errCode != 0) {
            pthread_attr_destroy(&attr);
            break;
        }
        errCode = pthread_create(&thread, &attr, thread_function, this);
    } while(0);
    return errCode;
}

void* RoleLoginLayer::thread_function(void *arg) {
    while(true) {
        log("===============启动线程================");
        srand(time(nullptr));
        int time = rand()/60 + 10;  //生成下次执行该任务的时间间隔
        time = time * 60;
        sleep(time);
        RoleService* roleService = new RoleService();
        Role* role = roleService->loadRoleById(1);
        std::string levelConfig = RoleTaskLevelConfig::getByLevel(StringUtils::format("%d", role->getLevel()));
    }
    return NULL;
}