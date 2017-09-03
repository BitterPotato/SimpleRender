#include "frag_shader.hpp"

void MyFragShader::shade(const Frag& frag) const {
	//if (frag.x < 400) {
	framebuffer->setBufferPixel(frag.x, frag.y, *(frag.info->bgra));
	//}
}
