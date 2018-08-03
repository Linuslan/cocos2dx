//
// Created by LinusLan on 2018/7/19.
//

#ifndef PROJ_ANDROID_STUDIO_MOVELAYER2_H
#define PROJ_ANDROID_STUDIO_MOVELAYER2_H
#include "cocos2d.h"
USING_NS_CC;
class MoveLayer2: public Layer {
private:
    bool goLeft = false;
    float x = 0.0f;
    float y = 0.0f;
    float unwalkableY = 0.0f;
public:
    virtual bool init();
    CREATE_FUNC(MoveLayer2);
    void doGoLeft(float t);
    void doGoRight(float t);
    void doGoUp(float t);
    void doGoDown(float t);
    void setTargetPosition(Vec2 vec2);
    void autoWalk();
    Vec2 parseSysCoordToMapCoord(Vec2 vec2);
    Size moveSize(Vec2 vec2);   //传入的坐标，计算出屏幕需要移动到该坐标的距离
    void setUnwalkableY(float y) {this->unwalkableY = y;}
};
#endif //PROJ_ANDROID_STUDIO_MOVELAYER2_H
