#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "../raster/Frag.hpp"

class framebuffer {
public:
	void linkForm(void* ptr);
	void setBufferStorage(const int width, const int height);
	void setBufferPixel(const int x, const int y, const BGRA & bgra);
private:
	unsigned char * fbuffer = nullptr;
	int width; int height;
};
#endif