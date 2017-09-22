#ifndef BLEND_HPP
#define BLEND_HPP

#include "../material/color.hpp"

#include <memory>
#include <algorithm>

using std::min;
using std::max;
using std::unique_ptr;

enum BLEND_OP : char {
	Add,
	Sub,
	Max, 
	Min
};

enum BLEND_FACTOR : char {
	One,
	Zero,
	SrcColor,
	SrcAlpha,
	DstColor,
	DstAlpha,
	OneMinusSrcColor,
	OneMinusSrcAlpha,
	OneMinusDstColor,
	OneMinusDstAlpha
};

class BlendOptions {
public:
	BlendOptions(BLEND_FACTOR srcFactor = SrcAlpha, BLEND_FACTOR dstFactor = OneMinusSrcAlpha, BLEND_OP op = Add) :
	mOp(op), mSrcFactor(srcFactor), mDstFactor(dstFactor){}

	friend BGRA* factorBGRA(const BLEND_FACTOR factor, const BLEND_FACTOR alphaFactor, const BGRA& src, const BGRA& dst, const BGRA& before);
	friend void blend(const BlendOptions& options, const BGRA& src, const BGRA& dst, BGRA& output);
private:
	BLEND_OP mOp;
	BLEND_FACTOR mSrcFactor;
	BLEND_FACTOR mDstFactor;

	BLEND_FACTOR mSrcAlphaFactor = SrcAlpha;
	BLEND_FACTOR mDstAlphaFactor = OneMinusSrcAlpha;
};
#endif