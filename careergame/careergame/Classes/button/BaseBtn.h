//
// Created by LinusLan on 2018/6/20.
//

#ifndef PROJ_ANDROID_STUDIO_BASEBTN_H
#define PROJ_ANDROID_STUDIO_BASEBTN_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "DialogLayer.h"
#include "RoleSprite.h"
USING_NS_CC;
class BaseBtn:public ui::Button {
public:
    virtual bool init();
    CREATE_FUNC(BaseBtn);
    virtual void callback();
    virtual void doClick(Ref* ref);
};


#endif //PROJ_ANDROID_STUDIO_BASEBTN_H
