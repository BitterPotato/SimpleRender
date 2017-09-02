#ifndef TVECTOR_TRANS_HPP
#define TVECTOR_TRANS_HPP

#include "tvector.hpp"

namespace math{
	template<typename T, const int len>
	static inline T dot(const TVectorN<T, len>& va, const TVectorN<T, len>& vb) {
		T ret = va[0] * vb[0];
		for (int i = 1; i < len; i++) {
			ret += va[i] * vb[i];
		}
		return ret;
	}

	template<typename T, const int len>
	static inline T length(const TVectorN<T, len>& v) {
		T ret = v[0] * v[0];
		for (int i = 1; i < len; i++) {
			ret += v[i] * v[i];
		}
		return (T)sqrt(ret);
	}

	template<typename T, const int len>
	static inline TVectorN<T, len> normalize(const TVectorN<T, len>& v) {
		return v / length(v);
	}
	
	// ------------------ not universal ------------------
	template<typename T>
	static inline T det(const TVector2<T>& va, const TVector2<T>& vb) {
		T ret = va[0] * vb[1] - va[1] * vb[0];
		return ret;
	}

	template<typename T>
	static inline TVector3<T> cross(const TVector3<T>& va, const TVector3<T>& vb) {
		return TVector3<T>(
			va[1]*vb[2] - va[2]*vb[1],
			va[2] * vb[0] - va[0] * vb[2],
			va[0] * vb[1] - va[1] * vb[0]
			);
	}

	template<typename T>
	TVector3<T> asVec3(const TVector4<T> vec4) {
		return TVector3(vec4[0], vec4[1], vec4[2]);
	}

	// for homogeneous coordinate
	template<typename T>
	TVector4<T> asVec4_homo(const TVector3<T> vec3) {
		return TVector3(vec3[0], vec3[1], vec3[2], T(1));
	}

	// just for enlarge
	template<typename T>
	TVector4<T> asVec4_exp(const TVector3<T> vec3) {
		return TVector3(vec3[0], vec3[1], vec3[2], T(0));
	}
}

#endif