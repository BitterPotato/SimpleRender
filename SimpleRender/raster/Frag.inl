#ifndef FRAG_INL
#define FRAG_INL

#include "Frag.hpp"

// TODO: remove this method
inline Info& colorRatioInfo(const Info& info, float ratio) {
	BGRA* bgra = new BGRA{static_cast<int>(info.bgra->b*ratio), static_cast<int>(info.bgra->g*ratio), static_cast<int>(info.bgra->r*ratio), static_cast<int>(info.bgra->a*ratio)};
	Info* rInfo = new Info{bgra, info.depth, info.stencil };
	return *rInfo;
}

inline BGRA operator*(const BGRA& bgra, const float ratio) {
	return { mround(bgra.r*ratio), mround(bgra.g*ratio), mround(bgra.b*ratio), mround(bgra.a*ratio) };
}
#endif