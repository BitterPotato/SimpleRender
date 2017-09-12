#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "../raster/Frag.hpp"

#include <vector>

using std::vector;

class Shape {
public:
	virtual void tessellate(vector<FVertex>& outVertexData) const = 0;
};


#endif