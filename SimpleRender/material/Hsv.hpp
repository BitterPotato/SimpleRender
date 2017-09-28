//
// Created by WJ Yang on 2017/9/22.
//

#ifndef SIMPLERENDER_HSV_HPP
#define SIMPLERENDER_HSV_HPP

#include "common/setup.hpp"

class HSV {
public:
    HSV(int hh = 0, float ss = 0.0f, float vv = 0.0f) :
            h(hh), s(ss), v(vv) {}
    MY_OPERATOR_DECL bool operator==(const HSV& hsv) const {
        return h == hsv.h &&
               s >= hsv.s - epsilon &&
               s <= hsv.s + epsilon &&
               v >= hsv.v - epsilon &&
               v <= hsv.v + epsilon;
    }
private:
    int h; float s; float v;
};

#endif //SIMPLERENDER_HSV_HPP
