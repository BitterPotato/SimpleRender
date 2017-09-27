#ifndef SIMPLERENDER_VERTEX_INL
#define SIMPLERENDER_VERTEX_INL

#include "Vertex.hpp"

void Vertex::inter(const fvec2& first, const fvec2& second, const fvec2& third, fvec2& out, const fvec3& ratio) {
    out[U] = first[U]*ratio[0] + second[U]*ratio[1] + third[U]*ratio[2];
    out[V] = first[V]*ratio[0] + second[V]*ratio[1] + third[V]*ratio[2];
}

#endif