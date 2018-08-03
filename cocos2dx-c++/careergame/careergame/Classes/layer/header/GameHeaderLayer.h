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
    void showTaskList(Ref* ref);
    void update(float t);
    void showShop(Ref* ref);
    Node* showFurniture();
    Node* showFood();
};
#endif //PROJ_ANDROID_STUDIO_GAMEHEADERLayer_H
