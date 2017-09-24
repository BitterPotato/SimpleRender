#ifndef TEXTURE_HPP
#define TEXTURE_HPP


#include "material/Rgba.hpp"

class Texture {
public:
	virtual int width() const = 0;
	virtual int height() const = 0;
	virtual bool getPixelColor(const int x, const int y, RGBA& out) const = 0;
	virtual bool getUVPixelColor(const float u, const float v, RGBA& out) const = 0;
};


#endif