//
// Created by WJ Yang on 2017/9/23.
//

#include "Triangle3D.hpp"

namespace Geometry {
    template <typename T>
    float Triangle3D<T>::distToTri(const vec3<T>& view) const {
        return dot(normal, view) + remainder;
    }

    template <typename T>
    float Triangle3D<T>::intersectToTri(const Point3D<T>& vThis, const Point3D<T>& vThat) const {
        fvec3 vecThis = asVec3(vThis);
        fvec3 vecThat = asVec3(vThat);

        return -(remainder + dot(vecThis, normal) / dot(normal, vecThat - vecThis));
    }

}