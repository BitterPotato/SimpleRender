//
// Created by WJ Yang on 2017/9/23.
//

#include <math/TVector_Trans.hpp>
#include "Triangle2D.hpp"

namespace Geometry {
    bool Triangle2D::computeBaryCoord(const Point2D &point, Bary &outBary) const {
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

    void Triangle2D::asBoundingBox(Box2D &box) const {
        box[LEFT] = min(pA[X], min(pB[X], pC[X]));
        box[TOP] = min(pA[Y], min(pB[Y], pC[Y]));
        box[RIGHT] = max(pA[X], max(pB[X], pC[X]));
        box[BOTTOM] = max(pA[Y], max(pB[Y], pC[Y]));
    }

    void toPerspectiveCorrect(const float homoA, const float homoB, const float homoC, Bary &outBary) {
        float beta = outBary[BETA];
        float gamma = outBary[GAMMA];

        float denominator = homoB * homoC + homoC * beta * (homoA - homoB) + homoB * gamma * (homoA - homoC);
        outBary[BETA] = homoA * homoC * beta / denominator;
        outBary[GAMMA] = homoA * homoB * gamma / denominator;
        outBary[ALPHA] = 1 - outBary[BETA] - outBary[GAMMA];
    }

    float computeAreaRatio(const Point2D &point1, const Point2D &point2, const Point2D &pointSide, const Point2D &point) {
        ivec2 vecSide1 = ivec2(point1[X] - pointSide[X], point1[Y] - pointSide[Y]);
        ivec2 vecSide2 = ivec2(point2[X] - pointSide[X], point2[Y] - pointSide[Y]);
        ivec2 vec1 = ivec2(point1[X] - point[X], point1[Y] - point[Y]);
        ivec2 vec2 = ivec2(point2[X] - point[X], point2[Y] - point[Y]);

        return static_cast<float>(math::det<int>(vec1, vec2)) / math::det<int>(vecSide1, vecSide2);
    }

    bool isInTriangle(const float x) {
        return x >= 0.0f && x <= 1.of;
    }

    bool isOnTriangle(const Bary &bary) {
        return (bary[ALPHA] >= 0 && bary[ALPHA] <= LINE_DET)
               || (bary[BETA] >= 0 && bary[BETA] <= LINE_DET)
               || (bary[GAMMA] >= 0 && bary[GAMMA] <= LINE_DET);
    }
}