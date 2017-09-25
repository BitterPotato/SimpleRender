//
// Created by WJ Yang on 2017/9/22.
//

#ifndef SIMPLERENDER_FRAG_HPP
#define SIMPLERENDER_FRAG_HPP


#include "Info.hpp"
#include "Point.hpp"

class Frag{
public:
    Frag(IPoint2D p = IPoint2D(), Info i = Info()) :
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

    MY_OPERATOR_DECL Frag& operator=(Frag frag);
    MY_OPERATOR_DECL Frag& operator=(Frag&& frag) noexcept ;
    MY_SFRIEND_FUNC_DECL void swap(Frag& first, Frag& second);

//private:
    IPoint2D point;
    Info info;
};

#endif //SIMPLERENDER_FRAG_HPP
