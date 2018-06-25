//
// Created by LinusLan on 2018/6/13.
//

#ifndef PROJ_ANDROID_STUDIO_ROLESPRITE_H
#define PROJ_ANDROID_STUDIO_ROLESPRITE_H

#include "cocos2d.h"
#include "BaseBtn.h"
#include <exception>
USING_NS_CC;
class RoleSprite : public Sprite {
private:
    //需要角色走过去的对象
    BaseBtn* targetObj;
    //走到坐标后需要执行的按钮
    BaseBtn* targetBtn;
    //玩家等级
    int level=0;
    int hp=100;
    int mp=100;
    int exp=0;
public:
    virtual bool init();
    CREATE_FUNC(RoleSprite);
    void walk();
    void standFront();
    void standBack();
    void standSide();
    void update(float a);
    void setTargetBtn(BaseBtn* targetBtn) {this->targetBtn=targetBtn;}
    void setTargetObj(BaseBtn* targetObj) {this->targetObj = targetObj;}
    void (*callback)();
    int getLevel() {return level;}
    int getHp() {return hp;}
    int getMp() {return mp;}
    int getExp() {return exp;}
    void setLevel(int level) {this->level=level;}
    void setHp(int hp) {this->hp = hp;}
    void setMp(int mp) {this->mp = mp;}
    void setExp(int exp) {this->exp = exp;}
    void levelUp() {this->level = this->level + 1;}
    void hpIncrease(int hp) {this->hp = this->hp + hp;}
    void hpReduce(int hp) {this->hp = this->hp - hp;}
    void mpIncrease(int hp) {this->mp = this->mp + mp;}
    void mpReduce(int mp) {this->mp = this->mp - mp;}
    void expIncrease(int exp) {this->exp = this->exp + exp;}
};
#endif //PROJ_ANDROID_STUDIO_ROLESPRITE_H
