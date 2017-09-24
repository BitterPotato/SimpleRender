//
// Created by WJ Yang on 2017/9/23.
//

#ifndef SIMPLERENDER_TRIANGLE_HPP
#define SIMPLERENDER_TRIANGLE_HPP

#define LINE_DET 0.01f

#include <common/Point.hpp>
#include "Shape2D.hpp"

using Bary = fvec3;
const int ALPHA = 0;
const int BETA = 1;
const int GAMMA = 2;

namespace Geometry {
    class Triangle2D : Shape2D {
    public:
        Triangle2D(const Point2D &a, const Point2D &b, const Point2D &c) :
                pA(a), pB(b), pC(c) {}

        MY_SMALL_FUNC_DECL void asBoundingBox(Box2D &box) const override;

        /**
         * return point is in triangle or not
         * @param point
         * @param outBary
         * @return
         */
        MY_COMP_FUNC_DECL bool computeBaryCoord(const Point2D &point, Bary &outBary) const;

        MY_SMALL_UTIL_DECL bool isOnTriangle(const Bary &bary);

        MY_SMALL_UTIL_DECL void toPerspectiveCorrect(const float hA, const float hB, const float hC, Bary &outBary);

    private:
        const Point2D &pA, pB, pC;

        MY_SMALL_UTIL_DECL float
        computeAreaRatio(const Point2D &point1, const Point2D &point2, const Point2D &pointSide, const Point2D &point);

        MY_SMALL_UTIL_DECL bool isInTriangle(const float x);
    };
}


#endif //SIMPLERENDER_TRIANGLE_HPP
