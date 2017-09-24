//
// Created by WJ Yang on 2017/9/24.
//

#ifndef SIMPLERENDER_LINE_HPP
#define SIMPLERENDER_LINE_HPP

#include <common/Vertex.hpp>
#include "FragCache.hpp"
#include "math/Basic.hpp"

#define LINE_Bresenham
//#define LINE_WuXiaolin

namespace Gl {
    class Line {
    public:
        MY_SMALL_UTIL_DECL void
        rasterLine(const Vertex &lineBegin, const Vertex &lineEnd, const int width, FragCache &outFragCache);

    private:
        MY_UTIL_DECL void
        rasterLineB(const Vertex &lineBegin, const Vertex &lineEnd, const int width, FragCache &fragCache);

        MY_UTIL_DECL void
        rasterLineBB(const Vertex &lineBegin, const Vertex &lineEnd, const int width, FragCache &fragCache);

        MY_UTIL_DECL void
        rasterLineW(const Vertex &lineBegin, const Vertex &lineEnd, const int width, FragCache &fragCache);

        MY_UTIL_DECL void rasterErrorYBased(const Vertex &lineBP, const Vertex &lineEP, float errorUnit, FragCache &outFragCache);

        MY_UTIL_DECL void rasterErrorXBased(const Vertex &lineBP, const Vertex &lineEP, float errorUnit, FragCache &outFragCache);
    };
}


#endif //SIMPLERENDER_LINE_HPP
