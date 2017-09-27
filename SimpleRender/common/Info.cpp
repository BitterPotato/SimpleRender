//
// Created by WJ Yang on 2017/9/22.
//

#include "Info.hpp"

// some sort of constructor
//Info::Info(const Info &info) {
//    rgba = RGBA(info.rgba);
//    depth = info.depth;
//    stencil = info.stencil;
//#ifdef CONSTRUCT_INFO_ENABLE
//    cout << "Info: copy constructor" << endl;
//#endif
//}

//Info::Info(Info &&info) noexcept {
//    rgba = info.rgba;
//    depth = info.depth;
//    stencil = info.stencil;
//#ifdef CONSTRUCT_INFO_ENABLE
//    cout << "Info: move constructor" << endl;
//#endif
//}

//Info &Info::operator=(Info &&info) noexcept {
//    if (this != &info) {
//        rgba = info.rgba;
//        depth = info.depth;
//        stencil = info.stencil;
//    }
//    return *this;
//}

Info::~Info() {
    //std::cout << "Info de_construct\n";
}

