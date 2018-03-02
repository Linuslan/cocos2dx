//
// Created by LinusLan on 2018/3/1.
//

#ifndef PROJ_ANDROID_STUDIO_SPEAR_H
#define PROJ_ANDROID_STUDIO_SPEAR_H

#include "Weapon.h"

class Spear : public Weapon {
public:
    virtual bool init();
    CREATE_FUNC(Spear);
    void stand();
    void walk();
    void fight();
};
#endif //PROJ_ANDROID_STUDIO_SPEAR_H
