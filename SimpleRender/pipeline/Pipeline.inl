#ifndef STAGE_FLOW_INL
#define STAGE_FLOW_INL

#include "Pipeline.hpp"

#include "common/Vertex.hpp"
#include "common/FVertex.hpp"
#include "common/Info.hpp"
#include "math/TVector_Trans.hpp"

using math::homogeneous;

void Pipeline::pipeTrans(FVertex& fVertex) const {
    fvec4 outCoord4(fVertex.point[X], fVertex.point[Y], fVertex.point[Z], 1.0f);
    // 1. Model - World Transform
    // 2. World - Camera Transform
    // 3. Camera - Clip Transform
    outCoord4 = mRenderState.mLookatMatrix*mRenderState.mTransformMatrix*outCoord4;
    outCoord4 = mRenderState.mProjMatrix*outCoord4;
    //outCoord4 = mProjMatrix*mLookatMatrix*mTransformMatrix*outCoord4;

    fVertex.point = outCoord4;
}

void Pipeline::afterClip(const FVertex& fVertex, Vertex& outVertex) const {
    // 3_5. as for perspective projection, needs a stage called 'Homogeneous'
    fvec3 outCoord3 = homogeneous(fvec4(fVertex.point[X], fVertex.point[Y], fVertex.point[Z], fVertex.point[W]));

    // 4. Clip - Viewport Transform
    outCoord3[2] = 1.0f;
    outCoord3 = mRenderState.mViewportMatrix * outCoord3;

    // output
    outVertex.point[X] = outCoord3[0];
    outVertex.point[Y] = outCoord3[1];

    // save info that doesn't change
    outVertex.info.rgba = fVertex.rgba;
    // with bigger z, the depth is lower, for we look at -z
    outVertex.info.depth = -fVertex.point[Z];
    outVertex.tex = fVertex.tex;

    // save homogeneous info
    outVertex.homo = fVertex.point[W];
}

#endif