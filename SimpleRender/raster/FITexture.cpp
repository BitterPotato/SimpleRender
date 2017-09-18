#include "texture.hpp"

FITexture::FITexture(const char* img) {
	image.load(img);
}
FITexture::~FITexture() {
	// do nothing
	image = NULL;
}

int FITexture::width() const {
	return image.getWidth();
}
int FITexture::height() const {
	return image.getHeight();
}
bool FITexture::getPixelColor(int x, int y, BGRA& bgra) const {
	if (x < 0 || x >= width() || y < 0 || y >= height())
		return false;
		
	RGBQUAD color;
	bool res = image.getPixelColor(x, y, &color);

	// TODO: why the color cannot get results in place
	bgra.r = color.rgbBlue;
	bgra.g = color.rgbGreen;
	bgra.b = color.rgbRed;
}
