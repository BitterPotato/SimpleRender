#ifndef SIMPLERENDER_INFO_INL
#define SIMPLERENDER_INFO_INL

#include "Info.hpp"

void Info::assign(const Info &info) {
    this->rgba = info.rgba;
    this->depth = info.depth;
    this->stencil = info.stencil;
}

void Info::scale(const float ratio) {
    rgba *= ratio;
}

Info inter(const Info& from, const Info& to, const float t){
    Info info;

    RGBA rgba = inter(from.rgba, to.rgba, t);
    info.rgba = rgba;
    info.depth = (1 - t) * from.depth + t * to.depth;
    info.stencil = static_cast<int>((1 - t) * from.stencil + t * to.stencil);
    return info;
}

void interDepth(const Info& first, const Info& second, const Info& third, Info& out, const fvec3& ratio) {
    out.depth = first.depth*ratio[0] + second.depth*ratio[1] + third.depth*ratio[2];
}

#endif