#ifndef RASTER_STAGE_HPP
#define RASTER_STAGE_HPP

#include "stage_struc.hpp"
#include "../raster/Point.hpp"
#include "../raster/Line.hpp"
#include "../raster/Triangle.hpp"

#include <vector>

using std::vector;

#define WIDTH 1
#define SIZE 10

namespace gl {

static inline void rasterUniverTriangle(const GL_PATTERN& pattern, const Vertex& vertexA, const Vertex& vertexB, const Vertex& vertexC, const Texture* texture, FragCache& fragCache) {
	if (pattern == GL_NORMAL)
		rasterTriangle(vertexA, vertexB, vertexC, texture, fragCache);
	else if (pattern == GL_WIREFRAME)
		rasterTriangleWire(vertexA, vertexB, vertexC, fragCache);
}

static inline void raster(const GL_MODE& mode, const GL_PATTERN& pattern, const vector<Vertex>& vecVertex, Texture* texture, FragCache& fragCache) {
	switch (mode) {
	case GL_POINTS:
		for (auto iter = vecVertex.begin(); iter != vecVertex.end(); iter++) {
			rasterPoint(*iter, SIZE, fragCache);
		}
		break;
	case GL_LINES:
		for (auto iter = vecVertex.begin(); iter != vecVertex.end(); iter += 2) {
			rasterLine(*iter, *(iter + 1), WIDTH, fragCache);
		}
		break;
	case GL_TRIANGLES:
		for (auto iter = vecVertex.begin(); iter != vecVertex.end(); iter += 3) {
			rasterUniverTriangle(pattern, *iter, *(iter + 1), *(iter + 2), texture, fragCache);
		}
		break;
	case GL_TRIANGLES_STRIP:
		auto iter = vecVertex.begin();
		iter += 2;
		for ( ; iter != vecVertex.end(); iter++) {
			rasterUniverTriangle(pattern, *(iter - 2), *(iter - 1), *iter, texture, fragCache);
		}
		break;
	}

}
}

#endif