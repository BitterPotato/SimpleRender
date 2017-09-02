#ifndef FRAG_HPP
#define FRAG_HPP

#include <iostream>

#include "../util/type_def.hpp"

// colors
//struct BGRA {
//	int b; int g;  int r; int a;
//	// TODO: why method cause LINK2005 error
//	friend BGRA operator*(const BGRA& bgra, const float ratio);
//	//BGRA operator*(const BGRA& bgraA, const BGRA& bgraB) {
//	//	return {};
//	//}
//};

class BGRA {
public:
	int b; int g;  int r; int a;

	friend BGRA operator*(const BGRA& bgra, const float ratio);
};

struct Info {
	BGRA* bgra; int depth; int stencil;
	Info(BGRA* bgra, int depth=0, int stencil=0) {
		this->bgra = bgra;
		this->depth = depth;
		this->stencil = stencil;
	}
	~Info() {
		std::cout << "Info de_construct\n";
	}
};

// just shallow copy
struct Frag{
	int x; int y; Info& info;
	Frag(Info& info, int x = 0, int y = 0): info(info) {
		this->x = x;
		this->y = y;
	}
	Frag operator=(const Frag& stuInst) {
		x = stuInst.x;
		y = stuInst.y;
		info = stuInst.info;
		return *this;
	}
};

typedef Frag Vertex;

typedef struct { int x; int y; } Point;

// frag shader fun pointer
typedef void(*fragShader)(const Frag&);

#include "Frag.inl"

#endif
