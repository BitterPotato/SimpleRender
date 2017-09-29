#ifndef BSP_INL
#define BSP_INL

#include "BSPTree.hpp"

using Geometry::FTriangle3D;

float BSPTree::distToTri(const Triangle *tri, const FPoint3D &point) const {
    FTriangle3D triangle3D(asVec3(vertexList[tri->indexA].point),
                           asVec3(vertexList[tri->indexB].point),
                           asVec3(vertexList[tri->indexC].point));
    return triangle3D.distToTri(point);
}

float BSPTree::distToTriWrapper(const Triangle *tri, const FPoint3D &point) const {
    float dis = distToTri(tri, point);
    return abs(dis) < epsilon ? 0.0f : dis;
}

float BSPTree::intersectToTri(const Triangle* tri, const FPoint3D& pThis, const FPoint3D& pThat) const {
    FTriangle3D triangle3D(asVec3(vertexList[tri->indexA].point),
                           asVec3(vertexList[tri->indexB].point),
                           asVec3(vertexList[tri->indexC].point));

    return triangle3D.intersectToTri(pThis, pThat);
}

void BSPTree::intersectToTriWrapper(const Triangle* tri, const FVertex& vThis, const FVertex& vThat, FVertex& outVertex) const {
    float ratio = intersectToTri(tri, asVec3(vThis.point), asVec3(vThat.point));
    inter(vThis, vThat, outVertex, ratio);
}

#endif
