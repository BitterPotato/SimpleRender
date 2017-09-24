#ifndef GL_UTILS_HPP
#define GL_UTILS_HPP

#include "common/Frag.hpp"

inline bool isInVisualBody(const FVertex& fVertex) {
	float x = fVertex.point[X];
	float y = fVertex.point[Y];
	float z = fVertex.point[Z];
	float w = fVertex.point[W];

	return x >= -w && x <= w
		&& y >= -w && y <= w
		&& z >= -w && z <= w;
}

inline void dicideAssignTo(const float& t, float& val) {
	if (t >= 0.0f && t <= 1.0f && t < val)
		val = t;
}

static void computeInterSect(const FVertex& vertexIn, const FVertex& vertexOut, FVertex& outVertex) {
	float ix = vertexIn.point[X];
	float iy = vertexIn.point[Y];
	float iz = vertexIn.point[Z];
	float iw = vertexIn.point[W];

	float ox = vertexOut.point[X];
	float oy = vertexOut.point[Y];
	float oz = vertexOut.point[Z];
	float ow = vertexOut.point[W];

	// line segment: vertexIn + t(VertexOut-vertexIn)
	// t \in [0, 1]
	float val = 1.0f;
	float tx;
	if (vertexOut.point[X] > vertexIn.point[X]) {
		// will intersect with plane: x = iw + t(ow - iw)
		// notice: divide zero will not cause exception
		tx = (iw - ix) / ((ox - ow) - (ix - iw));
	}
	else {
		tx = (-iw - ix) / ((ox - ow) - (ix - iw));
	}
	dicideAssignTo(tx, val);
	float ty;
	if (vertexOut.point[Y] > vertexIn.point[Y]) {
		// will intersect with plane: x = iw + t(ow - iw)
		ty = (iw - iy) / ((oy - ow) - (iy - iw));
	}
	else {
		ty = (-iw - iy) / ((oy - ow) - (iy - iw));
	}
	dicideAssignTo(ty, val);
	float tz;
	if (vertexOut.point[Z] > vertexIn.point[Z]) {
		// will intersect with plane: x = iw + t(ow - iw)
		tz = (iw - iz) / ((oz - ow) - (iz - iw));
	}
	else {
		tz = (-iw - iz) / ((oz - ow) - (iz - iw));
	}
	dicideAssignTo(tz, val);

	inter(vertexIn, vertexOut, val, outVertex);
}


#endif