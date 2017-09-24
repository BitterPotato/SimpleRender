//
// Created by WJ Yang on 2017/9/22.
//

#ifndef SIMPLERENDER_HSV_HPP
#define SIMPLERENDER_HSV_HPP

class HSV {
public:
    HSV(int hh = 0, float ss = 0.0f, float vv = 0.0f) :
            h(hh), s(ss), v(vv) {}

private:
    int h; float s; float v;
};

#endif //SIMPLERENDER_HSV_HPP
