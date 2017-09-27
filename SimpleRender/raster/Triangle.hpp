#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "common/setup.hpp"

class Texture;
class FragCache;
class Vertex;

namespace Gl {
	class Triangle {
	public:
		MY_UTIL_DECL void rasterTriangle(const Vertex &vertexA, const Vertex &vertexB, const Vertex &vertexC,
									  const unique_ptr<Texture> &texture, FragCache &fragCache) ;
		MY_UTIL_DECL void rasterTriangleWire(const Vertex &vertexA, const Vertex &vertexB, const Vertex &vertexC, FragCache &fragCache) ;
	};

}
#endif
