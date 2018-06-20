//
// Created by LinusLan on 2018/6/20.
//

#include "BaseBtn.h"
bool BaseBtn::init() {
    if(!ui::Button::init()) {
        return false;
    }
    return true;
}

void BaseBtn::callback(Ref *ref) {

}