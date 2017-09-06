#include "../stdafx.h"
#include "framebuffer.hpp"

#include <cstdlib>
#include <cstring>

void FrameBuffer::linkForm(void* ptr) {
	fbuffer = (unsigned char*)ptr;
}
void FrameBuffer::setBufferStorage(const int width, const int height) {
	//if (fbuffer)
	//	free(fbuffer);
	this->width = width;
	this->height = height;
	std::memset(fbuffer, 0, width*height * 4);
}
void FrameBuffer::setBufferPixel(const int x, const int y, const BGRA & bgra) {
	if (x < width && y < height) {
		int startIndex = (y*width + x) * 4;
		fbuffer[startIndex] = bgra.r;
		fbuffer[startIndex + 1] = bgra.g;
		fbuffer[startIndex + 2] = bgra.b;
		fbuffer[startIndex + 3] = bgra.a;
	}
}
void FrameBuffer::clearColor(const BGRA& bgra) {
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			setBufferPixel(x, y, bgra);
}