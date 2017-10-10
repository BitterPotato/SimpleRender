//
// Created by WJ Yang on 2017/9/24.
//

#include "Raster.hpp"

#include "Point.hpp"
#include "Line.hpp"
#include "Triangle.hpp"

using std::next;

namespace Gl {
    void Raster::rasterUniverTriangle(const GL_PATTERN& pattern, const Vertex& vertexA, const Vertex& vertexB, const Vertex& vertexC, const unique_ptr<Texture>& texture, FragCache& fragCache) {
        if (pattern == GL_NORMAL)
            Triangle::rasterTriangle(vertexA, vertexB, vertexC, texture, fragCache);
        else if (pattern == GL_WIREFRAME)
            Triangle::rasterTriangleWire(vertexA, vertexB, vertexC, fragCache);
    }

    void Raster::raster(const GL_MODE& mode, const GL_PATTERN& pattern, const VertexContainer& vecVertex, const IndexContainer& indexContainer, 
                        const unique_ptr<Texture>& texture, FragCache& fragCache) {
        switch (mode) {
            case GL_POINTS:
                for (auto iter = indexContainer.begin(); iter != indexContainer.end(); iter = next(iter)) {
                    Point::rasterPoint(vecVertex[*iter], POINT_SIZE, fragCache);
                }
                break;
            case GL_LINES:
                for (auto iter = indexContainer.begin(); iter != indexContainer.end(); iter = next(iter, LINE_COUNT)) {
                    Line::rasterLine(vecVertex[*iter], vecVertex[*next(iter)], LINE_WIDTH, fragCache);
                }
                break;
            case GL_TRIANGLES:
            case GL_TRIANGLES_STRIP:
                for (auto iter = indexContainer.begin(); iter != indexContainer.end(); iter = next(iter, TRI_COUNT)) {
                    rasterUniverTriangle(pattern, vecVertex[*iter], vecVertex[*next(iter)], vecVertex[*next(iter, 2)], texture, fragCache);
                }
                break;
        }

    }
}

