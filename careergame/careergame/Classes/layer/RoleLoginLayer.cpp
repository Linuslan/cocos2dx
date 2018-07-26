//
// Created by LinusLan on 2018/5/21.
//

#include <unistd.h>
#include <Classes/config/TaskListConfig.h>
#include <Classes/config/RoleTaskListConfig.h>
#include <Classes/config/IdConfig.h>
#include "RoleLoginLayer.h"
#include "RoleJobTaskConfig.h"
#include "time.h"
#include "RoleTaskLevelConfig.h"
#include "RoleService.h"
#include "Role.h"
#include "TaskDifficultyLevelConfig.h"
#include "Task.h"
#include "TaskListService.h"
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
        //int time = rand()%60 + 10;  //生成下次执行该任务的时间间隔
        //time = time * 60;
        int time = rand()%10 + 5;  //生成下次执行该任务的时间间隔
        log("睡眠时间为：%d", time);
        sleep(time);
        RoleService* roleService = new RoleService();
        Role* role = roleService->loadRoleById(1);
        std::string level = StringUtils::format("%d", role->getLevel());
        //玩家等级对应的任务生成的配置信息
        std::string levelConfig = RoleTaskLevelConfig::getByLevel(level);
        //玩家已领取的任务列表
        std::string roleTaskList = RoleTaskListConfig::getByLevel(level);
        //得到用户当前等级，系统已经生成多少的任务了
        std::string levelTaskList = TaskListConfig::getByLevel(level);
        float difficulty1 = 0.0;
        float difficulty2 = 0.0;
        float difficulty3 = 0.0;
        float difficulty4 = 0.0;
        float difficulty5 = 0.0;
        log("判断用户当前等级任务列表是否为空");
        if(!levelTaskList.empty()) {
            log("用户当前等级任务列表为空");
            std::vector<rapidjson::Value> acceptedList;
            std::vector<rapidjson::Value> unacceptedList;

            Document doc;
            doc.Parse(levelTaskList.c_str());
            for(rapidjson::Value::ValueIterator iter = doc.Begin(); iter != doc.End(); iter ++) {
                rapidjson::Value value = (*iter).GetObject();
                if(0 == value["status"].GetInt()) { //未领取的，则加入到未领取的集合中
                    unacceptedList.push_back((*iter).GetObject());
                } else if(1 == value["status"].GetInt()) {  //已领取的加入到已领取的集合中
                    acceptedList.push_back((*iter).GetObject());
                }
                int difficultyLevel = value["difficultyLevel"].GetInt();
                switch(difficultyLevel) {
                    case 1: difficulty1 ++; break;
                    case 2: difficulty2 ++; break;
                    case 3: difficulty3 ++; break;
                    case 4: difficulty4 ++; break;
                    case 5: difficulty5 ++; break;
                }
            }
            //如果有大于5个任务未领取，则不再生成新任务
            if(unacceptedList.size() >= 5) {
                continue;
            }
        }

        difficulty1 = difficulty1 <= 0 ? 1 : difficulty1;
        difficulty2 = difficulty2 <= 0 ? 1 : difficulty2;
        difficulty3 = difficulty3 <= 0 ? 1 : difficulty3;
        difficulty4 = difficulty4 <= 0 ? 1 : difficulty4;
        difficulty5 = difficulty5 <= 0 ? 1 : difficulty5;
        int difficulty1Probability = TaskDifficultyLevelConfig::getIntByName("1", "probability");
        int difficulty2Probability = TaskDifficultyLevelConfig::getIntByName("2", "probability");
        int difficulty3Probability = TaskDifficultyLevelConfig::getIntByName("3", "probability");
        int difficulty4Probability = TaskDifficultyLevelConfig::getIntByName("4", "probability");
        int difficulty5Probability = TaskDifficultyLevelConfig::getIntByName("5", "probability");
        std::string difficultyLevel = "1";
        float rate1 = difficulty1/difficulty1Probability;
        float rate2 = difficulty2/difficulty2Probability;
        float rate3 = difficulty3/difficulty3Probability;
        float rate4 = difficulty4/difficulty4Probability;
        float rate5 = difficulty5/difficulty5Probability;
        float rateArr[5] = {rate1, rate2, rate3, rate4, rate5};
        float min = rate1;
        for(int i = 0; i < 5; i ++) {
            if(rateArr[i] < min) {
                min = rateArr[i];
                difficultyLevel = StringUtils::format("%d", i);
            }
        }
        int minConfig = TaskDifficultyLevelConfig::getIntByName(difficultyLevel, "min");
        int maxConfig = TaskDifficultyLevelConfig::getIntByName(difficultyLevel, "max");
        float rateConfig = (rand()%maxConfig + minConfig)/100.0f;  //在最大值和最小值中取一个随机值，得到浮动的值
        char* taskNameArr[]={"第一中学线上教育系统", "XX公司官网开发", "XX公司官网维护", "XX公司OA系统开发", "市第一医院医疗管理系统开发"};
        char* taskName = taskNameArr[rand()%5+0];
        Document levelConfigDoc;
        levelConfigDoc.Parse(levelConfig.c_str());
        int originalMoney = levelConfigDoc["money"].GetInt();
        int originalExp = levelConfigDoc["exp"].GetInt();
        int originalTime = levelConfigDoc["time"].GetInt();
        int originalPower = levelConfigDoc["power"].GetInt();
        int originalMp = levelConfigDoc["mp"].GetInt();
        int money = originalMoney + originalMoney*rateConfig;
        int exp = originalExp + originalExp*rateConfig;
        Task* task = new Task();
        task->setId(IdConfig::getIdByKey("taskId"));
        task->setMp(originalMp);
        task->setPower(originalPower);
        task->setName(taskName);
        task->setTime(originalTime);
        task->setMoney(money);
        task->setExp(exp);
        task->setLevel(role->getLevel());
        task->setStatus(0);
        TaskListService* taskListService = new TaskListService();
        taskListService->addTask(task);
        delete taskListService;
        delete task;
    }
    return NULL;
}