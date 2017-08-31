#ifndef TVECTOR_HPP
#define TVECTOR_HPP

template<typename T>
struct TVector2 {
	T x;
	T y;

	TVector2(T xx, T yy) {
		x = xx;
		y = yy;
	}
};


template<typename T>
struct TVector3 {
	T x;
	T y;
	T z;
};
#endif