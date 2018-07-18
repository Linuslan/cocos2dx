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
public:
    virtual bool init();
    CREATE_FUNC(MoveLayer);
    void doGoLeft(float t);
    void doGoRight(float t);
};
#endif //PROJ_ANDROID_STUDIO_MOVELAYER_H
