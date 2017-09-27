//
// Created by WJ Yang on 2017/9/23.
//

#ifndef SIMPLERENDER_SHAPE_HPP
#define SIMPLERENDER_SHAPE_HPP

#include <math/TVector.hpp>

template <typename T>
using Box2D = TVectorN<T, 4>;
using IBox2D = TVectorN<int, 4>;

/**
 * TOP has small Y
 */
const int TOP = 0;
const int LEFT = 1;
const int BOTTOM = 2;
const int RIGHT = 3;

namespace Geometry {
    template<typename T>
    class Shape2D {
    public:
        virtual void asBoundingBox(Box2D<T>& box) const = 0;
    };
}

#endif //SIMPLERENDER_SHAPE_HPP
