#ifndef COLOR_INL
#define COLOR_INL

#include "color.hpp"
#include "../math/basic.hpp"

inline BGRA* inter(const BGRA* from, const BGRA* to, const float t) {
	BGRA* bgra = new BGRA();
	bgra->b = (1 - t)*from->b + t*to->b;
	bgra->g = (1 - t)*from->g + t*to->g;
	bgra->r = (1 - t)*from->r + t*to->r;
	bgra->a = (1 - t)*from->a + t*to->a;

	return bgra;
}

inline BGRA operator*(const BGRA& bgra, const float ratio) {
	return { mround(bgra.b*ratio), mround(bgra.g*ratio), mround(bgra.r*ratio), mround(bgra.a*ratio) };
}


#endif