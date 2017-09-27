//
// Created by WJ Yang on 2017/9/24.
//

#include "Raster.hpp"

#include "Point.hpp"
#include "Line.hpp"
#include "Triangle.hpp"

namespace Gl {
    void Raster::rasterUniverTriangle(const GL_PATTERN& pattern, const Vertex& vertexA, const Vertex& vertexB, const Vertex& vertexC, const unique_ptr<Texture>& texture, FragCache& fragCache) {
        if (pattern == GL_NORMAL)
            Triangle::rasterTriangle(vertexA, vertexB, vertexC, texture, fragCache);
        else if (pattern == GL_WIREFRAME)
            Triangle::rasterTriangleWire(vertexA, vertexB, vertexC, fragCache);
    }

    void Raster::raster(const GL_MODE& mode, const GL_PATTERN& pattern, const vector<Vertex>& vecVertex, const unique_ptr<Texture>& texture, FragCache& fragCache) {
        switch (mode) {
            case GL_POINTS:
                for (auto iter = vecVertex.begin(); iter != vecVertex.end(); iter++) {
                    Point::rasterPoint(*iter, POINT_SIZE, fragCache);
                }
                break;
            case GL_LINES:
                for (auto iter = vecVertex.begin(); iter != vecVertex.end(); iter += 2) {
                    Line::rasterLine(*iter, *(iter + 1), LINE_WIDTH, fragCache);
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

