#include "FITexture.hpp"
#include "third/FreeImage.h"
#include "material/Rgba.hpp"

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

// TODO: texture wrap/ filter mode
bool FITexture::getPixelColor(const int x, const int y, RGBA& out) const {
    if (x < 0 || x > width() || y < 0 || y > height())
        return false;

    // deal with the border value
    int xc = x==0? 1:x;
    xc = x==width()? width()-1 : x;
    int yc = y==0? 1:y;
    yc = y==height()? height()-1 : y;

    RGBQUAD color;
    bool res = FreeImage_GetPixelColor(image, xc, yc, &color);

    out[R] = color.rgbRed;
    out[G] = color.rgbGreen;
    out[B] = color.rgbBlue;
    return res;
}

bool FITexture::getUVPixelColor(const float u, const float v, RGBA& out) const {
    return getPixelColor(u*width(), v*height(), out);
}


