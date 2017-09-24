//
// Created by WJ Yang on 2017/9/23.
//

#ifndef SIMPLERENDER_SHAPE_HPP
#define SIMPLERENDER_SHAPE_HPP

#include <math/TVector.hpp>

using Box2D = ivec4;
/**
 * TOP has small Y
 */
const int TOP = 0;
const int LEFT = 1;
const int BOTTOM = 2;
const int RIGHT = 3;

namespace Geometry {
    class Shape2D {
    public:
        virtual void asBoundingBox(Box2D& box) const = 0;
    };
}

#endif //SIMPLERENDER_SHAPE_HPP
