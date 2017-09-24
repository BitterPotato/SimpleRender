//
// Created by WJ Yang on 2017/9/24.
//

#ifndef SIMPLERENDER_POINT_HPP
#define SIMPLERENDER_POINT_HPP

#include <common/Point.hpp>
#include <common/Vertex.hpp>
#include "FragCache.hpp"

namespace Gl {
	class Point {
	public:
		MY_SMALL_UTIL_DECL void rasterPoint(const Vertex &vertex, const int size, FragCache &outFragCache) ;

	};
}

#endif //SIMPLERENDER_POINT_HPP
