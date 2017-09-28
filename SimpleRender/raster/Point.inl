#ifndef SIMPLERENDER_RASTER_POINT_INL
#define SIMPLERENDER_RASTER_POINT_INL

#include "Point.hpp"
#include "common/Frag.hpp"
#include "common/Vertex.hpp"
#include "common/Point.hpp"
#include "FragCache.hpp"

namespace Gl {
    void Point::rasterPoint(const Vertex &vertex, const int size, FragCache &outFragCache) {
        for (int i = -size; i <= size; i++) {
            for (int j = -size; j < size; j++) {
                outFragCache.addFrag(Frag(IPoint2D(vertex.point[X] + i, vertex.point[Y] + j), vertex.info));
            }
        }
    }
}

#endif