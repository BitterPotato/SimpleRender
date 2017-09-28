#ifndef COLOR_INL
#define COLOR_INL

#include "Rgba.hpp"
#include "math/Basic.hpp"

using math::mround;

RGBA inter(const RGBA& from, const RGBA& to, const float t) {
	RGBA rgba;
	for(int i=0; i<CAPACITY; i++)
		rgba[i] = (1-t)*from[i] + t*to[i];

	return rgba;
}

RGBA inter(const RGBA& first, const RGBA& second, const RGBA& third, RGBA& outRgba, const fvec3& ratio) {
    outRgba[B] = first[B]*ratio[0] + second[B]*ratio[1] + third[B]*ratio[2];
    outRgba[G] = first[G]*ratio[0] + second[G]*ratio[1] + third[G]*ratio[2];
    outRgba[R] = first[R]*ratio[0] + second[R]*ratio[1] + third[R]*ratio[2];
    outRgba[A] = first[A]*ratio[0] + second[A]*ratio[1] + third[A]*ratio[2];
}


RGBA operator*(const RGBA& rgba, const float ratio) {
	return RGBA( mround(rgba[R]*ratio), mround(rgba[G]*ratio), mround(rgba[B]*ratio), mround(rgba[A]*ratio) );
}


#endif