#ifndef BASIC_INL
#define BASIC_INL

#include "Basic.hpp"

namespace math {
    int ipart(float x) {
        return static_cast<int>(x);
    }

    float fpart(float x) {
        return x - static_cast<float>(ipart(x));
    }

    float rfpart(float x) {
        return 1.0f - fpart(x);
    }

    int mround(float x) {
        return ipart(x + 0.5f);
    }
}

#endif