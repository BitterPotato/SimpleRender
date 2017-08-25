#ifndef FRAG_HPP
#define FRAG_HPP

#include "../util/type_def.hpp"

// colors
typedef struct { 
	int b; int g;  int r; int a;
} BGRA;
// TODO: why method cause LINK2005 error
//BGRA operator*(const BGRA& bgra, const float ratio) {
//	return { mround(bgra.r*ratio), mround(bgra.g*ratio), mround(bgra.b*ratio), mround(bgra.a*ratio) };
//}

typedef struct {
	BGRA bgra; int depth; int stencil;
} Info;
//Info operator*(const Info& a, const float ratio) {
//	return { a.bgra*ratio, a.depth, a.stencil };
//}

// just shallow copy
typedef struct stu{
	int x; int y; Info& info;
	stu operator=(stu& stuInst) {
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
