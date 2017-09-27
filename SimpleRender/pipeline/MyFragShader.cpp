#include "MyFragShader.hpp"
#include "platform/FrameBuffer.hpp"
#include "common/Frag.hpp"
#include "common/Info.hpp"
#include "common/Point.hpp"

void MyFragShader::shade(const Frag& frag) const {
	//if (frag.x < 400) {
	mFrameBuffer.setBufferPixel(frag.point[X], frag.point[Y], frag.info.rgba);
	//}
}
