#include "frag_shader.hpp"

void MyFragShader::shade(const Frag& frag) const {
	//if (frag.x < 400) {
	mFrameBuffer.setBufferPixel(frag.x, frag.y, *(frag.info->bgra));
	//}
}
