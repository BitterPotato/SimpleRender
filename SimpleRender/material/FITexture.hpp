#ifndef FITexture_HPP
#define FITexture_HPP

#include "Texture.hpp"

class FIBITMAP;

class FITexture : public Texture {
public:
    FITexture(const char* img);
    FITexture(const FITexture& texture) = delete;
    FITexture& operator=(FITexture texture) = delete;
    ~FITexture();

    int width() const override ;
    int height() const override ;
    bool getPixelColor(const int x, const int y, RGBA& out) const override ;
    bool getUVPixelColor(const float u, const float v, RGBA& out) const override ;
private:
    FIBITMAP* image;
};

#endif