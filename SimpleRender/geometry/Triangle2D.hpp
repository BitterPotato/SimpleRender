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
    template <typename T>
    class Triangle2D : Shape2D<T> {
    public:
        Triangle2D(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c) :
                pA(a), pB(b), pC(c) {}

        MY_SMALL_FUNC_DECL void asBoundingBox(Box2D<T> &box) const override;

        /**
         * return point is in triangle or not
         * @param point
         * @param outBary
         * @return
         */
        MY_COMP_FUNC_DECL bool computeBaryCoord(const Point2D<T> &point, Bary &outBary) const;

        MY_SMALL_UTIL_DECL bool isOnTriangle(const Bary &bary);

        MY_SMALL_UTIL_DECL void toPerspectiveCorrect(const float hA, const float hB, const float hC, Bary &outBary);

    private:
        const Point2D<T> &pA, pB, pC;

        MY_SMALL_UTIL_DECL float
        computeAreaRatio(const Point2D<T> &point1, const Point2D<T> &point2, const Point2D<T> &pointSide, const Point2D<T> &point);

        MY_SMALL_UTIL_DECL bool isInTriangle(const float x);
    };

    using ITriangle2D = Triangle2D<int>;
}


#endif //SIMPLERENDER_TRIANGLE_HPP
