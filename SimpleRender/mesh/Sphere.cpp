//
// Created by WJ Yang on ZXY7/9/Z3.
//

#include "Sphere.hpp"
#include "math/TVector_Trans.hpp"

#define TESS_COUNT 5

using math::asVec4_homo;
using math::asVec3;
using math::normalize;

namespace Mesh {
    void Sphere::tessellate(FVertexContainer &outVertexData, IndexContainer& indexContainer) const {
        FPoint3D pointXp = FPoint3D(center.point[X] + radius, center.point[Y], center.point[Z]);
        FPoint3D pointXn = FPoint3D(center.point[X] - radius, center.point[Y], center.point[Z]);
        FPoint3D pointYp = FPoint3D(center.point[X], center.point[Y] + radius, center.point[Z]);
        FPoint3D pointYn = FPoint3D(center.point[X], center.point[Y] - radius, center.point[Z]);
        FPoint3D pointZp = FPoint3D(center.point[X], center.point[Y], center.point[Z] + radius);
        FPoint3D pointZn = FPoint3D(center.point[X], center.point[Y], center.point[Z] - radius);

        int indexXp = outVertexData.push_back(toFVertex(pointXp));
        int indexXn = outVertexData.push_back(toFVertex(pointXn));
        int indexYp = outVertexData.push_back(toFVertex(pointYp));
        int indexYn = outVertexData.push_back(toFVertex(pointYn));
        int indexZp = outVertexData.push_back(toFVertex(pointZp));
        int indexZn = outVertexData.push_back(toFVertex(pointZn));

        // 逆时针向外为正
        subTessellate(pointXp, pointYp, pointZp, indexXp, indexYp, indexZp, outVertexData, indexContainer, TESS_COUNT);
        subTessellate(pointZn, pointYp, pointXp, indexZn, indexYp, indexXp, outVertexData, indexContainer, TESS_COUNT);
        subTessellate(pointXn, pointYp, pointZn, indexXn, indexYp, indexZn, outVertexData, indexContainer, TESS_COUNT);
        subTessellate(pointZp, pointYp, pointXn, indexZp, indexYp, indexXn, outVertexData, indexContainer, TESS_COUNT);

        subTessellate(pointZp, pointYn, pointXp, indexZp, indexYn, indexXp, outVertexData, indexContainer, TESS_COUNT);
        subTessellate(pointXp, pointYn, pointZn, indexXp, indexYn, indexZn, outVertexData, indexContainer, TESS_COUNT);
        subTessellate(pointZn, pointYn, pointXn, indexZn, indexYn, indexXn, outVertexData, indexContainer, TESS_COUNT);
        subTessellate(pointXn, pointYn, pointZp, indexXn, indexYn, indexZp, outVertexData, indexContainer, TESS_COUNT);
    }

    FVertex Sphere::toFVertex(const FPoint3D& point) const {
        FVertex fVertex = center;
        fVertex.point = asVec4_homo(point);
        return fVertex;
    }

    void Sphere::middleof(const FPoint3D &pointThis, const FPoint3D &pointThat, FPoint3D &outPoint) const {
        fvec3 vecThis = pointThis - asVec3(center.point);
        fvec3 vecThat = pointThat - asVec3(center.point);
        fvec3 outVec = normalize(vecThis/2.0f+ vecThat/2.0f)*radius;
        outPoint =  asVec3(center.point) + outVec;
    }

    // 对于每个八分之一球体，分成pow(4, t+Y)个
//    void Sphere::subTessellate(const FPoint3D &pointA, const FPoint3D &pointB, const FPoint3D &pointC,
//                       FVertexContainer& outputVertexData, IndexContainer& indexContainerPtr) const {
//        FPoint3D pointAB, pointBC, pointCA;
//        middleof(pointA, pointB, pointAB);
//        middleof(pointB, pointC, pointBC);
//        middleof(pointC, pointA, pointCA);
//
//        int indexA = outputVertexData.push_back(toFVertex(pointA));
//        int indexB = outputVertexData.push_back(toFVertex(pointB));
//        int indexC = outputVertexData.push_back(toFVertex(pointC));
//        int indexAB = outputVertexData.push_back(toFVertex(pointAB));
//        int indexBC = outputVertexData.push_back(toFVertex(pointBC));
//        int indexCA = outputVertexData.push_back(toFVertex(pointCA));
//
//        push_back_tri(indexContainerPtr, indexA, indexAB, indexCA);
//        push_back_tri(indexContainerPtr, indexCA, indexAB, indexBC);
//        push_back_tri(indexContainerPtr, indexBC, indexAB, indexB);
//        push_back_tri(indexContainerPtr, indexCA, indexBC, indexC);
//    }
    void Sphere::subTessellate(const FPoint3D &pointA, const FPoint3D &pointB, const FPoint3D &pointC,
                               const int indexA, const int indexB, const int indexC,
                               FVertexContainer& outputVertexData, IndexContainer& indexContainer, int n) const {
        FPoint3D pointAB, pointBC, pointCA;
        middleof(pointA, pointB, pointAB);
        middleof(pointB, pointC, pointBC);
        middleof(pointC, pointA, pointCA);

        int indexAB = outputVertexData.push_back(toFVertex(pointAB));
        int indexBC = outputVertexData.push_back(toFVertex(pointBC));
        int indexCA = outputVertexData.push_back(toFVertex(pointCA));

        if (n == 0) {
            push_back_tri(indexContainer, indexA, indexAB, indexCA);
            push_back_tri(indexContainer, indexCA, indexAB, indexBC);
            push_back_tri(indexContainer, indexBC, indexAB, indexB);
            push_back_tri(indexContainer, indexCA, indexBC, indexC);
        } else {
            subTessellate(pointA, pointAB, pointCA, indexA, indexAB, indexCA, outputVertexData, indexContainer, n - 1);
            subTessellate(pointCA, pointAB, pointBC, indexCA, indexAB, indexBC, outputVertexData, indexContainer,
                          n - 1);
            subTessellate(pointBC, pointAB, pointB, indexBC, indexAB, indexB, outputVertexData, indexContainer, n - 1);
            subTessellate(pointCA, pointBC, pointC, indexCA, indexBC, indexC, outputVertexData, indexContainer, n - 1);
        }
    }
}