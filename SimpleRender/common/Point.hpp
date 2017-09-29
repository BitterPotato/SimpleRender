//
// Created by WJ Yang on 2017/9/22.
//

#ifndef SIMPLERENDER_COMMON_POINT_HPP
#define SIMPLERENDER_COMMON_POINT_HPP

#include "math/TVector.hpp"

template <typename T>
using Point2D = TVectorN<T, 2>;
template <typename T>
using Point3D = TVectorN<T, 3>;
//template <typename T>
//using Point4D = TVectorN<T, 4>;

using IPoint2D = ivec2;
//using FPoint2D = fvec2;
//using IPoint3D = ivec3;
using FPoint3D = fvec3;
//using IPoint4D = ivec4;
using FPoint4D = fvec4;

const int X = 0;
const int Y = 1;
const int Z = 2;
const int W = 3;

using TexCoord = fvec2;

const int U = 0;
const int V = 1;


MY_SMALL_STORAGE_DECL bool isInVisualBody(const FPoint4D& point) {
    return point[X] >= -point[W] && point[X] <= point[W]
           && point[Y] >= -point[W] && point[Y] <= point[W]
           && point[Z] >= -point[W] && point[Z] <= point[W];
}

// use define as default parameter
// code smell
/*if construct by the form like: Macro_FPoint4D test(0.0f, 1.0f， 0.0f), then will assert fail*/
#define Macro_FPoint4D(x, y, z) FPoint4D(x, y, z, 1.0f)

#endif //SIMPLERENDER_COMMON_POINT_HPP
