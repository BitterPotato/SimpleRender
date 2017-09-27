#include "FrameBuffer.hpp"

#include "material/Rgba.hpp"

void FrameBuffer::setBufferPixel(const int x, const int y, const RGBA & rgba) {
	if (x < width && y < height) {
		int startIndex = (y*width + x) * 4;
		fbuffer[startIndex] = rgba[B];
		fbuffer[startIndex + 1] = rgba[G];
		fbuffer[startIndex + 2] = rgba[R];
		fbuffer[startIndex + 3] = rgba[A];
	}
}
void FrameBuffer::clearColor(const RGBA& rgba) {
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			setBufferPixel(x, y, rgba);
}