//
// Created by LinusLan on 2018/5/22.
//

#ifndef PROJ_ANDROID_STUDIO_HOMELAYER_H
#define PROJ_ANDROID_STUDIO_HOMELAYER_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "RoleSprite.h"
#include <exception>
#include <string>
USING_NS_CC;
class HomeLayer : public Layer {
public:
    virtual bool init();
    CREATE_FUNC(HomeLayer);
};
#endif //PROJ_ANDROID_STUDIO_HOMELAYER_H
