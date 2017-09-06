#include "vertex_shader.hpp"

void MyVertexShader::shade(const FVertex& input, FVertex& output) const {
	// pass through, just for test
	// call copy method
	*output.info = *input.info;
	output.tex = input.tex;
	output.x = input.x;
	output.y = input.y;
	output.z = input.z;
}