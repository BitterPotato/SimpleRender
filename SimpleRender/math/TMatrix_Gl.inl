#ifndef TMATRIX_GL_INL
#define TMATRIX_GL_INL

#include "TMatrix_Gl.hpp"
#include "TMatrix_Trans.hpp"

namespace math {

    template<typename T>
    auto lookatMatrix(const TVectorN<T, 3> &position,
                      const TVectorN<T, 3> &center, const TVectorN<T, 3> &up) {
        auto dirtVec = normalize(center - position);
        auto beforeUpVec = normalize(up);

        auto rightVec = normalize(cross(dirtVec, beforeUpVec));
        auto afterUpVec = cross(rightVec, dirtVec);

        //TMatrix4<T> posiMatrix = TMatrix4<T>(T(1));
        //posiMatrix[3][0] = -position.x;
        //posiMatrix[3][1] = -position.y;
        //posiMatrix[3][2] = -position.z;
        auto posiMatrix = translate(TVectorN<T, 3>(-position[0], -position[1], -position[2]));

        // treat the (0, 0, 1) as the default camera
        // and for the clip space to be (-1, -1, -1) to (1, 1, 1)
        //TMatrix4<T> posiMatrix = translate(TVectorN<T, 3>(-position[0], -position[1], 1-position[2]));

        auto dirtMatrix = TMatrix4<T>(
                asVec4_exp(rightVec),
                asVec4_exp(afterUpVec),
                TVectorN<T, 4>(-dirtVec[0], -dirtVec[1], -dirtVec[2], 0),
                TVectorN<T, 4>(T(0), T(0), T(0), T(1))
        );
        dirtMatrix = transpose(dirtMatrix);

        return dirtMatrix * posiMatrix;
    }

// happens after dividing w
// attention: should pass into the float parameter
    template<typename T>
    auto viewportMatrix(const T &width, const T &height) {
        auto scaleVec = TVectorN<T, 3>(width / T(2), height / T(2), T(1));
        auto scaleMatrix = scale3T(scaleVec);
        auto translateMatrix = TMatrix3<T>(T(1));
        translateMatrix[2][0] = (width - T(1)) / T(2);
        translateMatrix[2][1] = (height - T(1)) / T(2);

        // first scale and then translate
        return translateMatrix * scaleMatrix;
    }

// when viewport: (-1, -1) on the up-left instead of bottom-left
    template<typename T>
    auto viewportMatrixReflectY(const T &width, const T &height) {
        auto scaleVec = TVectorN<T, 3>(width / T(2), height / T(2), T(1));
        auto scaleMatrix = scale3T(scaleVec);
        auto translateMatrix = TMatrix3<T>(T(1));
        translateMatrix[2][0] = (width - T(1)) / T(2);
        translateMatrix[2][1] = (height - T(1)) / T(2);
        auto reflectMatrix = TMatrix3<T>(T(1));
        reflectMatrix[1][1] = -1;

        // first scale and then translate
        return translateMatrix * scaleMatrix * reflectMatrix;
    }

// inputs are the two diagonal points of entity (whatever which one is bigger)
// attention: should pass into the float parameter
    template<typename T>
    auto frontviewMatrix(const TVectorN<T, 3> &pointThis, const TVectorN<T, 3> &pointThat) {
        T l = pointThis[0];
        T b = pointThis[1];
        T n = pointThis[2];
        T r = pointThat[0];
        T t = pointThat[1];
        T f = pointThat[2];

        auto translateVec = TVectorN<T, 3>(-(l + r) / 2, -(b + t) / 2, -(n + f) / 2);
        auto translateMatrix = translate(translateVec);
        auto scaleVec = TVectorN<T, 3>(2 / abs(r - l), 2 / abs(t - b), 2 / abs(n - f));
        auto scaleMatrix = scale4T(scaleVec);

        // first translate and then scale
        return scaleMatrix * translateMatrix;
    }

// attention: since the input points are related to the standard visual body,
// it may not seem intuitively for frustum(perspective)
    template<typename T>
    auto perspectiveMatrix(const TVectorN<T, 3> &pointThis, const TVectorN<T, 3> &pointThat) {
        T n = pointThis[2];
        T f = pointThat[2];

        auto persMatrix = TMatrix4<T>(
                TVectorN<T, 4>(n, 0, 0, 0),
                TVectorN<T, 4>(0, n, 0, 0),
                TVectorN<T, 4>(0, 0, n + f, 1),
                TVectorN<T, 4>(0, 0, -f * n, 0)
        );

        return frontviewMatrix(pointThis, pointThat) * persMatrix;
    }

// FOV version
// assume that:
// 1. we look from the center of visual body
// 2. there are no deformation happening
/**
fovy: the vertical field of view
aspect: n_x / n_y of viewport
**/
    template<typename T>
    auto perspectiveMatrix(const T &fovy, const T &aspect, const T &n, const T &f) {
        TMatrix4<T> persMatrix = TMatrix4<T>(
                TVectorN<T, 4>(n, 0, 0, 0),
                TVectorN<T, 4>(0, n, 0, 0),
                TVectorN<T, 4>(0, 0, n + f, 1),
                TVectorN<T, 4>(0, 0, -f * n, 0)
        );

        const T halfTanFovy = tan(fovy / T(2));
        T t = n * halfTanFovy;
        T r = aspect * t;
        T b = -t;
        T l = -r;

        auto pointThis = TVectorN<T, 3>(l, b, n);
        auto pointThat = TVectorN<T, 3>(r, t, f);

        // first transform frustum to standard visual body
        return frontviewMatrix(pointThis, pointThat) * persMatrix;
    }
}

#endif