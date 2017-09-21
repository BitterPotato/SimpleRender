#ifndef LINE_HPP
#define LINE_HPP

#include "FragCache.hpp"
#include "../math/basic.hpp"
#include "../util/func.hpp"

#include <cmath>
#include <iostream>

#define LINE_Bresenham
//#define LINE_WuXiaolin

inline void rasterLineB(const Vertex& lineBegin, const Vertex& lineEnd, const int width, FragCache& fragCache);
inline void rasterLineBB(const Vertex& lineBegin, const Vertex& lineEnd, const int width, FragCache& fragCache);
inline void rasterLineW(const Vertex& lineBegin, const Vertex& lineEnd, const int width, FragCache& fragCache);

inline void rasterLine(const Vertex& lineBegin, const Vertex& lineEnd, const int width, FragCache& outFragCache) {
#if defined(LINE_Bresenham)
	rasterLineBB(lineBegin, lineEnd, width, outFragCache);
#elif defined(LINE_WuXiaolin)
	rasterLineW(lineBegin, lineEnd, width, outFragCache);
#endif
}

inline void rasterErrorXBased(const Vertex& lineBP, const Vertex& lineEP, float errorUnit, FragCache &outFragCache)
{
	int ySege = lineBP.y > lineEP.y ? -1 : 1;
	int curY = lineBP.y;
	float error = 0;
	for (int curX = lineBP.x; curX <= lineEP.x; curX++) {
		error += errorUnit;
		if (std::abs(error) > 0.5f) {
			curY += ySege;
			error -= ySege;
		}
		// TODO color interpolate
		outFragCache.addFrag({ lineBP.info, curX, curY});
	}
}

inline void rasterErrorYBased(const Vertex& lineBP, const Vertex& lineEP, float errorUnit, FragCache &outFragCache)
{
	int xSege = lineBP.x > lineEP.x ? -1 : 1;
	int curX = lineBP.x;
	float error = 0;
	for (int curY = lineBP.y; curY <= lineEP.y; curY++) {
		error += errorUnit;
		if (std::abs(error) > 0.5f) {
			curX += xSege;
			error -= xSege;
		}
		// TODO color interpolate
		outFragCache.addFrag({ lineBP.info, curX, curY });
	}
}

// do not support color interpolate temply
inline void rasterLineB(const Vertex& lineBegin, const Vertex& lineEnd, const int width, FragCache& fragCache) {
	// 1. vertical line
	if (lineBegin.x == lineEnd.x) {
		// divide zero
		int lineX = lineBegin.x;
		int lineSmallY, lineBigY;
		if (lineBegin.y > lineEnd.y) {
			lineSmallY = lineEnd.y;
			lineBigY = lineBegin.y;
		}
		else {
			lineSmallY = lineBegin.y;
			lineBigY = lineEnd.y;
		}
		for (int curY = lineSmallY; curY <= lineBigY; curY++) {
			fragCache.addFrag({ lineBegin.info, lineX, curY });
		}
		return;
	}

	float slope = (float)(lineEnd.y - lineBegin.y) / (float)(lineEnd.x - lineBegin.x);
	if (std::abs(slope) > 1) {
		float slope_inve = (float)(lineEnd.x - lineBegin.x) / (float)(lineEnd.y - lineBegin.y);
		if (lineBegin.y > lineEnd.y)
			rasterErrorYBased(lineEnd, lineBegin, slope_inve, fragCache);
		else
			rasterErrorYBased(lineBegin, lineEnd, slope_inve, fragCache);
	}
	// horizontal line will be included
	else {
		// Learn1. use sub functions to achieve the swap effect in similar
		if(lineBegin.x > lineEnd.x)
			rasterErrorXBased(lineEnd, lineBegin, slope, fragCache);
		else
			rasterErrorXBased(lineBegin, lineEnd, slope, fragCache);
	}
}

inline void rasterLineBB(const Vertex& lineBegin, const Vertex& lineEnd, const int width, FragCache& fragCache) {
	int x0 = lineBegin.x;
	int y0 = lineBegin.y;
	int x1 = lineEnd.x;
	int y1 = lineEnd.y;

	int b0 = lineBegin.info->bgra->b;
	int g0 = lineBegin.info->bgra->g;
	int r0 = lineBegin.info->bgra->r;
	int a0 = lineBegin.info->bgra->a;
	int b1 = lineEnd.info->bgra->b;
	int g1 = lineEnd.info->bgra->g;
	int r1 = lineEnd.info->bgra->r;
	int a1 = lineEnd.info->bgra->a;

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
		
		BGRA* interBGRA = new BGRA{ ipart(curB), ipart(curG), ipart(curR), ipart(curA) };
		Info* interInfo = new Info{ interBGRA };
		if (steep)
			fragCache.addFrag({ interInfo, curY, curX });
		else
			fragCache.addFrag({ interInfo, curX, curY });
	}
}


inline void rasterLineW(const Vertex& lineBegin, const Vertex& lineEnd, const int width, FragCache& fragCache) {
	float x0 = lineBegin.x;
	float y0 = lineBegin.y;
	float x1 = lineEnd.x;
	float y1 = lineEnd.y;
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
	float gradient = (float)deltaY / (float)deltaX;

	// 1. 对于整数坐标点，与Bresenham一致
	int xend = mround(x0);
	float yend = y0 + gradient*(xend - x0);
	float xgap = rfpart(x0 + 0.5f);
	int xpxl1 = xend;
	int ypxl1 = ipart(yend);
	// TODO: begin and end
	if (steep)
		myswap(&xpxl1, &ypxl1);

	fragCache.addFrag({ *lineBegin.info*(rfpart(yend)*xgap), xpxl1, ypxl1 });
	fragCache.addFrag({ *lineBegin.info*(fpart(yend)*xgap), xpxl1, ypxl1 + 1 });
	if (steep)
		myswap(&xpxl1, &ypxl1);

	float intery = yend + gradient;

	xend = mround(x1);
	yend = y1 + gradient*(xend - x1);
	xgap = rfpart(x1 + 0.5f);
	int xpxl2 = xend;
	int ypxl2 = ipart(yend);
	// TODO: begin and end
	if (steep)
		myswap(&xpxl1, &ypxl1);
	fragCache.addFrag({ *lineBegin.info*(rfpart(yend)*xgap), xpxl2, ypxl2  });
	fragCache.addFrag({ *lineBegin.info*(fpart(yend)*xgap), xpxl2, ypxl2 + 1 });
	if (steep)
		myswap(&xpxl1, &ypxl1);

	
	// main loop
	for (int x = xpxl1 + 1; x < xpxl2; x++) {
		// 点的颜色值按照比例分配给它的上下两个点
		if (steep) {
			fragCache.addFrag({ *lineBegin.info*(rfpart(intery)), ipart(intery), x });
			fragCache.addFrag({ *lineBegin.info*(fpart(intery)), ipart(intery) + 1, x });
		}
		else {
			fragCache.addFrag({ *lineBegin.info*(rfpart(intery)), x, ipart(intery) });
			fragCache.addFrag({ *lineBegin.info*(fpart(intery)), x, ipart(intery) + 1 });
		}

		intery += gradient;
	}
}
#endif
