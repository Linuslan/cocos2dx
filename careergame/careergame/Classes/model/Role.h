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
    int hp=100; //玩家角色当前的生命值
    int mp=100; //玩家角色当前的体力值
    int exp=0;  //玩家角色当前的经验值
    int money=0;    //玩家角色存款
    std::string name;   //玩家角色的名称
    int type;   //玩家角色的职业类型，0：无职业；1：程序员；2：画家；
public:
    Role();
    ~Role();
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
    void setName(std::string name) {this->name=name;}
    std::string getName() {return this->name;}
    int getMoney() {return this->money;}
    void addMoney(int money) {this->money = this->money + money;}
    void setType(int type) {this->type = type;}
    int getType() {return this->type;}
};
#endif //PROJ_ANDROID_STUDIO_ROLE_H
