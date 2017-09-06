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
	BGRA(int b=0, int g=0, int r=0, int a=0) {
		this->b = b;
		this->g = g;
		this->r = r;
		this->a = a;
	}
	BGRA(const BGRA& bgra) : b(bgra.b), g(bgra.g), r(bgra.r), a(bgra.a) {}
	friend BGRA operator*(const BGRA& bgra, const float ratio);
};

struct Info {
	BGRA* bgra; int depth; int stencil;
	Info(int depth=0, int stencil=0) {
		// default construct
		bgra = new BGRA();
		this->depth = depth;
		this->stencil = stencil;
	}
	Info(BGRA* bgra, int depth=0, int stencil=0) {
		this->bgra = bgra;
		this->depth = depth;
		this->stencil = stencil;
	}
	// some sort of constructor
	Info(const Info& info) {
		bgra = new BGRA(*info.bgra);
		depth = info.depth;
		stencil = info.stencil;
	}
	// deep copy, avoid self =
	Info& operator=(Info info){
		swap(*this, info);
		return *this;
	}
	friend void swap(Info& first, Info& second) // nothrow
	{
		// enable ADL (not necessary in our case, but good practice)
		using std::swap;

		// by swapping the members of two objects,
		// the two objects are effectively swapped
		// attention: the input parameter aren't pointers, if BGRA implements
		// the swap function, then it will delivery
		swap(*first.bgra, *second.bgra);
		swap(first.depth, second.depth);
		swap(first.stencil, second.stencil);
	}
	~Info() {
		delete bgra;
		//std::cout << "Info de_construct\n";
	}
};

// just shallow copy
struct Frag{
	int x; int y; Info* info;
	Frag(int x = 0, int y = 0) {
		info = new Info();
		this->x = x;
		this->y = y;
	}
	Frag(Info* info, int x = 0, int y = 0) {
		this->info = info;
		this->x = x;
		this->y = y;
	}
	Frag(const Frag& frag) : x(frag.x), y(frag.y) {
		info = new Info(*frag.info);
	}
	Frag& operator=(Frag frag) {
		swap(*this, frag);
		return *this;
	}
	friend void swap(Frag& first, Frag& second) // nothrow
	{
		// enable ADL (not necessary in our case, but good practice)
		using std::swap;

		// by swapping the members of two objects,
		// the two objects are effectively swapped
		swap(first.x, second.x);
		swap(first.y, second.y);
		swap(*first.info, *second.info);
	}
	~Frag() {
		delete info;
	}
};

struct TexCoord {
	float u; float v;
	TexCoord(float u = 0.0f, float v = 0.0f) {
		this->u = u;
		this->v = v;
	}
	// copy/=/deconstructor unnecessary
};

struct Vertex {
	int x; int y; Info* info;
	TexCoord tex;
	// save the homogeneous divide value
	float h;

	Vertex(int x = 0, int y = 0) {
		info = new Info();
		tex = TexCoord();
		h = 0.0f;

		this->x = x;
		this->y = y;
	}
	Vertex(Info* info, int x = 0, int y = 0, TexCoord tex = TexCoord(), float h = 0.0f) {
		this->info = info;
		this->tex = tex;
		this->h = h;

		this->x = x;
		this->y = y;
	}
	Vertex(const Vertex& vertex) : x(vertex.x), y(vertex.y), h(vertex.h) {
		info = new Info(*vertex.info);
		tex = vertex.tex;
	}
	Vertex& operator=(Vertex vertex) {
		swap(*this, vertex);
		return *this;
	}
	friend void swap(Vertex& first, Vertex& second) // nothrow
	{
		// enable ADL (not necessary in our case, but good practice)
		using std::swap;

		// by swapping the members of two objects,
		// the two objects are effectively swapped
		swap(first.x, second.x);
		swap(first.y, second.y);
		swap(first.h, second.h);

		swap(first.tex, second.tex);
		swap(*first.info, *second.info);
	}
	~Vertex() {
		delete info;
	}
};

struct FVertex {
	float x; float y; float z; Info* info;
	TexCoord tex;
	
	FVertex(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
		info = new Info();
		tex = TexCoord();

		this->x = x;
		this->y = y;
		this->z = z;
	}
	FVertex(Info* info, float x = 0.0f, float y = 0.0f, float z = 0.0f, TexCoord tex = TexCoord()) {
		this->info = info;
		this->tex = tex;

		this->x = x;
		this->y = y;
		this->z = z;
	}
	FVertex(const FVertex& fVertex) : x(fVertex.x), y(fVertex.y), z(fVertex.z){
		info = new Info(*fVertex.info);
		tex = fVertex.tex;
	}
	FVertex& operator=(FVertex fVertex) {
		using std::swap;

		swap(*this, fVertex);
		return *this;
	}
	// friend func: to use swap outsides
	friend void swap(FVertex& first, FVertex& second) // nothrow
	{
		// enable ADL (not necessary in our case, but good practice)
		using std::swap;

		// by swapping the members of two objects,
		// the two objects are effectively swapped
		swap(first.x, second.x);
		swap(first.y, second.y);
		swap(first.z, second.z);
		swap(first.tex, second.tex);
		swap(*first.info, *second.info);
	}
	~FVertex() {
		delete info;
	}
};

typedef struct { int x; int y; } Point;

#include "Frag.inl"

#endif
