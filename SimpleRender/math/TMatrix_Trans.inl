#ifndef TMATRIX_TRANS_INL
#define TMATRIX_TRANS_INL

#include "TMatrix_Trans.hpp"

namespace math {
    template<typename T, const int w, const int h>
    auto transpose(const TMatrixN<T, w, h>& matrixN) {
        TMatrixN<T, h, w> result;

        for (int i = 0; i < w; i++)
            for (int j = 0; j < h; j++)
                result[j][i] = matrixN[i][j];

        return result;
    }

    //template<typename T, const int w, const int h>
    //TMatrixN<T, w, h> inverse(const TMatrixN<T, w, h>& matrixN) {
    //	TMatrix<T, w, h> result;
    //	// TODO: some matrix don't have inverse
    //	return result;
    //}

    // -------------------- not universal --------------------
    template<typename T>
    auto asMat3(const TMatrix4<T> mat4) {
        return TMatrix3<T>(asVec3(static_cast<TVectorN<T, 3>>(mat4[0])), asVec3(static_cast<TVectorN<T, 3>>(mat4[1])), asVec3(static_cast<TVectorN<T, 3>>(mat4[2])));
    }

    template<typename T>
    auto asMat4(const TMatrix3<T> mat3) {
        TVectorN<T, 4> vec4(T(0), T(0), T(0), T(1));
        return TMatrix4<T>(asVec4_exp(static_cast<TVectorN<T, 3>>(mat3[0])), asVec4_exp(static_cast<TVectorN<T, 3>>(mat3[1])), asVec4_exp(static_cast<TVectorN<T, 3>>(mat3[2])), vec4);
    }

    template<typename T>
    auto translate(const TVectorN<T, 3> vec3) {
        TMatrix4<T> mat4(T(1));
        mat4[3][0] = vec3[0];
        mat4[3][1] = vec3[1];
        mat4[3][2] = vec3[2];
        return mat4;
    }

    template<typename T>
    auto scale3T(const TVectorN<T, 3> vec3) {
        TMatrix3<T> mat3(T(1));
        mat3[0][0] = vec3[0];
        mat3[1][1] = vec3[1];
        mat3[2][2] = vec3[2];
        return mat3;
    }

    template<typename T>
    auto scale4T(const TVectorN<T, 3> vec3) {
        return asMat4(scale3T(vec3));
    }

}

#endif