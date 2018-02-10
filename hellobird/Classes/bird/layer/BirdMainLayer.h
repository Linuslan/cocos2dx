//
// Created by LinusLan on 2018/2/8.
//

#ifndef PROJ_ANDROID_STUDIO_MAINLAYER_H
#define PROJ_ANDROID_STUDIO_MAINLAYER_H

#include "cocos2d.h"
#include "cstdlib"
#include "ctime"
USING_NS_CC;
class BirdMainLayer : public Layer {
private:
    Sprite* topTube;
    Sprite* bottomTube;
    Sprite* bird;
public:
    virtual bool init();
    CREATE_FUNC(BirdMainLayer);
    void createTube(float a);
};
#endif //PROJ_ANDROID_STUDIO_MAINLAYER_H
