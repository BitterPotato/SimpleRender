//
// Created by WJ Yang on 2017/9/24.
//

#include "Line.hpp"

#ifndef LINE_HPP
#define LINE_HPP

namespace Gl {
    void Line::rasterLine(const Vertex &lineBegin, const Vertex &lineEnd, const int width, FragCache &outFragCache) {
#if defined(LINE_Bresenham)
        rasterLineBB(lineBegin, lineEnd, width, outFragCache);
#elif defined(LINE_WuXiaolin)
        rasterLineW(lineBegin, lineEnd, width, outFragCache);
#endif
    }

    void
    Line::rasterErrorXBased(const Vertex &lineBP, const Vertex &lineEP, float errorUnit, FragCache &outFragCache) {
        int ySege = lineBP.point[Y] > lineEP.point[Y] ? -1 : 1;
        int curY = lineBP.point[Y];
        float error = 0;
        for (int curX = lineBP.point[X]; curX <= lineEP.point[X]; curX++) {
            error += errorUnit;
            if (std::abs(error) > 0.5f) {
                curY += ySege;
                error -= ySege;
            }
            // TODO color interpolate
            outFragCache.addFrag(Frag(Point2D(curX, curY), lineBP.info));
        }
    }

    void
    Line::rasterErrorYBased(const Vertex &lineBP, const Vertex &lineEP, float errorUnit, FragCache &outFragCache) {
        int xSege = lineBP.point[X] > lineEP.point[X] ? -1 : 1;
        int curX = lineBP.point[X];
        float error = 0;
        for (int curY = lineBP.point[Y]; curY <= lineEP.point[Y]; curY++) {
            error += errorUnit;
            if (std::abs(error) > 0.5f) {
                curX += xSege;
                error -= xSege;
            }
            // TODO color interpolate
            outFragCache.addFrag(Frag(Point2D(curX, curY), lineBP.info));
        }
    }

// do not support color interpolate temply
    void Line::rasterLineB(const Vertex &lineBegin, const Vertex &lineEnd, const int width, FragCache &fragCache) {
        // 1. vertical line
        if (lineBegin.point[X] == lineEnd.point[X]) {
            // divide zero
            int lineX = lineBegin.point[X];
            int lineSmallY, lineBigY;
            if (lineBegin.point[Y] > lineEnd.point[Y]) {
                lineSmallY = lineEnd.point[Y];
                lineBigY = lineBegin.point[Y];
            } else {
                lineSmallY = lineBegin.point[Y];
                lineBigY = lineEnd.point[Y];
            }
            for (int curY = lineSmallY; curY <= lineBigY; curY++) {
                fragCache.addFrag(Frag(Point2D(lineX, curY), lineBegin.info));
            }
            return;
        }

        float slope = (float) (lineEnd.point[Y] - lineBegin.point[Y]) / (float) (lineEnd.point[X] - lineBegin.point[X]);
        if (std::abs(slope) > 1) {
            float slope_inve =
                    (float) (lineEnd.point[X] - lineBegin.point[X]) / (float) (lineEnd.point[Y] - lineBegin.point[Y]);
            if (lineBegin.point[Y] > lineEnd.point[Y])
                rasterErrorYBased(lineEnd, lineBegin, slope_inve, fragCache);
            else
                rasterErrorYBased(lineBegin, lineEnd, slope_inve, fragCache);
        }
            // horizontal line will be included
        else {
            // Learn1. use sub functions to achieve the swap effect in similar
            if (lineBegin.point[X] > lineEnd.point[X])
                rasterErrorXBased(lineEnd, lineBegin, slope, fragCache);
            else
                rasterErrorXBased(lineBegin, lineEnd, slope, fragCache);
        }
    }

    void Line::rasterLineBB(const Vertex &lineBegin, const Vertex &lineEnd, const int width, FragCache &fragCache) {
        int x0 = lineBegin.point[X];
        int y0 = lineBegin.point[Y];
        int x1 = lineEnd.point[X];
        int y1 = lineEnd.point[Y];

        int b0 = lineBegin.info.rgba[B];
        int g0 = lineBegin.info.rgba[G];
        int r0 = lineBegin.info.rgba[R];
        int a0 = lineBegin.info.rgba[A];
        int b1 = lineEnd.info.rgba[B];
        int g1 = lineEnd.info.rgba[G];
        int r1 = lineEnd.info.rgba[R];
        int a1 = lineEnd.info.rgba[A];

        bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
        if (steep) {
            myswap(&x0, &y0);
            myswap(&x1, &y1);
        }
        if (x0 > x1) {
            myswap(&x0, &x1);
            myswap(&y0, &y1);

            myswap(&b0, &b1);
            myswap(&g0, &g1);
            myswap(&r0, &r1);
            myswap(&a0, &a1);
        }
        float error = 0;
        float deltaError = static_cast<float>(y1 - y0) / (x1 - x0);
        float bDeltaError = static_cast<float>(b1 - b0) / (x1 - x0);
        float gDeltaError = static_cast<float>(g1 - g0) / (x1 - x0);
        float rDeltaError = static_cast<float>(r1 - r0) / (x1 - x0);
        float aDeltaError = static_cast<float>(a1 - a0) / (x1 - x0);

        int ySege = y0 > y1 ? -1 : 1;
        int curY = y0;
        float curB = b0;
        float curG = g0;
        float curR = r0;
        float curA = a0;

        for (int curX = x0; curX <= x1; curX++) {
            error += deltaError;
            if (std::abs(error) >= 0.5f) {
                curY += ySege;
                error -= ySege;
            }
            curB += bDeltaError;
            curG += gDeltaError;
            curR += rDeltaError;
            curA += aDeltaError;

            RGBA interBGRA = RGBA(ipart(curB), ipart(curG), ipart(curR), ipart(curA));
            Info interInfo = Info(interBGRA);
            if (steep)
                fragCache.addFrag(Frag(Point2D(curY, curX), interInfo));
            else
                fragCache.addFrag(Frag(Point2D(curX, curY), interInfo));
        }
    }


    void Line::rasterLineW(const Vertex &lineBegin, const Vertex &lineEnd, const int width, FragCache &fragCache) {
        float x0 = lineBegin.point[X];
        float y0 = lineBegin.point[Y];
        float x1 = lineEnd.point[X];
        float y1 = lineEnd.point[Y];
        bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
        if (steep) {
            myswap(&x0, &y0);
            myswap(&x1, &y1);
        }
        if (x0 > x1) {
            myswap(&x0, &x1);
            myswap(&y0, &y1);
        }
        float deltaX = x1 - x0;
        float deltaY = y1 - y0;
        float gradient = (float) deltaY / (float) deltaX;

        //1. 对于整数坐标点，与Bresenham一致
        int xend = mround(x0);
        float yend = y0 + gradient * (xend - x0);
        float xgap = rfpart(x0 + 0.5f);
        int xpxl1 = xend;
        int ypxl1 = ipart(yend);
        // TODO: begin and end
        if (steep)
            myswap(&xpxl1, &ypxl1);

        fragCache.addFrag(Frag(Point2D(xpxl1, ypxl1), lineBegin.info * (rfpart(yend) * xgap)));
        fragCache.addFrag(Frag(Point2D(xpxl1, ypxl1 + 1), lineBegin.info * (fpart(yend) * xgap)));
        if (steep)
            myswap(&xpxl1, &ypxl1);

        float intery = yend + gradient;

        xend = mround(x1);
        yend = y1 + gradient * (xend - x1);
        xgap = rfpart(x1 + 0.5f);
        int xpxl2 = xend;
        int ypxl2 = ipart(yend);
        // TODO: begin and end
        if (steep)
            myswap(&xpxl1, &ypxl1);
        fragCache.addFrag(Frag(Point2D(xpxl2, ypxl2), lineBegin.info * (rfpart(yend) * xgap)));
        fragCache.addFrag(Frag(Point2D(xpxl2, ypxl2 + 1), lineBegin.info * (fpart(yend) * xgap)));
        if (steep)
            myswap(&xpxl1, &ypxl1);


        // main loop
        for (int x = xpxl1 + 1; x < xpxl2; x++) {
            // 点的颜色值按照比例分配给它的上下两个点
            if (steep) {
                fragCache.addFrag(Frag(Point2D(ipart(intery), x), lineBegin.info * (rfpart(intery))));
                fragCache.addFrag(Frag(Point2D(ipart(intery) + 1, x), lineBegin.info * (fpart(intery))));
            } else {
                fragCache.addFrag(Frag(Point2D(x, ipart(intery)), lineBegin.info * (rfpart(intery))));
                fragCache.addFrag(Frag(Point2D(x, ipart(intery) + 1), lineBegin.info * (fpart(intery))));
            }

            intery += gradient;
        }
    }
}
#endif
