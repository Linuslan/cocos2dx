//
// Created by LinusLan on 2018/7/25.
//

#ifndef PROJ_ANDROID_STUDIO_TASK_H
#define PROJ_ANDROID_STUDIO_TASK_H

#include "BaseEntity.h"

class Task: public BaseEntity {
private:
    int id = 0;
    char* name = nullptr;
    int money = 0;
    int exp = 0;
    int time = 0;   //需要消耗的时间
    int power = 0;  //需要消耗的能量
    int mp = 0; //需要消耗的MP
    int level = 0;  //等级
    int status = 0;
    int difficultyLevel = 0;
public:
    ~Task();
    void setId(int id) {this->id = id;}
    int getId() {return this->id;}
    void setName(char* name) {this->name = name;}
    char* getName() {return this->name;}
    void setMoney(int money) {this->money = money;}
    int getMoney() {return this->money;}
    void setExp(int exp) {this->exp = exp;}
    int getExp() {return this->exp;}
    void setTime(int time) {this->time = time;}
    int getTime() {return this->time;}
    void setPower(int power) {this->power = power;}
    int getPower() {return this->power;}
    void setMp(int mp) {this->mp = mp;}
    int getMp() {return this->mp;}
    void setLevel(int level) {this->level = level;}
    int getLevel() {return this->level;}
    void setStatus(int status) {this->status = status;}
    int getStatus() {return this->status;}
    void setDifficultyLevel(int difficultyLevel) {this->difficultyLevel = difficultyLevel;}
    int getDifficultyLevel() {return this->difficultyLevel;}
};
#endif //PROJ_ANDROID_STUDIO_TASK_H
