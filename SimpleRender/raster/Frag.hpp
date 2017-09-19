#ifndef FRAG_HPP
#define FRAG_HPP

#define CONSTRUCT_INFO_ENABLE

#include "../math/tvector.hpp"

#include <iostream>

using std::cout;

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
	friend BGRA* inter(const BGRA* from, const BGRA* to, const float t) {
		BGRA* bgra = new BGRA();
		bgra->b = (1 - t)*from->b + t*to->b;
		bgra->g = (1 - t)*from->g + t*to->g;
		bgra->r = (1 - t)*from->r + t*to->r;
		bgra->a = (1 - t)*from->a + t*to->a;

		return bgra;
	}
	friend BGRA operator*(const BGRA& bgra, const float ratio);
};

struct Info {
	// depth can be integer, but that needs one more step:
	// map the z \in (n, f) -> (0, B-1)
	// for simplicity, just use float
	BGRA* bgra; float depth; int stencil;
	Info(float depth=0.0f, int stencil=0) {
		// default construct
		bgra = new BGRA();
		this->depth = depth;
		this->stencil = stencil;
#ifdef CONSTRUCT_INFO_ENABLE
		cout << "Info: first constructor" << endl;
#endif
	}
	Info(BGRA* bgra, float depth=0.0f, int stencil=0) {
		this->bgra = bgra;
		this->depth = depth;
		this->stencil = stencil;
#ifdef CONSTRUCT_INFO_ENABLE
		cout << "Info: second constructor" << endl;
#endif
	}
	// some sort of constructor
	Info(const Info& info) {
		bgra = new BGRA(*info.bgra);
		depth = info.depth;
		stencil = info.stencil;
#ifdef CONSTRUCT_INFO_ENABLE
		cout << "Info: copy constructor" << endl;
#endif
	}
	Info(Info&& info) noexcept {
		bgra = info.bgra;
		depth = info.depth;
		stencil = info.stencil;
		info.bgra = nullptr;
#ifdef CONSTRUCT_INFO_ENABLE
		cout << "Info: move constructor" << endl;
#endif
	}
	// deep copy, avoid self =
	Info& operator=(Info info){
		swap(*this, info);
		return *this;
	}
	Info* operator*(float ratio) {
		BGRA tmpBGRA = *bgra*ratio;
		BGRA* rBgra = new BGRA(tmpBGRA);
		Info* rInfo = new Info{ rBgra, depth, stencil };
		return rInfo;
	}
	Info& operator=(Info&& info) noexcept {
		if (this != &info) {
			delete bgra;
			bgra = info.bgra;
			depth = info.depth;
			stencil = info.stencil;
			info.bgra = nullptr;
		}
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
	friend Info* inter(const Info* from, const Info* to, const float t) {
		Info* info = new Info();

		BGRA* bgra = inter(from->bgra, to->bgra, t);
		info->bgra = bgra;
		info->depth = (1 - t)*from->depth + t*to->depth;
		info->stencil = (1 - t) * from->stencil + t*to->stencil;
		return info;
	}
	~Info() noexcept {
		if (bgra) {
			delete bgra;
			bgra = nullptr;
		}
		
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
#ifdef CONSTRUCT_INFO_ENABLE
		cout << "Frag: constructor" << endl;
#endif
	}
	Frag(const Frag& frag) : x(frag.x), y(frag.y) {
		info = new Info(*frag.info);
#ifdef CONSTRUCT_INFO_ENABLE
		cout << "Frag: copy constructor" << endl;
#endif
	}
	Frag(Frag&& frag) noexcept : info(frag.info), x(frag.x), y(frag.y) {
		frag.info = nullptr;
#ifdef CONSTRUCT_INFO_ENABLE
		cout << "Frag: move constructor" << endl;
#endif
	}
	Frag& operator=(Frag frag) {
		swap(*this, frag);
		return *this;
	}
	Frag& operator=(Frag&& frag) noexcept {
		if (&frag != this) {
			delete info;
			info = frag.info;
			x = frag.x;
			y = frag.y;
			frag.info = nullptr;
		}
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
		if (info) {
			delete info;
			info = nullptr;
		}
#ifdef CONSTRUCT_INFO_ENABLE
		cout << "Frag: deconstructor" << endl;
#endif
	}
};

struct TexCoord {
	float u; float v;
	TexCoord(float u = 0.0f, float v = 0.0f) {
		this->u = u;
		this->v = v;
	}
	friend TexCoord inter(const TexCoord& from, const TexCoord& to, const float t) {
		return TexCoord((1 - t)*from.u + t*to.u, (1 - t)*from.v + t*to.v);
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
	float x; float y; float z; float w;
	// TODO: has the member info, seems strange
	Info* info;
	TexCoord tex;
	
	FVertex(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) {
		info = new Info();
		tex = TexCoord();

		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	FVertex(Info* info, float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f, TexCoord tex = TexCoord()) {
		this->info = info;
		this->tex = tex;

		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	FVertex(const FVertex& fVertex) : x(fVertex.x), y(fVertex.y), z(fVertex.z), w(fVertex.w){
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
		swap(first.w, second.w);
		swap(first.tex, second.tex);
		swap(*first.info, *second.info);
	}
	friend bool inter(const FVertex& from, const FVertex& to, const float t, FVertex& out) {
		if (t < 0 || t > 1)
			return false;

		out.x = (1 - t)*from.x + t*to.x;
		out.y = (1 - t)*from.y + t*to.y;
		out.z = (1 - t)*from.z + t*to.z;
		out.w = (1 - t)*from.w + t*to.w;
		out.tex = inter(from.tex, to.tex, t);
		out.info = inter(from.info, to.info, t);
		return true;
	}
	friend fvec3 extractVec(const FVertex& fVertex) {
		return fvec3(fVertex.x, fVertex.y, fVertex.z);
	}
	~FVertex() {
		delete info;
	}
};

typedef struct { int x; int y; } Point;

#include "Frag.inl"

#endif
