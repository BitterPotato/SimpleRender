#ifndef POINT_HPP
#define POINT_HPP

#include "FragCache.hpp"

inline FragCache rasterPoint(const Vertex& vertex, const int size) {

	FragCache fragCache;
	for (int i = -size; i <= size; i++) {
		for (int j = -size; j < size; j++) {
			Frag frag(vertex.info, vertex.x + i, vertex.y + j);
			fragCache.addFrag(frag);
		}
	}

	return fragCache;
}

#endif
