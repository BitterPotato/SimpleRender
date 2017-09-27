#ifndef GL_UTILS_HPP
#define GL_UTILS_HPP

#include "common/FVertex.hpp"

MY_SMALL_STORAGE_DECL void dicideAssignTo(const float& t, float& val) {
	if (t >= 0.0f && t <= 1.0f && t < val)
		val = t;
}

MY_STORAGE_FUNC_DECL float computeInterRatio(const FPoint4D& inPoint, const FPoint4D& outPoint) {
	float ix = inPoint[X];
	float iy = inPoint[Y];
	float iz = inPoint[Z];
	float iw = inPoint[W];

	float ox = outPoint[X];
	float oy = outPoint[Y];
	float oz = outPoint[Z];
	float ow = outPoint[W];

	// line segment: inPoint + t(VertexOut-inPoint)
	// t \in [0, 1]
	float val = 1.0f;
	float tx;
	if (outPoint[X] > inPoint[X]) {
		// will intersect with plane: x = iw + t(ow - iw)
		// notice: divide zero will not cause exception
		tx = (iw - ix) / ((ox - ow) - (ix - iw));
	}
	else {
		tx = (-iw - ix) / ((ox - ow) - (ix - iw));
	}
	dicideAssignTo(tx, val);
	float ty;
	if (outPoint[Y] > inPoint[Y]) {
		// will intersect with plane: x = iw + t(ow - iw)
		ty = (iw - iy) / ((oy - ow) - (iy - iw));
	}
	else {
		ty = (-iw - iy) / ((oy - ow) - (iy - iw));
	}
	dicideAssignTo(ty, val);
	float tz;
	if (outPoint[Z] > inPoint[Z]) {
		// will intersect with plane: x = iw + t(ow - iw)
		tz = (iw - iz) / ((oz - ow) - (iz - iw));
	}
	else {
		tz = (-iw - iz) / ((oz - ow) - (iz - iw));
	}
	dicideAssignTo(tz, val);

    return val;
}

MY_STORAGE_FUNC_DECL void computeInterSect(const FVertex& inVertex, const FVertex& outVertex, FVertex& sectVertex) {
    float ratio = computeInterRatio(inVertex.point, outVertex.point);
    inter(inVertex, outVertex, sectVertex, ratio);
}

#endif