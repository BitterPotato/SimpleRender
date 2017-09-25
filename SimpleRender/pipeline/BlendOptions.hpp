#ifndef BLEND_HPP
#define BLEND_HPP

#include "material/Rgba.hpp"

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

	MY_NFRIEND_FUNC_DECL void blend(const BlendOptions& options, const RGBA& src, const RGBA& dst, RGBA& output);
private:
	BLEND_OP mOp;
	BLEND_FACTOR mSrcFactor;
	BLEND_FACTOR mDstFactor;

	BLEND_FACTOR mSrcAlphaFactor = SrcAlpha;
	BLEND_FACTOR mDstAlphaFactor = OneMinusSrcAlpha;


	MY_UTIL_DECL void blendCompo(const BLEND_FACTOR factor, const BLEND_FACTOR alphaFactor,
										 const RGBA &src, const RGBA &dst,
										  const RGBA &before, RGBA& after);
	MY_UTIL_DECL void alphaBlend(const BLEND_FACTOR alphaFactor, const RGBA &src, const RGBA &dst,
										 const RGBA &before, RGBA& after);
	MY_UTIL_DECL void colorBlend(const BLEND_FACTOR factor, const RGBA &src, const RGBA &dst,
										 const RGBA &before, RGBA& after);
};
#endif