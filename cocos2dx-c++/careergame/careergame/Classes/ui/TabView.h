//
// Created by LinusLan on 2018/8/1.
//

#ifndef PROJ_ANDROID_STUDIO_TABVIEW_H
#define PROJ_ANDROID_STUDIO_TABVIEW_H

#include <ui/UIButton.h>
#include "cocos2d.h"
USING_NS_CC;
class TabModel {
private:
    std::string* name = nullptr;
    ui::Button* header = nullptr;
    Node* content = nullptr;
public:
    TabModel(std::string title, Node* ct);
    ~TabModel();
    std::string* getName() {return name;}
    ui::Button* getHeader() {return header;}
    Node* getContent() {return content;}
};
class TabView : public Sprite {
private:
    int tabCount;   //设置标签页的个数
    std::vector<TabModel*>* tabs = nullptr;
    Sprite* headerPanel = nullptr;
    Sprite* contentPanel = nullptr;
public:
    TabView();
    ~TabView();
    virtual bool init();
    bool initTab(std::vector<TabModel*>* tabModels);
    CREATE_FUNC(TabView);
    bool pushBackTab(std::string title, Node* content);
};
#endif //PROJ_ANDROID_STUDIO_TABVIEW_H
