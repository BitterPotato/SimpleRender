#ifndef SIMPLERENDER_LINE_INL
#define SIMPLERENDER_LINE_INL

#include "Line.hpp"

namespace Gl {
    void Line::rasterLine(const Vertex &lineBegin, const Vertex &lineEnd, const int width, FragCache &outFragCache) {
#if defined(LINE_Bresenham)
        rasterLineBB(lineBegin, lineEnd, width, outFragCache);
#elif defined(LINE_WuXiaolin)
        rasterLineW(lineBegin, lineEnd, width, outFragCache);
#endif
    }
}
#endif