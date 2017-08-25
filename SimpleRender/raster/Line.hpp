#ifndef LINE_HPP
#define LINE_HPP

#include "FragCache.hpp"

#include <cmath>

inline FragCache rasterLineB(const Vertex& lineBegin, const Vertex& lineEnd, const int width);
inline FragCache rasterLineBB(const Vertex& lineBegin, const Vertex& lineEnd, const int width);
inline FragCache rasterLineW(const Vertex& lineBegin, const Vertex& lineEnd, const int width);

inline FragCache rasterLine(const Vertex& lineBegin, const Vertex& lineEnd, const int width) {
#if defined(LINE_Bresenham)
	return rasterLineBB(lineBegin, lineEnd, width);
#elif defined(LINE_WuXiaolin)
	return rasterLineW(lineBegin, lineEnd, width);
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
		outFragCache.addFrag({ curX, curY, lineBP.info });
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
		outFragCache.addFrag({ curX, curY, lineBP.info });
	}
}

inline FragCache rasterLineB(const Vertex& lineBegin, const Vertex& lineEnd, const int width) {
	FragCache fragCache;

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
			fragCache.addFrag({ lineX, curY, lineBegin.info });
		}
		return fragCache;
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

	return fragCache;
}

inline FragCache rasterLineBB(const Vertex& lineBegin, const Vertex& lineEnd, const int width) {
	FragCache fragCache;

	int x0 = lineBegin.x;
	int y0 = lineBegin.y;
	int x1 = lineEnd.x;
	int y1 = lineEnd.y;
	bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
	if (steep) {
		swap(&x0, &y0);
		swap(&x1, &y1);
	}
	if (x0 > x1) {
		swap(&x0, &x1);
		swap(&y0, &y1);
	}
	int deltaX = x1 - x0;
	int deltaY = y1 - y0;
	float error = 0;
	float deltaError =(float) deltaY / (float)deltaX;
	
	int ySege = y0 > y1 ? -1 : 1;
	int curY = y0;
	for (int curX = x0; curX <= x1; curX++) {
		error += deltaError;
		if (std::abs(error) >= 0.5f) {
			curY += ySege;
			error -= ySege;
		}

		if (steep)
			fragCache.addFrag({ curY, curX, lineBegin.info });
		else
			fragCache.addFrag({ curX, curY, lineBegin.info });
	}
	return fragCache;
}


inline FragCache rasterLineW(const Vertex& lineBegin, const Vertex& lineEnd, const int width) {
	FragCache fragCache;

	float x0 = lineBegin.x;
	float y0 = lineBegin.y;
	float x1 = lineEnd.x;
	float y1 = lineEnd.y;
	bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
	if (steep) {
		swap(&x0, &y0);
		swap(&x1, &y1);
	}
	if (x0 > x1) {
		swap(&x0, &x1);
		swap(&y0, &y1);
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
		swap(&xpxl1, &ypxl1);
	fragCache.addFrag({ xpxl1, ypxl1, colorRatioInfo(lineBegin.info, rfpart(yend)*xgap) });
	fragCache.addFrag({ xpxl1, ypxl1 + 1, colorRatioInfo(lineBegin.info, fpart(yend)*xgap) });
	if (steep)
		swap(&xpxl1, &ypxl1);

	float intery = yend + gradient;

	xend = mround(x1);
	yend = y1 + gradient*(xend - x1);
	xgap = rfpart(x1 + 0.5f);
	int xpxl2 = xend;
	int ypxl2 = ipart(yend);
	// TODO: begin and end
	if (steep)
		swap(&xpxl1, &ypxl1);
	fragCache.addFrag({ xpxl2, ypxl2, colorRatioInfo(lineBegin.info, rfpart(yend)*xgap) });
	fragCache.addFrag({ xpxl2, ypxl2 + 1, colorRatioInfo(lineBegin.info, fpart(yend)*xgap) });
	if (steep)
		swap(&xpxl1, &ypxl1);

	
	// main loop
	for (int x = xpxl1 + 1; x < xpxl2; x++) {
		// 点的颜色值按照比例分配给它的上下两个点
		if (steep) {
			fragCache.addFrag({ ipart(intery), x, colorRatioInfo(lineBegin.info, rfpart(intery)) });
			fragCache.addFrag({ ipart(intery) + 1, x, colorRatioInfo(lineBegin.info, fpart(intery)) });
		}
		else {
			fragCache.addFrag({ x, ipart(intery), colorRatioInfo(lineBegin.info, rfpart(intery)) });
			fragCache.addFrag({ x, ipart(intery) + 1, colorRatioInfo(lineBegin.info, fpart(intery)) });
		}

		intery += gradient;
	}

	return fragCache;
}
#endif
