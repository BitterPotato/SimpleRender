#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "FragCache.hpp"
#include "../math/tvector_trans.hpp"

#include <algorithm>

struct Bary {
	float alpha;
	float beta;
	float gamma;
}; 

inline float computeAreaRatio(const Point& point1, const Point& point2, const Point& pointSide, const Point& point) {
	TVector2<int> vecSide1 = { point1.x - pointSide.x, point1.y - pointSide.y };
	TVector2<int> vecSide2 = { point2.x - pointSide.x, point2.y - pointSide.y };
	TVector2<int> vec1 = { point1.x - point.x, point1.y - point.y };
	TVector2<int> vec2 = { point2.x - point.x, point2.y - point.y };

	return  static_cast<float>(math::cross<int>(vec1, vec2)) / math::cross<int>(vecSide1, vecSide2);
}


inline bool isPartInTri(const float x) {
	return x >= 0 && x <= 1;
}


inline void computeBaryCoord(const Point& pointA, const Point& pointB, const Point& pointC, const Point& point, Bary& outBary, int& outCount) {
	outBary.alpha = computeAreaRatio(pointB, pointC, pointA, point);
	if (isPartInTri(outBary.alpha)) {
		outCount++;

		outBary.beta = computeAreaRatio(pointA, pointC, pointB, point);
		if (isPartInTri(outBary.beta)) {
			outCount++;

			outBary.gamma = 1 - outBary.alpha - outBary.beta;
			if(isPartInTri(outBary.gamma))
				outCount++;
		}
	}
}


inline void computeInterColor(const BGRA& bgraA, const BGRA& bgraB, const BGRA& bgraC, const Bary& bary, BGRA& outBgra) {
	outBgra.b = bgraA.b*bary.alpha + bgraB.b*bary.beta + bgraC.b*bary.gamma;
	outBgra.g = bgraA.g*bary.alpha + bgraB.g*bary.beta + bgraC.g*bary.gamma;
	outBgra.r = bgraA.r*bary.alpha + bgraB.r*bary.beta + bgraC.r*bary.gamma;
	outBgra.a = bgraA.a*bary.alpha + bgraB.a*bary.beta + bgraC.a*bary.gamma;
}
// TODO: on triangle

// TODO: 1. bounding box
inline void rasterTriangle(const Vertex& vertexA, const Vertex& vertexB, const Vertex& vertexC, FragCache& fragCache) {
	using std::min;
	using std::max;

	// find bounding box
	int top_left_x = min(vertexA.x, min(vertexB.x, vertexC.x));
	int top_left_y = min(vertexA.y, min(vertexB.y, vertexC.y));
	int bottom_right_x = max(vertexA.x, max(vertexB.x, vertexC.x));
	int bottom_right_y = max(vertexA.y, max(vertexB.y, vertexC.y));

	// tranverse, compute barycentric coordinate
	Point pointA { vertexA.x, vertexA.y };
	Point pointB { vertexB.x, vertexB.y };
	Point pointC { vertexC.x, vertexC.y };
	for (int x = top_left_x; x < bottom_right_x; x++) {
		for (int y = top_left_y; y < bottom_right_y; y++) {
			Point point { x, y };
			Bary bary;
			int count = 0;
			computeBaryCoord(pointA, pointB, pointC, point, bary, count);
			if (count == 3) {
				BGRA* bgra = new BGRA();
				computeInterColor(*vertexA.info.bgra, *vertexB.info.bgra, *vertexC.info.bgra, bary, *bgra);

				Info* info = new Info(bgra, 0, 0);
				fragCache.addFrag({x, y, *info});
			}
		}
	}
}


// as for function
//1. 没副作用的方法类似const方法
//2. 选择业务交接点，不纯的函数
//3. 底层函数不纯影响所有调用它的方法
//4. 常常意味着更多参数
//5. C++容器的复制后果可能是性能糟糕的
//6. 并非所有方法都使用复制，例如光栅化前的framebuffer和光栅化后的framebuffer
#endif
