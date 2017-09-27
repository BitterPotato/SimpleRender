#include "Rgba.hpp"

RGBA& RGBA::operator*(const float ratio) {
    for(auto& element : data)
        element *= ratio;

    return *this;
}

RGBA& RGBA::operator*=(const float ratio) {
    for(auto& element : data)
        element *= ratio;

    return *this;
}

HSV toHSV(const RGBA& rgba) {
    int r = rgba[R];
    int g = rgba[G];
    int b = rgba[B];

    int maxV = max(r, max(g, b));
    int minV = min(r, min(g, b));

    int h;
    float s, v;

    int diffV = maxV - minV;
    if (diffV == 0)
        h = 0;
    else if (maxV == r) {
        if (g >= b)
            h = 60 * (g - b) / diffV;
        else
            h = 60 * (g - b) / diffV + 360;
    }
    else if (maxV == g)
        h = 60 * (b - r) / diffV + 120;
    else
        h = 60 * (r - g) / diffV + 240;

    if (maxV == 0)
        s = 0;
    else
        s = static_cast<float>(diffV) / maxV;

    v = RGBA::toFloat(maxV);

    return HSV(h, s, v);
}