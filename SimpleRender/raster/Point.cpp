//
// Created by WJ Yang on 2017/9/24.
//

#include "Point.hpp"

namespace Gl {
    void Point::rasterPoint(const Vertex &vertex, const int size, FragCache &outFragCache) {
        for (int i = -size; i <= size; i++) {
            for (int j = -size; j < size; j++) {
                outFragCache.addFrag(Frag(Point2D(vertex.point[X] + i, vertex.point[Y] + j), vertex.info));
            }
        }
    }
}