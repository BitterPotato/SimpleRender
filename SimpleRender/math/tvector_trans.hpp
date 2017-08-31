#ifndef TVECTOR_TRANS_HPP
#define TVECTOR_TRANS_HPP

#include "tvector.hpp"

namespace math{
	template<typename T>
	T cross(TVector2<T> va, TVector2<T> vb) {
		return va.x*vb.y - va.y*vb.x;
	}
	template<typename T>
	T dot(TVector2<T> va, TVector2<T> vb) {
		return va.x*vb.x + va.y*vb.y;
	}
}

#endif