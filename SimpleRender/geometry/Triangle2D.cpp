//
// Created by WJ Yang on 2017/9/23.
//

#include <math/TVector_Trans.hpp>
#include "Triangle2D.hpp"

namespace Geometry {
    template <typename T>
    bool Triangle2D<T>::computeBaryCoord(const Point2D<T> &point, Bary &outBary) const {
        outBary[ALPHA] = computeAreaRatio(pB, pC, pA, point);
        if (isInTriangle(outBary[ALPHA])) {
            outBary[BETA] = computeAreaRatio(pA, pC, pB, point);
            if (isInTriangle(outBary[BETA])) {
                outBary[GAMMA] = 1 - outBary[ALPHA] - outBary[BETA];
                if (isInTriangle(outBary[GAMMA]))
                    return true;
            }
        }
        return false;
    }

    template <typename T>
    void Triangle2D<T>::asBoundingBox(Box2D<T> &box) const {
        box[LEFT] = min(pA[X], min(pB[X], pC[X]));
        box[TOP] = min(pA[Y], min(pB[Y], pC[Y]));
        box[RIGHT] = max(pA[X], max(pB[X], pC[X]));
        box[BOTTOM] = max(pA[Y], max(pB[Y], pC[Y]));
    }

    template <typename T>
    void Triangle2D<T>::toPerspectiveCorrect(const float homoA, const float homoB, const float homoC, Bary &outBary) {
        float beta = outBary[BETA];
        float gamma = outBary[GAMMA];

        float denominator = homoB * homoC + homoC * beta * (homoA - homoB) + homoB * gamma * (homoA - homoC);
        outBary[BETA] = homoA * homoC * beta / denominator;
        outBary[GAMMA] = homoA * homoB * gamma / denominator;
        outBary[ALPHA] = 1 - outBary[BETA] - outBary[GAMMA];
    }

    template<typename T>
    float Triangle2D<T>::computeAreaRatio(const Point2D<T> &point1, const Point2D<T> &point2, const Point2D<T> &pointSide, const Point2D<T> &point) {
        vec2<T> vecSide1(point1[X] - pointSide[X], point1[Y] - pointSide[Y]);
        vec2<T> vecSide2(point2[X] - pointSide[X], point2[Y] - pointSide[Y]);
        vec2<T> vec1(point1[X] - point[X], point1[Y] - point[Y]);
        vec2<T> vec2(point2[X] - point[X], point2[Y] - point[Y]);

        return static_cast<float>(math::det<T>(vec1, vec2)) / math::det<T>(vecSide1, vecSide2);
    }

    template<typename T>
    bool Triangle2D<T>::isInTriangle(const float x) {
        return x >= 0.0f && x <= 1.0f;
    }

    template<typename T>
    bool Triangle2D<T>::isOnTriangle(const Bary &bary) {
        return (bary[ALPHA] >= 0 && bary[ALPHA] <= LINE_DET)
               || (bary[BETA] >= 0 && bary[BETA] <= LINE_DET)
               || (bary[GAMMA] >= 0 && bary[GAMMA] <= LINE_DET);
    }

}