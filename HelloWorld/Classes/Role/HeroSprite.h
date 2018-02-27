//
// Created by LinusLan on 2018/2/27.
//

#ifndef PROJ_ANDROID_STUDIO_ROLESPRITE_H
#define PROJ_ANDROID_STUDIO_ROLESPRITE_H

#include "cocos2d.h"
USING_NS_CC;
class HeroSprite : public Sprite {
private:
    std::string name;
    //图片资源
    std::string resource;
    SpriteFrameCache* sfc;
public:
    virtual bool init();
    CREATE_FUNC(HeroSprite);
    void walk();
    void stand();
    void update(float a);
};

#endif //PROJ_ANDROID_STUDIO_ROLESPRITE_H
