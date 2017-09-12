#ifndef TMATRIX_GL_HPP
#define TMATRIX_GL_HPP

#include "tmatrix.hpp"

#include <cmath>

using math::normalize;
using math::cross;
using math::asVec4_exp;
using math::transpose;
using math::translate;
using math::scale3T;
using math::scale4T;

using std::abs;
using std::tan;

namespace math {
	template<typename T>
	static TVector3<T>& asCameraPosi(const TMatrix4<T>& lookat) {
		return TVector3<T>(-lookat[3][0], -lookat[3][1], -lookat[3][2]);
	}

	template<typename T>
	static inline TMatrix4<T> lookatMatrix(const TVector3<T>& position,
		const TVector3<T>& center, const TVector3<T>& up) {
		TVector3<T> dirtVec = normalize(center - position);
		TVector3<T> beforeUpVec = normalize(up);

		TVector3<T> rightVec = normalize(cross(dirtVec, beforeUpVec));
		TVector3<T> afterUpVec = cross(rightVec, dirtVec);

		//TMatrix4<T> posiMatrix = TMatrix4<T>(T(1));
		//posiMatrix[3][0] = -position.x;
		//posiMatrix[3][1] = -position.y;
		//posiMatrix[3][2] = -position.z;
		TMatrix4<T> posiMatrix = translate(TVector3<T>(-position[0], -position[1], -position[2]));

		// treat the (0, 0, 1) as the default camera
		// and for the clip space to be (-1, -1, -1) to (1, 1, 1)
		//TMatrix4<T> posiMatrix = translate(TVector3<T>(-position[0], -position[1], 1-position[2]));

		TMatrix4<T> dirtMatrix = TMatrix4<T>(
			asVec4_exp(rightVec),
			asVec4_exp(afterUpVec),
			TVector4<T>(-dirtVec[0], -dirtVec[1], -dirtVec[2], 0),
			TVector4<T>(T(0), T(0), T(0), T(1))
		);
		dirtMatrix = transpose(dirtMatrix);

		return dirtMatrix*posiMatrix;
	}

	// happens after dividing w
	// attention: should pass into the float parameter
	template<typename T>
	static inline TMatrix3<T> viewportMatrix(const T& width, const T& height) {
		auto scaleVec = TVector3<T>(width / T(2), height / T(2), T(1));
		TMatrix3<T> scaleMatrix = scale3T(scaleVec);
		TMatrix3<T> translateMatrix = TMatrix3<T>(T(1));
		translateMatrix[2][0] = (width - T(1)) / T(2);
		translateMatrix[2][1] = (height - T(1)) / T(2);

		// first scale and then translate
		return translateMatrix*scaleMatrix;
	}

	// when viewport: (-1, -1) on the up-left instead of bottom-left
	template<typename T>
	static inline TMatrix3<T> viewportMatrixReflectY(const T& width, const T& height) {
		auto scaleVec = TVector3<T>(width / T(2), height / T(2), T(1));
		TMatrix3<T> scaleMatrix = scale3T(scaleVec);
		TMatrix3<T> translateMatrix = TMatrix3<T>(T(1));
		translateMatrix[2][0] = (width - T(1)) / T(2);
		translateMatrix[2][1] = (height - T(1)) / T(2);
		TMatrix3<T> reflectMatrix = TMatrix3<T>(T(1));
		reflectMatrix[1][1] = -1;

		// first scale and then translate
		return translateMatrix*scaleMatrix*reflectMatrix;
	}

	// inputs are the two diagonal points of entity (whatever which one is bigger)
	// attention: should pass into the float parameter
	template<typename T>
	static inline TMatrix4<T> frontviewMatrix(const TVector3<T>& pointThis, const TVector3<T>& pointThat) {
		T l = pointThis[0];
		T b = pointThis[1];
		T n = pointThis[2];
		T r = pointThat[0];
		T t = pointThat[1];
		T f = pointThat[2];

		auto translateVec = TVector3<T>(-(l+r)/2, -(b+t)/2, -(n+f)/2);
		TMatrix4<T> translateMatrix = translate(translateVec);
		auto scaleVec = TVector3<T>(2 /abs(r - l), 2 / abs(t - b), 2 / abs(n - f));
		TMatrix4<T> scaleMatrix = scale4T(scaleVec);

		// first translate and then scale
		return scaleMatrix*translateMatrix;
	}

	// attention: since the input points are related to the standard visual body, 
	// it may not seem intuitively for frustum(perspective)
	template<typename T>
	static inline TMatrix4<T> perspectiveMatrix(const TVector3<T>& pointThis, const TVector3<T>& pointThat) {
		T n = pointThis[2];
		T f = pointThat[2];

		TMatrix4<T> persMatrix = TMatrix4(
			TVector4<T>(n, 0, 0, 0),
			TVector4<T>(0, n, 0, 0),
			TVector4<T>(0, 0, n + f, 1),
			TVector4<T>(0, 0, -f*n, 0)
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
	static inline TMatrix4<T> perspectiveMatrix(const T& fovy, const T& aspect, const T& n, const T& f) {
		TMatrix4<T> persMatrix = TMatrix4<T>(
			TVector4<T>(n, 0, 0, 0),
			TVector4<T>(0, n, 0, 0),
			TVector4<T>(0, 0, n + f, 1),
			TVector4<T>(0, 0, -f*n, 0)
		);
		
		const T halfTanFovy = tan(fovy / T(2));
		T t = n*halfTanFovy;
		T r = aspect*t;
		T b = -t;
		T l = -r;

		TVector3<T> pointThis = TVector3<T>(l, b, n);
		TVector3<T> pointThat = TVector3<T>(r, t, f);

		// first transform frustum to standard visual body
		return frontviewMatrix(pointThis, pointThat) * persMatrix;
	}

}

#endif