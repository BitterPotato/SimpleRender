#ifndef FRAG_INL
#define FRAG_INL

#include "Frag.hpp"

inline Info colorRatioInfo(const Info& info, float ratio) {
	Info rInfo;
	rInfo.bgra = {static_cast<int>(info.bgra.b*ratio), static_cast<int>(info.bgra.g*ratio), static_cast<int>(info.bgra.r*ratio), static_cast<int>(info.bgra.a*ratio)};
	rInfo.depth = info.depth;
	rInfo.stencil = info.stencil;
	return rInfo;
}
#endif
