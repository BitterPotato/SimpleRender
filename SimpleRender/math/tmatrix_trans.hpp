#ifndef TMATRIX_TRANS_HPP
#define TMATRIX_TRANS_HPP

#include "tmatrix.hpp"

namespace math {
	template<typename T, const int w, const int h>
	static inline TMatrixN<T, h, w> transpose(const TMatrixN<T, w, h>& matrixN) {
		TMatrixN<T, h, w> result;

		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
				result[j][i] = matrixN[i][j];

		return result;
	}

	//template<typename T, const int w, const int h>
	//static inline TMatrixN<T, w, h> inverse(const TMatrixN<T, w, h>& matrixN) {
	//	TMatrix<T, w, h> result;
	//	// TODO: some matrix don't have inverse
	//	return result;
	//}

	// -------------------- not universal --------------------
	template<typename T>
	static inline TMatrix3<T> asMat3(const TMatrix4<T> mat4) {
		return TMatrix3<T>(asVec3(static_cast<TVector4<T>>(mat4[0])), asVec3(static_cast<TVector4<T>>(mat4[1])), asVec3(static_cast<TVector4<T>>(mat4[2])));
	}

	template<typename T>
	static inline TMatrix4<T> asMat4(const TMatrix3<T> mat3) {
		TVector4<T> vec4(T(0), T(0), T(0), T(1));
		return TMatrix4<T>(asVec4_exp(static_cast<TVector3<T>>(mat3[0])), asVec4_exp(static_cast<TVector3<T>>(mat3[1])), asVec4_exp(static_cast<TVector3<T>>(mat3[2])), vec4);
	}

	template<typename T>
	static inline TMatrix4<T> translate(const TVector3<T> vec3) {
		TMatrix4<T> mat4(T(1));
		mat4[3][0] = vec3[0];
		mat4[3][1] = vec3[1];
		mat4[3][2] = vec3[2];
		return mat4;
	}

	template<typename T>
	static inline TMatrix3<T> scale3T(const TVector3<T> vec3) {
		TMatrix3<T> mat3(T(1));
		mat3[0][0] = vec3[0];
		mat3[1][1] = vec3[1];
		mat3[2][2] = vec3[2];
		return mat3;
	}

	template<typename T>
	static inline TMatrix4<T> scale4T(const TVector3<T> vec3) {
		return asMat4(scale3T(vec3));
	}

}

#include "tmatrix_rotate.hpp"
#include "tmatrix_gl.hpp"

#endif