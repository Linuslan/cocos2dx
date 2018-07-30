//
// Created by LinusLan on 2018/7/30.
//

#include <cmath>
#include "NumberUtils.h"
#include <iostream>
double linuslan::NumberUtils::formatDecimal(double num, int decimal) {
    int zoomIn = 1;
    for(int i = 0; i < decimal; i ++) {
        zoomIn = zoomIn*10;
    }
    long temp = round(num*zoomIn);
    return temp/(zoomIn*1.0f);
}