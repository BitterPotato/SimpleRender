#ifndef SIMPLERENDER_TRIANGLE3D_INL
#define SIMPLERENDER_TRIANGLE3D_INL

namespace Geometry {
    template <typename T>
    float Triangle3D<T>::distToTri(const vec3<T>& view) const {
        return dot(normal, view) + remainder;
    }

    template <typename T>
    float Triangle3D<T>::intersectToTri(const Point3D<T>& vThis, const Point3D<T>& vThat) const {
        return -(remainder + dot(vThis, normal) / dot(normal, vThat - vThis));
    }

}

#endif