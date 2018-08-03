//
// Created by LinusLan on 2018/5/22.
//

#ifndef PROJ_ANDROID_STUDIO_HOMESCENE_H
#define PROJ_ANDROID_STUDIO_HOMESCENE_H

#include "cocos2d.h"
#include "GameHeaderLayer.h"
#include "Classes/layer/home/HomeLayer.h"
#include <exception>
#include <string>
#include "MoveLayer.h"
USING_NS_CC;
class HomeScene : public Scene {
public:
    virtual bool init();
    CREATE_FUNC(HomeScene);
};
#endif //PROJ_ANDROID_STUDIO_HOMESCENE_H
