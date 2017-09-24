//
// Created by WJ Yang on 2017/9/22.
//

#include "FVertex.hpp"

FVertex& FVertex::operator=(FVertex fVertex) {
    swap(*this, fVertex);
    return *this;
}
// friend func: to use swap outsides
void swap(FVertex& first, FVertex& second) // nothrow
{
    // enable ADL (not necessary in our case, but good practice)
    using std::swap;

    // by swapping the members of two objects,
    // the two objects are effectively swapped
    swap(first.point, second.point);
    swap(first.rgba, second.rgba);
    swap(first.tex, second.tex);
}
bool inter(const FVertex& from, const FVertex& to, const float t, FVertex& out) {
    if (t < 0 || t > 1)
        return false;

    out.point = inter(from.point, to.point, t);
    out.rgba = inter(from.rgba, to.rgba, t );
    out.tex = inter(from.tex, to.tex, t);
    return true;
}