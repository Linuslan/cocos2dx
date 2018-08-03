//
// Created by LinusLan on 2018/6/25.
//

#ifndef PROJ_ANDROID_STUDIO_ROLE_H
#define PROJ_ANDROID_STUDIO_ROLE_H

#include "BaseEntity.h"
#include <string>

class Role : public BaseEntity {
private:
    //玩家等级
    int level=0;    //玩家角色当前等级
    float hp=100; //玩家角色当前的生命值
    float mp=100; //玩家角色当前的体力值
    float exp=0;  //玩家角色当前的经验值
    float money=0;    //玩家角色存款
    float power = 0;  //玩家角色当前的体力值
    std::string name;   //玩家角色的名称
    int type;   //玩家角色的职业类型，0：无职业；1：程序员；2：画家；
public:
    int getLevel() {return level;}
    float getHp() {return hp;}
    float getMp() {return mp;}
    float getExp() {return exp;}
    void setLevel(int level) {this->level=level;}
    void setHp(float hp) {this->hp = hp;}
    void setMp(float mp) {this->mp = mp;}
    void setExp(float exp) {this->exp = exp;}
    void levelUp() {this->level = this->level + 1;}
    void hpIncrease(float hp) {this->hp = this->hp + hp;}
    void hpReduce(float hp) {this->hp = this->hp - hp;}
    void mpIncrease(float hp) {this->mp = this->mp + mp;}
    void mpReduce(float mp) {this->mp = this->mp - mp;}
    void expIncrease(float exp) {this->exp = this->exp + exp;}
    void setName(std::string name) {this->name=name;}
    std::string getName() {return this->name;}
    int getMoney() {return this->money;}
    void addMoney(float money) {this->money = this->money + money;}
    void setType(int type) {this->type = type;}
    int getType() {return this->type;}
    void setPower(float power) {this->power = power;}
    float getPower() {return this->power;}
    void powerIncrease(float power) {this->power = this->power + power;}
    void powerReduce(float power) {this->power = this->power - power;}
};
#endif //PROJ_ANDROID_STUDIO_ROLE_H
