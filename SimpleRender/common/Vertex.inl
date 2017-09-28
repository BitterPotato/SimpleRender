#ifndef SIMPLERENDER_VERTEX_INL
#define SIMPLERENDER_VERTEX_INL

#include "Vertex.hpp"

void Vertex::inter(const TexCoord& first, const TexCoord& second, const TexCoord& third, TexCoord& out, const fvec3& ratio) {
    out[U] = first[U]*ratio[0] + second[U]*ratio[1] + third[U]*ratio[2];
    out[V] = first[V]*ratio[0] + second[V]*ratio[1] + third[V]*ratio[2];
}

#endif