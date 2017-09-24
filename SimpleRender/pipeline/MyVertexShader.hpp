#ifndef VERTEX_SHADER_HPP
#define VERTEX_SHADER_HPP

#include "VertexShader.hpp"

class MyVertexShader : public VertexShader {
	MY_COMP_FUNC_DECL void shade(const FVertex& input, FVertex& output) const override ;
};

#endif
