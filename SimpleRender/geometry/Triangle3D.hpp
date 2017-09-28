//
// Created by WJ Yang on 2017/9/23.
//

#ifndef SIMPLERENDER_TRIANGLE3D_HPP
#define SIMPLERENDER_TRIANGLE3D_HPP

#include <common/Point.hpp>
#include <math/TVector_Trans.hpp>

using math::cross;
using math::dot;
using math::asVec3;

namespace Geometry {
    template <typename T>
    class Triangle3D {
    public:
        Triangle3D(const Point3D<T>& a, const Point3D<T>& b, const Point3D<T>& c) :
                pA(a), pB(b), pC(c) {
            vec3<T> vecAB = vec3<T>(b[X] - a[X], b[Y] - a[Y], b[Z] - a[Z]);
            vec3<T> vecBC = vec3<T>(c[X] - b[X], c[Y] - b[Y], c[Z] - b[Z]);
            vec3<T> cordA = vec3<T>(a[X], a[Y], a[Z]);
            normal = cross(vecAB, vecBC);
            remainder = -dot(normal, cordA);
        }
        // -: from v to see tri, tri is anticlockwise
        // 0: on tri
        // +: from v to see tri, tri is clockwise
        MY_SMALL_FUNC_DECL float distToTri(const vec3<T>& view) const ;
        MY_SMALL_FUNC_DECL float intersectToTri(const Point3D<T>& vThis, const Point3D<T>& vThat) const ;

    protected:
        const Point3D<T> &pA, pB, pC;
        vec3<T> normal;
        float remainder;
    };

    using FTriangle3D = Triangle3D<float>;
}

#include "Triangle3D.inl"

#endif //SIMPLERENDER_TRIANGLE3D_HPP
