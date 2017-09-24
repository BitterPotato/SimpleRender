//
// Created by WJ Yang on 2017/9/24.
//

#ifndef SIMPLERENDER_RASTER_HPP
#define SIMPLERENDER_RASTER_HPP

#include "pipeline/RenderSetup.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Triangle.hpp"
#include "common/Frag.hpp"
#include "material/Texture.hpp"
#include "FragCache.hpp"

#define LINE_WIDTH 1
#define POINT_SIZE 10

namespace Gl {
    class Raster {
    public:
        MY_UTIL_DECL void rasterUniverTriangle(const GL_PATTERN &pattern, const Vertex &vertexA, const Vertex &vertexB,
                                               const Vertex &vertexC, const unique_ptr<Texture> &texture,
                                               FragCache &fragCache);

        MY_UTIL_DECL void raster(const GL_MODE &mode, const GL_PATTERN &pattern, const vector<Vertex> &vecVertex,
                                 const unique_ptr<Texture> &texture, FragCache &fragCache);
    };
}

#endif //SIMPLERENDER_RASTER_HPP
