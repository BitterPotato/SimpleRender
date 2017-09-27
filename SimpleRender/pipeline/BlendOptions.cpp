#include "BlendOptions.hpp"

void BlendOptions::blendCompo(const BLEND_FACTOR factor, const BLEND_FACTOR  alphaFactor, const RGBA& src, const RGBA& dst, const RGBA& before, RGBA& after) {
	colorBlend(factor, src, dst, before, after);
	alphaBlend(alphaFactor, src, dst, before, after);
}
void BlendOptions::alphaBlend(const BLEND_FACTOR alphaFactor, const RGBA& src, const RGBA& dst, const RGBA& before, RGBA& after) {
	switch (alphaFactor) {
		case SrcAlpha:
			after[A] = before[A] * RGBA::toFloat(src[A]);
			break;
		case OneMinusSrcAlpha:
			after[A] = before[A]*(1 - RGBA::toFloat(src[A]));
			break;
	}
}
void BlendOptions::colorBlend(const BLEND_FACTOR factor, const RGBA& src, const RGBA& dst, const RGBA& before, RGBA& after) {
	switch (factor) {
	case One:
		after = RGBA(before);
	case Zero:
		after = RGBA(0, 0, 0, 0);
	case SrcColor:
		after = RGBA(RGBA::toFloat(src[B])*before[B],
					RGBA::toFloat(src[G])*before[G],
					RGBA::toFloat(src[R])*before[R]);
	case DstColor:
		after = RGBA(RGBA::toFloat(dst[B])*before[B],
		RGBA::toFloat(dst[G])*before[G],
		RGBA::toFloat(dst[R])*before[R]);
	case OneMinusSrcColor:
		after = RGBA((1 - RGBA::toFloat(src[B]))*before[B],
		(1 - RGBA::toFloat(src[G]))*before[G],
		(1 - RGBA::toFloat(src[R]))*before[R]);

	case OneMinusDstColor:
		after = RGBA((1 - RGBA::toFloat(dst[B]))*before[B],
		(1 - RGBA::toFloat(dst[G]))*before[G],
		(1 - RGBA::toFloat(dst[R]))*before[R]);

	case SrcAlpha:
		after = RGBA(before*RGBA::toFloat(src[A]));
	case DstAlpha:
		after = RGBA(before*RGBA::toFloat(dst[A]));
	case OneMinusSrcAlpha:
		after = RGBA(before*(1 - RGBA::toFloat(src[A])));
	case OneMinusDstAlpha:
		after = RGBA(before*(1 - RGBA::toFloat(dst[A])));
	default:
		after = RGBA(0, 0, 0, 0);
	}
}


void blend(const BlendOptions& options, const RGBA& src, const RGBA& dst, RGBA& output) {
	RGBA srcCompo, dstCompo;

	BlendOptions::blendCompo(options.mSrcFactor, options.mSrcAlphaFactor, src, dst, src, srcCompo);
	BlendOptions::blendCompo(options.mDstFactor, options.mDstAlphaFactor, src, dst, dst, dstCompo);

	switch (options.mOp) {
	case Add:
		output[B] = srcCompo[B] + dstCompo[B];
		output[G] = srcCompo[G] + dstCompo[G];
		output[R] = srcCompo[R] + dstCompo[R];
		output[A] = srcCompo[A] + dstCompo[A];
		break;
	case Sub:
		output[B] = srcCompo[B] - dstCompo[B];
		output[G] = srcCompo[G] - dstCompo[G];
		output[R] = srcCompo[R] - dstCompo[R];
		output[A] = srcCompo[A] - dstCompo[A];
		break;
	case Min:
		output[B] = min( srcCompo[B], dstCompo[B]);
		output[G] = min( srcCompo[G], dstCompo[G]);
		output[R] = min( srcCompo[R], dstCompo[R]);
		output[A] = min( srcCompo[A], dstCompo[A]);
		break;
	case Max:
		output[B] = max(srcCompo[B], dstCompo[B]);
		output[G] = max(srcCompo[G], dstCompo[G]);
		output[R] = max(srcCompo[R], dstCompo[R]);
		output[A] = max(srcCompo[A], dstCompo[A]);
		break;
	}
}