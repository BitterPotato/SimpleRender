//
// Created by WJ Yang on 2017/9/22.
//

#ifndef SIMPLERENDER_FRAG_HPP
#define SIMPLERENDER_FRAG_HPP

#include "setup.hpp"
#include "math/TVector.hpp"
#include "common/Info.hpp"

class Frag{
public:
    Frag(ivec2 p = ivec2(), Info i = Info()) :
            point(p), info(i){
#ifdef CONSTRUCT_INFO_ENABLE
        cout << "Frag: constructor" << endl;
#endif
    }
    Frag(const Frag& frag) :
            point(frag.point), info(frag.info) {
#ifdef CONSTRUCT_INFO_ENABLE
        cout << "Frag: copy constructor" << endl;
#endif
    }
    Frag(Frag&& frag) noexcept : point(frag.point), info(frag.info) {
#ifdef CONSTRUCT_INFO_ENABLE
        cout << "Frag: move constructor" << endl;
#endif
    }
    ~Frag() {
#ifdef CONSTRUCT_INFO_ENABLE
        cout << "Frag: deconstructor" << endl;
#endif
    }

    MY_OPERATOR_DECL Frag& operator=(Frag frag) {
        swap(*this, frag);
        return *this;
    }
    MY_OPERATOR_DECL Frag& operator=(Frag&& frag) noexcept {
        if (&frag != this) {
            point = frag.point;
            info = frag.info;
        }
        return *this;
    }
    MY_SFRIEND_FUNC_DECL void swap(Frag& first, Frag& second) {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // by swapping the members of two objects,
        // the two objects are effectively swapped
        swap(first.point, second.point);
        swap(first.info, second.info);
    }

//private:
    ivec2 point;
    Info info;
};

#endif //SIMPLERENDER_FRAG_HPP
