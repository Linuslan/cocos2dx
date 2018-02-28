//
// Created by LinusLan on 2018/2/27.
//

#ifndef PROJ_ANDROID_STUDIO_ROLESPRITE_H
#define PROJ_ANDROID_STUDIO_ROLESPRITE_H

#include "cocos2d.h"
#include "cmath"
USING_NS_CC;
class HeroSprite : public Sprite {
private:
    std::string name;
    //图片资源
    std::string resource;
    SpriteFrameCache* sfc;
    float offsetX = 0.0f;    //人物在当前地图的坐标点
    float offsetY = 0.0f;    //人物在当前地图的坐标点
public:
    virtual bool init();
    CREATE_FUNC(HeroSprite);
    void walk(double degree);
    void stand();
    void update(float a);
};

#endif //PROJ_ANDROID_STUDIO_ROLESPRITE_H
