#ifndef TVECTOR_TRANS_HPP
#define TVECTOR_TRANS_HPP

#include "TVector.hpp"

namespace math{
	template<typename T, const int len>
	MY_SMALL_UTIL_DECL T dot(const TVectorN<T, len>& va, const TVectorN<T, len>& vb) ;

	template<typename T, const int len>
	MY_SMALL_UTIL_DECL T length(const TVectorN<T, len>& v) ;


	template<typename T, const int len>
	// notice: use type v is wrong
	//MY_SMALL_UTIL_DECL auto normalize(const TVectorN<T, len>& v) -> decltype(v) {
	MY_SMALL_UTIL_DECL auto normalize(const TVectorN<T, len>& v) ;
	
	// ------------------ not universal ------------------
	template<typename T>
	MY_SMALL_UTIL_DECL T det(const TVectorN<T, 2>& va, const TVectorN<T, 2>& vb) ;

	template<typename T>
	MY_SMALL_UTIL_DECL auto cross(const TVectorN<T, 3>& va, const TVectorN<T, 3>& vb) ;

	template<typename T>
	auto asVec3(const TVectorN<T, 4>& vec4) ;

	// for homogeneous coordinate
	template<typename T>
	auto asVec4_homo(const TVectorN<T, 3>& vec3) ;

	// just for enlarge
	template<typename T>
	auto asVec4_exp(const TVectorN<T, 3>& vec3) ;

	template<typename T>
	auto homogeneous(const TVectorN<T, 4>& vec4) ;
}

#include "TVector_Trans.inl"

#endif