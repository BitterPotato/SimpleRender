#include "texture.hpp"

FITexture::FITexture(const char* img) {
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(img);
    image = FreeImage_Load(fif, img);
}
FITexture::~FITexture() {
    // do nothing
    if(image) {
        delete image;
        image = nullptr;
    }
}

int FITexture::width() const {
    return FreeImage_GetWidth(image);
}
int FITexture::height() const {
    return FreeImage_GetHeight(image);
}
bool FITexture::getPixelColor(int x, int y, BGRA& bgra) const {
    if (x < 0 || x >= width() || y < 0 || y >= height())
        return false;

    RGBQUAD color;
    bool res = FreeImage_GetPixelColor(image, x, y, &color);

    bgra.r = color.rgbRed;
    bgra.g = color.rgbGreen;
    bgra.b = color.rgbBlue;
    return res;
}


