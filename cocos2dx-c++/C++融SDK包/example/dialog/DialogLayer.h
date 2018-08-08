//
// Created by LinusLan on 2018/4/3.
//

#ifndef PROJ_ANDROID_STUDIO_DIALOGLAYER_H
#define PROJ_ANDROID_STUDIO_DIALOGLAYER_H

#include <cocos2d/cocos/ui/UITextBMFont.h>
#include "cocos2d.h"
USING_NS_CC;

class DialogLayer : public Layer {
private:
    double price = 0.0f;
public:
    typedef std::function<void(int)> dialogCallback;
    dialogCallback callback = nullptr;
    virtual bool init();
    CREATE_FUNC(DialogLayer);
    void setPrice(double price) {this->price = price;}
    //void (*callback)(Label* label, ui::TextBMFont* font);

    void setCallback(const dialogCallback& f);
};
#endif //PROJ_ANDROID_STUDIO_DIALOGLAYER_H
