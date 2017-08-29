#ifndef FRAG_INL
#define FRAG_INL

#include "Frag.hpp"

inline Info& colorRatioInfo(const Info& info, float ratio) {
	BGRA* bgra = new BGRA{static_cast<int>(info.bgra->b*ratio), static_cast<int>(info.bgra->g*ratio), static_cast<int>(info.bgra->r*ratio), static_cast<int>(info.bgra->a*ratio)};
	Info* rInfo = new Info{bgra, info.depth, info.stencil };
	return *rInfo;
}
#endif
