#ifndef FRAG_HPP
#define FRAG_HPP

#include <iostream>

#include "../util/type_def.hpp"

// colors
typedef struct BGRA {
	int b; int g;  int r; int a;
};
// TODO: why method cause LINK2005 error
//BGRA operator*(const BGRA& bgra, const float ratio) {
//	return { mround(bgra.r*ratio), mround(bgra.g*ratio), mround(bgra.b*ratio), mround(bgra.a*ratio) };
//}

typedef struct Info {
	BGRA* bgra; int depth; int stencil;
	~Info() {
		std::cout << "Info de_construct\n";
	}
};
//Info operator*(const Info& a, const float ratio) {
//	return { a.bgra*ratio, a.depth, a.stencil };
//}

// just shallow copy
typedef struct stu{
	int x; int y; Info& info;
	stu operator=(const stu& stuInst) {
		x = stuInst.x;
		y = stuInst.y;
		info = stuInst.info;
	}
} Frag;

typedef Frag Vertex;

typedef struct { int x; int y; } Point;

// frag shader fun pointer
typedef void(*fragShader)(const Frag&);

#include "Frag.inl"

#endif
