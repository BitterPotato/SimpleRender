//
// Created by WJ Yang on 2017/9/22.
//

#include "Info.hpp"

Info::Info(RGBA b = RGBA(), float d = 0.0f, int s = 0) :
    rgba(b), depth(d), stencil(s){
#ifdef CONSTRUCT_INFO_ENABLE
    cout << "Info: constructor" << endl;
#endif
}

// some sort of constructor
Info::Info(const Info &info) {
    rgba = RGBA(info.rgba);
    depth = info.depth;
    stencil = info.stencil;
#ifdef CONSTRUCT_INFO_ENABLE
    cout << "Info: copy constructor" << endl;
#endif
}

Info::Info(Info &&info) noexcept {
    rgba = info.rgba;
    depth = info.depth;
    stencil = info.stencil;
#ifdef CONSTRUCT_INFO_ENABLE
    cout << "Info: move constructor" << endl;
#endif
}

Info& Info::operator=(const Info& info) {
    assign(info);
    return *this;
}

// for no-pointer Info, of less use
Info &Info::operator=(Info info) {
    swap(*this, info);
    return *this;
}

Info &Info::operator*(const float ratio) {
    scale(ratio);
    return *this;
}

// TODO: test move
Info Info::operator*(const float ratio) const {
    Info info = Info(*this);
    info.scale(ratio);
    return info;
}

Info& Info::operator*=(const float ratio) {
    scale(ratio);
    return *this;
}

Info &Info::operator=(Info &&info) noexcept {
    if (this != &info) {
        rgba = info.rgba;
        depth = info.depth;
        stencil = info.stencil;
    }
    return *this;
}

Info::~Info() {
    //std::cout << "Info de_construct\n";
}

void swap(Info &first, Info &second) // nothrow
{
    // enable ADL (not necessary in our case, but good practice)
    using std::swap;

    // by swapping the members of two objects,
    // the two objects are effectively swapped
    // attention: the input parameter aren't pointers, if RGBA implements
    // the swap function, then it will delivery
    swap(first.rgba, second.rgba);
    swap(first.depth, second.depth);
    swap(first.stencil, second.stencil);
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

void Info::assign(const Info &info) {
    this->rgba = info.rgba;
    this->depth = info.depth;
    this->stencil = info.stencil;
}

void Info::scale(const float ratio) {
    rgba *= ratio;
}
