//
// Created by LinusLan on 2018/5/18.
//

#ifndef PROJ_ANDROID_STUDIO_LOGINLAYER_H
#define PROJ_ANDROID_STUDIO_LOGINLAYER_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Classes/scene/home/HomeScene.h"
USING_NS_CC;
class LoginLayer : public Layer {
public:
    virtual bool init();
    CREATE_FUNC(LoginLayer);
};
#endif //PROJ_ANDROID_STUDIO_LOGINLAYER_H
