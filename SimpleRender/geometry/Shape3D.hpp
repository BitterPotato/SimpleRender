//
// Created by WJ Yang on 2017/9/23.
//

#ifndef SIMPLERENDER_SHAPE3D_HPP
#define SIMPLERENDER_SHAPE3D_HPP

#include <math/TVector.hpp>

using Box3D = TVectorN<int, 6>;

const int FRONT = 4;
const int BACK = 5;

namespace Geometry {
    class Shape3D {
    public:
        virtual void asBoundingBox(Box3D& box) const = 0;
    };
}


#endif //SIMPLERENDER_SHAPE3D_HPP
