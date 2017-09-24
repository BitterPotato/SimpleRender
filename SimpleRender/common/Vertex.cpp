//
// Created by WJ Yang on 2017/9/22.
//

#include "Vertex.hpp"

Vertex& Vertex::operator=(const Vertex& vertex) {
    this->point = vertex.point;
    this->info = vertex.info;
    this->tex = vertex.tex;
    this->homo = vertex.homo;

    return *this;
}
Vertex& Vertex::operator=(Vertex vertex) {
    swap(*this, vertex);
    return *this;
}
void swap(Vertex& first, Vertex& second) // nothrow
{
    // enable ADL (not necessary in our case, but good practice)
    using std::swap;

    // by swapping the members of two objects,
    // the two objects are effectively swapped
    swap(first.point, second.point);
    swap(first.info, second.info);
    swap(first.tex, second.tex);
    swap(first.homo, second.homo);
}

void inter(const TexCoord& first, const TexCoord& second, const TexCoord& third, TexCoord& out, const fvec3& ratio) {
    float u = first[U]*ratio[0] + second[U]*ratio[1] + third[U]*ratio[2];
    float v = first[V]*ratio[0] + second[V]*ratio[1] + third[V]*ratio[2];
}

~Vertex() {

}