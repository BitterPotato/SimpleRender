#ifndef POINT_HPP
#define POINT_HPP

#include "FragCache.hpp"

inline void rasterPoint(const Vertex& vertex, const int size, FragCache& outFragCache) {
	for (int i = -size; i <= size; i++) {
		for (int j = -size; j < size; j++) {
			BGRA* bgra = new BGRA(*vertex.info->bgra);
			Info* info = new Info(bgra);
			outFragCache.addFrag({ info , vertex.x + i, vertex.y + j});
		}
	}
}

#endif
