#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "FragCache.hpp"
#include "math/TVector_Trans.hpp"
#include "material/Texture.hpp"

#include <algorithm>
#include <geometry/Shape2D.hpp>
#include <geometry/Triangle2D.hpp>
#include <common/Vertex.hpp>

using Geometry::ITriangle2D;

namespace Gl {
	class Triangle {
	public:
		MY_UTIL_DECL void rasterTriangle(const Vertex &vertexA, const Vertex &vertexB, const Vertex &vertexC,
									  const unique_ptr<Texture> &texture, FragCache &fragCache) ;
		MY_UTIL_DECL void rasterTriangleWire(const Vertex &vertexA, const Vertex &vertexB, const Vertex &vertexC, FragCache &fragCache) ;
	};

}
#endif
