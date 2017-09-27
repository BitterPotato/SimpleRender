#include "Triangle.hpp"

#include "common/Vertex.hpp"
#include "FragCache.hpp"
#include "geometry/Triangle2D.hpp"
#include "material/Texture.hpp"
#include "common/Frag.hpp"

using Geometry::ITriangle2D;

namespace Gl {
    void Triangle::rasterTriangle(const Vertex &vertexA, const Vertex &vertexB, const Vertex &vertexC,
                                  const unique_ptr<Texture> &texture, FragCache &fragCache) {

        // find bounding box
        IBox2D box;
        ITriangle2D triangle(vertexA.point, vertexB.point, vertexC.point);
        triangle.asBoundingBox(box);

        // tranverse, compute barycentric coordinate
        for (int x = box[LEFT]; x < box[RIGHT]; x++) {
            for (int y = box[TOP]; y < box[BOTTOM]; y++) {
                IPoint2D point{x, y};
                Bary bary;
                if (triangle.computeBaryCoord(point, bary)) {
                    Info info;
                    if (texture != nullptr) {
                        triangle.toPerspectiveCorrect(vertexA.homo, vertexB.homo, vertexC.homo, bary);

                        fvec2 interUV;
                        Vertex::inter(vertexA.tex, vertexB.tex, vertexC.tex, interUV, bary);

                        texture->getUVPixelColor(interUV[U], interUV[V], info.rgba);
                    } else {
                        inter(vertexA.info.rgba, vertexB.info.rgba, vertexC.info.rgba, info.rgba, bary);
                    }
                    interDepth(vertexA.info, vertexB.info, vertexC.info, info, bary);

                    fragCache.addFrag(Frag(point, info));
                }
            }
        }
    }

    void
    Triangle::rasterTriangleWire(const Vertex &vertexA, const Vertex &vertexB, const Vertex &vertexC,
                                 FragCache &fragCache) {

        // find bounding box
        IBox2D box;
        ITriangle2D triangle(vertexA.point, vertexB.point, vertexC.point);
        triangle.asBoundingBox(box);

        // tranverse, compute barycentric coordinate
        for (int x = box[LEFT]; x < box[RIGHT]; x++) {
            for (int y = box[TOP]; y < box[BOTTOM]; y++) {
                IPoint2D point(x, y);
                Bary bary;
                // attention: only there diffs
                if (triangle.computeBaryCoord(point, bary) && triangle.isOnTriangle(bary)) {
                    Info info;
                    inter(vertexA.info.rgba, vertexB.info.rgba, vertexC.info.rgba, info.rgba, bary);
                    interDepth(vertexA.info, vertexB.info, vertexC.info, info, bary);

                    fragCache.addFrag(Frag(point, info));
                }
            }
        }
    }
}