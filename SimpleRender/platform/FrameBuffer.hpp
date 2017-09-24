#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "common/Frag.hpp"

class FrameBuffer {
public:
	MY_SMALL_FUNC_DECL void linkForm(void* ptr);
	MY_SMALL_FUNC_DECL void setBufferStorage(const int width, const int height);
	MY_COMP_FUNC_DECL void setBufferPixel(const int x, const int y, const RGBA & bgra);
	MY_COMP_FUNC_DECL void clearColor(const RGBA& bgra);
private:
	unsigned char * fbuffer = nullptr;
	int width; int height;
};
#endif