#ifndef TMATRIX_GL_HPP
#define TMATRIX_GL_HPP

#include "TMatrix.hpp"

namespace math {
	template<typename T>
	MY_STORAGE_FUNC_DECL auto lookatMatrix(const TVectorN<T, 3>& position,
		const TVectorN<T, 3>& center, const TVectorN<T, 3>& up) ;
	// happens after dividing w
	// attention: should pass into the float parameter
	template<typename T>
	MY_STORAGE_FUNC_DECL auto viewportMatrix(const T& width, const T& height) ;

	// when viewport: (-1, -1) on the up-left instead of bottom-left
	template<typename T>
	MY_STORAGE_FUNC_DECL auto viewportMatrixReflectY(const T& width, const T& height) ;

	// inputs are the two diagonal points of entity (whatever which one is bigger)
	// attention: should pass into the float parameter
	template<typename T>
	MY_STORAGE_FUNC_DECL auto frontviewMatrix(const TVectorN<T, 3>& pointThis, const TVectorN<T, 3>& pointThat) ;

	// attention: since the input points are related to the standard visual body, 
	// it may not seem intuitively for frustum(perspective)
	template<typename T>
	MY_STORAGE_FUNC_DECL auto perspectiveMatrix(const TVectorN<T, 3>& pointThis, const TVectorN<T, 3>& pointThat) ;

	// FOV version
	// assume that:
	// 1. we look from the center of visual body
	// 2. there are no deformation happening
	/**
	fovy: the vertical field of view
	aspect: n_x / n_y of viewport
	**/
	template<typename T>
	MY_STORAGE_FUNC_DECL auto perspectiveMatrix(const T& fovy, const T& aspect, const T& n, const T& f) ;

}

#include "TMatrix_Gl.inl"

#endif