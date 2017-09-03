#ifndef VERTEX_SHADER_HPP
#define VERTEX_SHADER_HPP

#include "../raster/Frag.hpp"

class VertexShader {
public:
	virtual void shade(const FVertex& input, FVertex& output) const = 0;
};

class MyVertexShader : public VertexShader {
	void shade(const FVertex& input, FVertex& output) const;
};
#endif
