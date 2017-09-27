#ifndef TMATRIX_TRANS_HPP
#define TMATRIX_TRANS_HPP

#include "TMatrix.hpp"

namespace math {
	template<typename T, const int w, const int h>
	MY_STORAGE_FUNC_DECL auto transpose(const TMatrixN<T, w, h>& matrixN) ;

	//template<typename T, const int w, const int h>
	//MY_SMALL_NAME_FUNC_DECL TMatrixN<T, w, h> inverse(const TMatrixN<T, w, h>& matrixN) {
	//	TMatrix<T, w, h> result;
	//	// TODO: some matrix don't have inverse
	//	return result;
	//}

	// -------------------- not universal --------------------
	template<typename T>
	MY_SMALL_NAME_FUNC_DECL auto asMat3(const TMatrix4<T> mat4) ;

	template<typename T>
	MY_SMALL_NAME_FUNC_DECL auto asMat4(const TMatrix3<T> mat3) ;

	template<typename T>
	MY_SMALL_NAME_FUNC_DECL auto translate(const TVectorN<T, 3> vec3) ;

	template<typename T>
	MY_SMALL_NAME_FUNC_DECL auto scale3T(const TVectorN<T, 3> vec3) ;

	template<typename T>
	MY_SMALL_NAME_FUNC_DECL auto scale4T(const TVectorN<T, 3> vec3) ;

}

#include "TMatrix_Trans.inl"

#endif