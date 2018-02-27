//
// Created by LinusLan on 2018/2/24.
//

#ifndef PROJ_ANDROID_STUDIO_MOVELAYER_H
#define PROJ_ANDROID_STUDIO_MOVELAYER_H
#include "cocos2d.h"
#include "cmath"
#include "HeroSprite.h"
USING_NS_CC;
class MoveSprite : public Sprite {
public:
    virtual bool init();
    CREATE_FUNC(MoveSprite);
    void onMoveTouchesBegan(const std::vector<Touch*>& touches, Event* event);
    void onMoveTouchesMoved(const std::vector<Touch*>& touches, Event* event);
    void onMoveTouchesEnded(const std::vector<Touch*>& touches, Event* event);
};
#endif //PROJ_ANDROID_STUDIO_MOVELAYER_H