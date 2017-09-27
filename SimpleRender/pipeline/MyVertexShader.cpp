#include "MyVertexShader.hpp"
#include "common/FVertex.hpp"

void MyVertexShader::shade(const FVertex& input, FVertex& output) const {
	// pass through, just for test
	// call copy method
	output = input;
}