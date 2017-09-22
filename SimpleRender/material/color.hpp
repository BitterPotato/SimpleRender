#ifndef COLOR_HPP
#define COLOR_HPP

#define LIMIT 255

#include <iostream>

class BGRA {
public:
	int b; int g;  int r; int a;

	BGRA(int b = 0, int g = 0, int r = 0, int a = LIMIT) {
		this->b = b;
		this->g = g;
		this->r = r;
		this->a = a;

//		std::cout << "constructor";
	}
	BGRA(const BGRA& bgra) : b(bgra.b), g(bgra.g), r(bgra.r), a(bgra.a) {
//		std::cout << "copy constructor";
	}
	~BGRA() {
//		std::cout << "deconstructor";
	}

	inline friend BGRA* inter(const BGRA* from, const BGRA* to, const float t);
	inline friend BGRA operator*(const BGRA& bgra, const float ratio);
	inline friend float toFloat(int comp);
};

class HSV {
public:
	int h; float s; float v;

	HSV(int h = 0, float s = 0.0f, float v = 0.0f) {
		this->h = h;
		this->s = s;
		this->v = v;
	}

	friend HSV fromRGB(int r, int g, int b);
};
#include "color.inl"

#endif