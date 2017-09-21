#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Frag.hpp"
#include "../third/FreeImage.h"

class Texture {
public:
	virtual int width() const = 0;
	virtual int height() const = 0;
	virtual bool getPixelColor(int x, int y, BGRA& bgra) const = 0;
};

class FITexture : public Texture {
public:
    FITexture(const char* img);
    FITexture(const FITexture& texture) = delete;
    FITexture& operator=(FITexture texture) = delete;
    ~FITexture();

    int width() const;
    int height() const;
    bool getPixelColor(int x, int y, BGRA& bgra) const;
private:
    FIBITMAP* image;
};
#endif