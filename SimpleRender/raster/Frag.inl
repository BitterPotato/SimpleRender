#ifndef FRAG_INL
#define FRAG_INL

#include "Frag.hpp"

template<typename T>
inline void swap(T* outA, T* outB) {
	T temp = *outA;
	*outA = *outB;
	*outB = temp;
}

inline int ipart(float x) {
	return static_cast<int>(x);
}

inline float fpart(float x) {
	return x - static_cast<float>(ipart(x));
}

inline float rfpart(float x) {
	return 1.0f - fpart(x);
}

inline int mround(float x) {
	return ipart(x + 0.5f);
}

// TODO: remove this method
inline Info& colorRatioInfo(const Info& info, float ratio) {
	BGRA* bgra = new BGRA{static_cast<int>(info.bgra->b*ratio), static_cast<int>(info.bgra->g*ratio), static_cast<int>(info.bgra->r*ratio), static_cast<int>(info.bgra->a*ratio)};
	Info* rInfo = new Info{bgra, info.depth, info.stencil };
	return *rInfo;
}

inline BGRA operator*(const BGRA& bgra, const float ratio) {
	return { mround(bgra.b*ratio), mround(bgra.g*ratio), mround(bgra.r*ratio), mround(bgra.a*ratio) };
}
#endif
