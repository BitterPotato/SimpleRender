#ifndef TVECTOR_TRANS_INL
#define TVECTOR_TRANS_INL

#include "TVector_Trans.hpp"

namespace math{
    template<typename T, const int len>
     T dot(const TVectorN<T, len>& va, const TVectorN<T, len>& vb) {
        T ret = va[0] * vb[0];
        for (int i = 1; i < len; i++) {
            ret += va[i] * vb[i];
        }
        return ret;
    }

    template<typename T, const int len>
     T length(const TVectorN<T, len>& v) {
        T ret = v[0] * v[0];
        for (int i = 1; i < len; i++) {
            ret += v[i] * v[i];
        }
        return (T)sqrt(ret);
    }


    template<typename T, const int len>
    // notice: use type v is wrong
    // auto normalize(const TVectorN<T, len>& v) -> decltype(v) {
     auto normalize(const TVectorN<T, len>& v) {
        return v / length(v);
    }

//    template<typename T, const int len, typename Functor>
//    auto move(const TVectorN<T, len> v, const int n, Functor&& func) {
//        func(v[n]);
//        return v;
//    };
    // ------------------ not universal ------------------
    template<typename T>
     T det(const TVectorN<T, 2>& va, const TVectorN<T, 2>& vb) {
        T ret = va[0] * vb[1] - va[1] * vb[0];
        return ret;
    }

    template<typename T>
     auto cross(const TVectorN<T, 3>& va, const TVectorN<T, 3>& vb) {
        return TVectorN<T, 3>(
                va[1]*vb[2] - va[2]*vb[1],
                va[2] * vb[0] - va[0] * vb[2],
                va[0] * vb[1] - va[1] * vb[0]
        );
    }

    template<typename T>
    auto asVec3(const TVectorN<T, 4>& vec4) {
        return TVectorN<T, 3>(vec4[0], vec4[1], vec4[2]);
    }

    // for homogeneous coordinate
    template<typename T>
    auto asVec4_homo(const TVectorN<T, 3>& vec3) {
        return TVectorN<T, 4>(vec3[0], vec3[1], vec3[2], T(1));
    }

    // just for enlarge
    template<typename T>
    auto asVec4_exp(const TVectorN<T, 3>& vec3) {
        return TVectorN<T, 4>(vec3[0], vec3[1], vec3[2], T(0));
    }

    template<typename T>
    auto homogeneous(const TVectorN<T, 4>& vec4) {
        return TVectorN<T, 3>(vec4[0] / vec4[3], vec4[1] / vec4[3], vec4[2] / vec4[3]);
    }
}


#endif