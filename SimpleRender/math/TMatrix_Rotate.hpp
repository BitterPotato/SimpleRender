#ifndef TMATRIX_ROTATE_HPP
#define TMATRIX_ROTATE_HPP

//#define M_PI 3.1415926

#include "TMatrix.hpp"

// ----------------- matrix ------------------
namespace math {
	// should be called by input type: float
	template <typename T>
	MY_SMALL_NAME_FUNC_DECL T radians(const T angleInDegrees) ;
	template <typename T>
	MY_SMALL_NAME_FUNC_DECL T degrees(const T angleInRadians) ;

	MY_SMALL_NAME_FUNC_DECL fmat3 asXRotateMat(const float radians) ;
	MY_SMALL_NAME_FUNC_DECL fmat3 asYRotateMat(const float radians) ;
	MY_SMALL_NAME_FUNC_DECL fmat3 asZRotateMat(const float radians) ;

	MY_STORAGE_FUNC_DECL fvec3 noncollinear(const fvec3& axis) ;
	MY_STORAGE_FUNC_DECL fmat3 asRotateMat(const fvec3& axis, const float radians) ;

	// ----------------- euler ------------------
	// radians version
	MY_STORAGE_FUNC_DECL fmat3 eulerAsMatrix(const float pitch, const float yaw, const float roll, const string& order) ;

	// degrees version
	MY_STORAGE_FUNC_DECL fmat3 eulerAsMatrix(const int pi, const int ya, const int ro, const string& order) ;

	// ----------------- quaternion ------------------

}

#include "TMatrix_Rotate.inl"

#endif