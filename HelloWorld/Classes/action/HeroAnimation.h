//
// Created by LinusLan on 2018/3/2.
//

#ifndef PROJ_ANDROID_STUDIO_HEROANIMATION_H
#define PROJ_ANDROID_STUDIO_HEROANIMATION_H

#include "cocos2d.h"
USING_NS_CC;
class HeroAnimation : public Animation {
private:
    Sprite* target;
    std::string name;
    int id;
public:
    HeroAnimation();
    ~HeroAnimation();
    static HeroAnimation* createWithSpriteFrames(const Vector<SpriteFrame*>& arrayOfSpriteFrameNames, float delay = 0.0f, unsigned int loops = 1);
    void setTarget(Sprite* sprite);
    Sprite* getTarget();
    int getId() {return id;}
    void setId(int i) {id=i;}
    std::string getName() {return name;}
    void setName(std::string name) {this->name = name;}
};
#endif //PROJ_ANDROID_STUDIO_HEROANIMATION_H
