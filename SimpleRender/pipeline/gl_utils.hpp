#ifndef GL_UTILS_HPP
#define GL_UTILS_HPP

#include "../raster/Frag.hpp"

inline bool isInVisualBody(const FVertex& fVertex) {
	float x = fVertex.x;
	float y = fVertex.y;
	float z = fVertex.z;
	float w = fVertex.w;

	return x >= -w && x <= w
		&& y >= -w && y <= w
		&& z >= -w && z <= w;
}

inline void dicideAssignTo(const float& t, float& val) {
	if (t >= 0.0f && t <= 1.0f && t < val)
		val = t;
}

static void computeInterSect(const FVertex& vertexIn, const FVertex& vertexOut, FVertex& outVertex) {
	float ix = vertexIn.x;
	float iy = vertexIn.y;
	float iz = vertexIn.z;
	float iw = vertexIn.w;

	float ox = vertexOut.x;
	float oy = vertexOut.y;
	float oz = vertexOut.z;
	float ow = vertexOut.w;

	// line segment: vertexIn + t(VertexOut-vertexIn)
	// t \in [0, 1]
	float val = 1.0f;
	float tx;
	if (vertexOut.x > vertexIn.x) {
		// will intersect with plane: x = iw + t(ow - iw)
		// notice: divide zero will not cause exception
		tx = (iw - ix) / ((ox - ow) - (ix - iw));
	}
	else {
		tx = (-iw - ix) / ((ox - ow) - (ix - iw));
	}
	dicideAssignTo(tx, val);
	float ty;
	if (vertexOut.y > vertexIn.y) {
		// will intersect with plane: x = iw + t(ow - iw)
		ty = (iw - iy) / ((oy - ow) - (iy - iw));
	}
	else {
		ty = (-iw - iy) / ((oy - ow) - (iy - iw));
	}
	dicideAssignTo(ty, val);
	float tz;
	if (vertexOut.z > vertexIn.z) {
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