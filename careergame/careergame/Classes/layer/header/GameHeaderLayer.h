//
// Created by LinusLan on 2018/5/22.
//

#ifndef PROJ_ANDROID_STUDIO_GAMEHEADERLayer_H
#define PROJ_ANDROID_STUDIO_GAMEHEADERLayer_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "HelloWorldScene.h"
#include <exception>
#include <string>
USING_NS_CC;
class GameHeaderLayer: public Layer {
public:
    virtual bool init();
    CREATE_FUNC(GameHeaderLayer);
    void showTaskList();
};
#endif //PROJ_ANDROID_STUDIO_GAMEHEADERLayer_H
