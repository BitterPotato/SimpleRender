#include "BlendOptions.hpp"

RGBA factorBGRA(const BLEND_FACTOR factor, const RGBA& src, const RGBA& dst, const RGBA& before) {

}
RGBA colorBlend(const BLEND_FACTOR factor, const RGBA& src, const RGBA& dst, const RGBA& before) {
	switch (factor) {
	case One:
		return RGBA(before);
	case Zero:
		return RGBA(0, 0, 0, 0);
	case SrcColor:
		return RGBA(toFloat(src[B])*before[B],
					toFloat(src[G])*before[G],
					toFloat(src[R])*before[R]);
	case DstColor:
		return RGBA(toFloat(dst[B])*before[B],
		toFloat(dst[G])*before[G],
		toFloat(dst[R])*before[R]);
	case OneMinusSrcColor:
		return RGBA((1 - toFloat(src[B]))*before[B],
		(1 - toFloat(src[G]))*before[G],
		(1 - toFloat(src[R]))*before[R]);

	case OneMinusDstColor:
		return RGBA((1 - toFloat(dst[B]))*before[B],
		(1 - toFloat(dst[G]))*before[G],
		(1 - toFloat(dst[R]))*before[R]);

	case SrcAlpha:
		return RGBA(before*toFloat(src[A]));
	case DstAlpha:
		return RGBA(before*toFloat(dst[A]));
	case OneMinusSrcAlpha:
		return RGBA(before*(1 - toFloat(src[A])));
	case OneMinusDstAlpha:
		return RGBA(before*(1 - toFloat(dst[A])));
	default:
		return RGBA(0, 0, 0, 0);
	}

	switch (alphaFactor) {
	case SrcAlpha:
		tSrc[A] = before[A] * toFloat(src[A]);
		break;
	case OneMinusSrcAlpha:
		tSrc[A] = before[A]*(1 - toFloat(src[A]));
		break;
	}
}

void blend(const BlendOptions& options, const RGBA& src, const RGBA& dst, RGBA& output) {
	unique_ptr<RGBA> tSrc = unique_ptr<RGBA>(colorBlend(options.mSrcFactor, options.mSrcAlphaFactor, src, dst, src));
	unique_ptr<RGBA> tDst = unique_ptr<RGBA>(colorBlend(options.mDstFactor, options.mDstAlphaFactor, src, dst, dst));

	switch (options.mOp) {
	case Add:
		output[B] = tSrc[B] + tDst[B];
		output[G] = tSrc[G] + tDst[G];
		output[R] = tSrc[R] + tDst[R];
		output[A] = tSrc[A] + tDst[A];
		break;
	case Sub:
		output[B] = tSrc[B] - tDst[B];
		output[G] = tSrc[G] - tDst[G];
		output[R] = tSrc[R] - tDst[R];
		output[A] = tSrc[A] - tDst[A];
		break;
	case Min:
		output[B] = min( tSrc[B], tDst[B]);
		output[G] = min( tSrc[G], tDst[G]);
		output[R] = min( tSrc[R], tDst[R]);
		output[A] = min( tSrc[A], tDst[A]);
		break;
	case Max:
		output[B] = max(tSrc[B], tDst[B]);
		output[G] = max(tSrc[G], tDst[G]);
		output[R] = max(tSrc[R], tDst[R]);
		output[A] = max(tSrc[A], tDst[A]);
		break;
	}
}