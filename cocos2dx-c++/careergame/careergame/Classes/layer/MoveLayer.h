//
// Created by LinusLan on 2018/7/18.
//

#ifndef PROJ_ANDROID_STUDIO_MOVELAYER_H
#define PROJ_ANDROID_STUDIO_MOVELAYER_H

#include "cocos2d.h"
USING_NS_CC;
class MoveLayer: public Layer {
private:
    bool goLeft = false;
    float x = 0.0f;
    float y = 0.0f;
public:
    virtual bool init();
    CREATE_FUNC(MoveLayer);
    void doGoLeft(float t);
    void doGoRight(float t);
    void doGoUp(float t);
    void doGoDown(float t);
    void setTargetPosition(Vec2 vec2);
    void autoWalk();
    Vec2 parseSysCoordToMapCoord(Vec2 vec2);
};
#endif //PROJ_ANDROID_STUDIO_MOVELAYER_H
