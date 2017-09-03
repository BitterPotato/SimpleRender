#ifndef RASTER_STAGE_HPP
#define RASTER_STAGE_HPP

#include "stage_struc.hpp"
#include "../raster/Point.hpp"
#include "../raster/Line.hpp"
#include "../raster/Triangle.hpp"

#include <vector>
#include <exception>
#include <stdexcept>

using std::vector;
using std::logic_error;

#define TRIANGLE_POINTS 3
#define LINE_POINTS 2

#define WIDTH 1
#define SIZE 10

namespace gl {

static inline void rasterUniverTriangle(const GL_PATTERN& pattern, const Vertex& vertexA, const Vertex& vertexB, const Vertex& vertexC, FragCache& fragCache) {
	if (pattern == GL_NORMAL)
		rasterTriangle(vertexA, vertexB, vertexC, fragCache);
	else if (pattern == GL_WIREFRAME)
		rasterTriangleWire(vertexA, vertexB, vertexC, fragCache);
}

static inline void raster(const GL_MODE& mode, const GL_PATTERN& pattern, const vector<Vertex>& vecVertex, FragCache& fragCache) {
	switch (mode) {
	case GL_POINTS:
		for (auto iter = vecVertex.begin(); iter != vecVertex.end(); iter++) {
			rasterPoint(*iter, SIZE, fragCache);
		}
		break;
	case GL_LINES:
		if (vecVertex.size() % LINE_POINTS != 0)
			throw logic_error("not enough points for triangles");
		for (auto iter = vecVertex.begin(); iter != vecVertex.end(); iter += 2) {
			rasterLine(*iter, *(iter + 1), WIDTH, fragCache);
		}
		break;
	case GL_TRIANGLES:
		if (vecVertex.size() % TRIANGLE_POINTS != 0)
			throw logic_error("not enough points for triangles");
		for (auto iter = vecVertex.begin(); iter != vecVertex.end(); iter += 3) {
			rasterUniverTriangle(pattern, *iter, *(iter + 1), *(iter + 2), fragCache);
		}
		break;
	case GL_TRIANGLES_STRIP:
		auto iter = vecVertex.begin();
		iter += 2;
		for ( ; iter != vecVertex.end(); iter++) {
			rasterUniverTriangle(pattern, *(iter - 2), *(iter - 1), *iter, fragCache);
		}
		break;
	}

}
}

#endif