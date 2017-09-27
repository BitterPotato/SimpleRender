//
// Created by WJ Yang on 2017/9/23.
//

#ifndef SIMPLERENDER_TRIANGLE_HPP
#define SIMPLERENDER_TRIANGLE_HPP

#define LINE_DET 0.01f

#include "math/TVector.hpp"
#include "Shape2D.hpp"

using Bary = fvec3;
const int ALPHA = 0;
const int BETA = 1;
const int GAMMA = 2;

namespace Geometry {
    template <typename T>
    class Triangle2D : Shape2D<T> {
    public:
        Triangle2D(const TVectorN<T, 2> &a, const TVectorN<T, 2> &b, const TVectorN<T, 2> &c) :
                pA(a), pB(b), pC(c) {}

        MY_SMALL_FUNC_DECL void asBoundingBox(Box2D<T> &box) const override;

        /**
         * return point is in triangle or not
         * @param point
         * @param outBary
         * @return
         */
        MY_COMP_FUNC_DECL bool computeBaryCoord(const TVectorN<T, 2> &point, Bary &outBary) const;

        MY_SMALL_UTIL_DECL bool isOnTriangle(const Bary &bary);

        MY_SMALL_UTIL_DECL void toPerspectiveCorrect(const float hA, const float hB, const float hC, Bary &outBary);

    private:
        const TVectorN<T, 2> &pA, pB, pC;

        MY_SMALL_UTIL_DECL float
        computeAreaRatio(const TVectorN<T, 2> &point1, const TVectorN<T, 2> &point2, const TVectorN<T, 2> &pointSide, const TVectorN<T, 2> &point);

        MY_SMALL_UTIL_DECL bool isInTriangle(const float x);
    };

    using ITriangle2D = Triangle2D<int>;
}

#include "Triangle2D.inl"

#endif //SIMPLERENDER_TRIANGLE_HPP
