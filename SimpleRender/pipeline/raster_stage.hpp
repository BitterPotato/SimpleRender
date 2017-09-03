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

namespace gl {
static inline void raster(const GL_MODE& mode, const vector<Vertex>& vecVertex, FragCache& fragCache) {
	switch (mode) {
	case GL_TRIANGLES:
		if (vecVertex.size() % TRIANGLE_POINTS != 0)
			throw logic_error("not enough points for triangles");
		for (auto iter = vecVertex.begin(); iter != vecVertex.end(); iter += 3) {
			rasterTriangle(*iter, *(iter + 1), *(iter + 2), fragCache);
		}
		break;
	}
}
}

#endif