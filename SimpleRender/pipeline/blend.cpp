#include "blend.hpp"

inline float toFloat(int comp) {
    return static_cast<float>(comp) / LIMIT;
}

BGRA* factorBGRA(const BLEND_FACTOR factor, const BLEND_FACTOR alphaFactor, const BGRA& src, const BGRA& dst, const BGRA& before) {
	BGRA* tSrc;

	switch (factor) {
	case One:
		tSrc = new BGRA(before);
		break;
	case Zero:
		tSrc = new BGRA(0, 0, 0, 0);
		break;
	case SrcColor:
		tSrc = new BGRA();

		tSrc->b = toFloat(src.b)*before.b;
		tSrc->g = toFloat(src.g)*before.g;
		tSrc->r = toFloat(src.r)*before.r;
		break;
	case DstColor:
		tSrc = new BGRA();

		tSrc->b = toFloat(dst.b)*before.b;
		tSrc->g = toFloat(dst.g)*before.g;
		tSrc->r = toFloat(dst.r)*before.r;
		break;
	case OneMinusSrcColor:
		tSrc = new BGRA();

		tSrc->b = (1 - toFloat(src.b))*before.b;
		tSrc->g = (1 - toFloat(src.g))*before.g;
		tSrc->r = (1 - toFloat(src.r))*before.r;
		break;
	case OneMinusDstColor:
		tSrc = new BGRA();

		tSrc->b = (1 - toFloat(dst.b))*before.b;
		tSrc->g = (1 - toFloat(dst.g))*before.g;
		tSrc->r = (1 - toFloat(dst.r))*before.r;
		break;
	case SrcAlpha:
		tSrc = new BGRA(before*toFloat(src.a));
		break;
	case DstAlpha:
		tSrc = new BGRA(before*toFloat(dst.a));
		break;
	case OneMinusSrcAlpha:
		tSrc = new BGRA(before*(1 - toFloat(src.a)));
		break;
	case OneMinusDstAlpha:
		tSrc = new BGRA(before*(1 - toFloat(dst.a)));
		break;
	default:
		tSrc = new BGRA(0, 0, 0, 0);
		break;
	}

	switch (alphaFactor) {
	case SrcAlpha:
		tSrc->a = src.a * toFloat(src.a);
		break;
	case OneMinusSrcAlpha:
		tSrc->a = src.a*(1 - toFloat(src.a));
		break;
	}

	// move
	return tSrc;
}

void blend(const BlendOptions& options, const BGRA& src, const BGRA& dst, BGRA& output) {
	unique_ptr<BGRA> tSrc = unique_ptr<BGRA>(factorBGRA(options.mSrcFactor, options.mSrcAlphaFactor, src, dst, src));
	unique_ptr<BGRA> tDst = unique_ptr<BGRA>(factorBGRA(options.mDstFactor, options.mDstAlphaFactor, src, dst, dst));

	switch (options.mOp) {
	case Add:
		output.b = tSrc->b + tDst->b;
		output.g = tSrc->g + tDst->g;
		output.r = tSrc->r + tDst->r;
		output.a = tSrc->a + tDst->a;
		break;
	case Sub:
		output.b = tSrc->b - tDst->b;
		output.g = tSrc->g - tDst->g;
		output.r = tSrc->r - tDst->r;
		output.a = tSrc->a - tDst->a;
		break;
	case Min:
		output.b = min( tSrc->b, tDst->b);
		output.g = min( tSrc->g, tDst->g);
		output.r = min( tSrc->r, tDst->r);
		output.a = min( tSrc->a, tDst->a);
		break;
	case Max:
		output.b = max(tSrc->b, tDst->b);
		output.g = max(tSrc->g, tDst->g);
		output.r = max(tSrc->r, tDst->r);
		output.a = max(tSrc->a, tDst->a);
		break;
	}
}