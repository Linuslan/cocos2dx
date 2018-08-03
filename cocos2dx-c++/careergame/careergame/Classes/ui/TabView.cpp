//
// Created by LinusLan on 2018/8/1.
//

#include "TabView.h"
TabModel::TabModel(std::string title, Node *ct) {
    this->content = ct;
    this->name = new std::string(title);
    this->header = ui::Button::create("images/login/sure.png");
    Label* titleLbl = Label::createWithSystemFont(name->c_str(), "", 40);
    titleLbl->setColor(Color3B::BLACK);
    header->addChild(titleLbl);
    titleLbl->setPosition(header->getContentSize()/2);
}
TabModel::~TabModel() {
    if(nullptr != this->name) {
        delete name;
    }
}

bool TabView::init() {
    if(!Sprite::init()) {
        return false;
    }
    this->setTexture("test/background.png");
    this->headerPanel = Sprite::create();
    this->headerPanel->setContentSize(Size(this->getContentSize().width, this->getContentSize().height*0.2));
    log("headerPanel大小为：width=%f, height=%f", this->headerPanel->getContentSize().width, this->headerPanel->getContentSize().height);
    this->addChild(this->headerPanel);
    this->headerPanel->setPosition(Vec2(this->getContentSize().width*0.1, this->getContentSize().height*0.8));
    this->headerPanel->setAnchorPoint(Vec2::ZERO);
    log("headerPanel位置为：x=%f, y=%f", this->headerPanel->getPosition().x, this->headerPanel->getPosition().y);
    this->contentPanel = Sprite::create();
    this->contentPanel->setContentSize(Size(this->getContentSize().width, this->getContentSize().height-this->headerPanel->getContentSize().height));
    log("contentPanel大小为：width=%f, height=%f", this->contentPanel->getContentSize().width, this->contentPanel->getContentSize().height);
    this->addChild(this->contentPanel);
    this->contentPanel->setPosition(Vec2(this->getContentSize().width*0.1, this->getContentSize().height*0.1));
    this->contentPanel->setAnchorPoint(Vec2::ZERO);
    log("contentPanel位置为：x=%f, y=%f", this->contentPanel->getPosition().x, this->contentPanel->getPosition().y);
    this->tabs = new std::vector<TabModel*> ();
    return true;
}

TabView::TabView() {

}

TabView::~TabView() {
    log("调用~TabView()");
    if(nullptr != tabs) {
        log("开始删除tabs中的元素");
        for(std::vector<TabModel*>::iterator iter = tabs->begin(); iter != tabs->end(); iter ++) {
            delete *iter;
        }
        log("开始删除tabs");
        delete tabs;
    }
}

bool TabView::initTab(std::vector<TabModel *>* tabModels) {
    log("开始初始化tab");
    if(tabModels->empty()) {
        //如果为空的，则创建一个空的标签页
        return true;
    }
    int width = 0;
    int height = 0;
    TabModel* temp = tabModels->at(0);
    width = temp->getContent()->getContentSize().width + 100;
    height = temp->getContent()->getContentSize().height + temp->getHeader()->getContentSize().height + 100;
    this->setContentSize(Size(width, height));
    this->headerPanel->setContentSize(Size(this->getContentSize().width, this->getContentSize().height*0.1));
    this->headerPanel->setPosition(Vec2(this->getContentSize().width*0, this->getContentSize().height*0.8));
    this->contentPanel->setContentSize(Size(this->getContentSize().width, this->getContentSize().height-this->headerPanel->getContentSize().height));
    this->contentPanel->setPosition(Vec2(this->getContentSize().width*0, this->getContentSize().height*0));
    TabModel* model = nullptr;
    int i = 0;
    float headerStartX = headerPanel->getContentSize().width*0;
    int headerStartY = headerPanel->getContentSize().height*0;
    for(std::vector<TabModel*>::iterator iter = tabModels->begin(); iter != tabModels->end(); iter ++) {
        model = *iter;
        this->tabs->push_back(model);
        ui::Button* button = model->getHeader();
        button->setAnchorPoint(Vec2::ZERO);
        std::string name = "tab-"+StringUtils::format("%d", i);
        button->setName(name);
        headerPanel->addChild(button);
        log("button的宽度为：%f", button->getContentSize().width);
        log("生成的标签页的位置为：x=%f, y=%f", headerStartX, headerStartY);
        button->setPosition(Vec2(headerStartX, headerStartY));
        headerStartX = headerStartX+button->getContentSize().width;

        Node* node = model->getContent();
        node->setName("tab-"+StringUtils::format("%d", i));
        contentPanel->addChild(node);
        node->setPosition(contentPanel->getContentSize()/2);
        if(i > 0) {
            node->setVisible(false);
        }

        button->addClickEventListener([this, button](Ref* ref){
            log("==============点击了标签页===============");
            std::string name = button->getName();
            Vector<Node*> nodes = this->contentPanel->getChildren();
            for(Vector<Node*>::iterator iter2 = nodes.begin(); iter2 != nodes.end(); iter2 ++) {
                Node* node1 = *iter2;
                node1->setVisible(false);
            }
            Node* node2 = this->contentPanel->getChildByName(name);
            node2->setVisible(true);
        });
        i++;
    }
    tabCount = i;
    log("tab初始化成功，数量%d", tabCount);
    return true;
}

bool TabView::pushBackTab(std::string title, Node *content) {
    return true;
}