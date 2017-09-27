//
// Created by WJ Yang on 2017/9/22.
//

#include "FVertex.hpp"

FVertex& FVertex::operator=(FVertex fVertex) {
    swap(*this, fVertex);
    return *this;
}

bool inter(const FVertex& from, const FVertex& to, FVertex& out, const float t) {
    if (t < 0 || t > 1)
        return false;

    out.point = inter(from.point, to.point, t);
    out.rgba = inter(from.rgba, to.rgba, t );
    out.tex = inter(from.tex, to.tex, t);
    return true;
}