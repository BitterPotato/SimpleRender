//
// Created by WJ Yang on 2017/9/24.
//

#ifndef SIMPLERENDER_RASTER_POINT_HPP
#define SIMPLERENDER_RASTER_POINT_HPP

#include "common/setup.hpp"

class Vertex;
class FragCache;

namespace Gl {
	class Point {
	public:
		MY_SMALL_UTIL_DECL void rasterPoint(const Vertex &vertex, const int size, FragCache &outFragCache) ;

	};
}

#include "Point.inl"

#endif //SIMPLERENDER_RASTER_POINT_HPP
