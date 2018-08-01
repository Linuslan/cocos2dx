//
// Created by LinusLan on 2018/8/1.
//

#include "TabView.h"
TabModel::TabModel(std::string title, Node *ct) {
    this->content = ct;
    this->name = new std::string(title);
    this->header = ui::Button::create("", "");
    Label* titleLbl = Label::createWithSystemFont(name->c_str(), "", 20);
    header->addChild(titleLbl);
    titleLbl->setPosition(header->getContentSize()/2);
}
TabModel::~TabModel() {
    if(nullptr != this->name) {
        delete name;
    }
    if(nullptr != this->content) {
        CC_SAFE_DELETE(content);
    }
    if(nullptr != this->header) {
        CC_SAFE_DELETE(header);
    }
}

bool TabView::init() {
    if(!Sprite::init()) {
        return false;
    }
    return true;
}

bool TabView::initTab(std::vector<TabModel *> *tabModels) {

}