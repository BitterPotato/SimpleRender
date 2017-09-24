#include "MyVertexShader.hpp"

void MyVertexShader::shade(const FVertex& input, FVertex& output) const {
	// pass through, just for test
	// call copy method
	output = input;
}