//
// Created by WJ Yang on 2017/9/22.
//

#ifndef SIMPLERENDER_FVERTEX_HPP
#define SIMPLERENDER_FVERTEX_HPP

#include "setup.hpp"
#include "Point.hpp"
#include "material/Rgba.hpp"

// input
class FVertex {
public:
    FVertex(FPoint4D p = FPoint4D(), RGBA r = RGBA(), fvec2 t = fvec2()) :
            point(p), rgba(r), tex(t){}
    FVertex(const FVertex& fVertex) :
            point(fVertex.point), rgba(fVertex.rgba), tex(fVertex.tex){}
    ~FVertex() {}

    FVertex& operator=(FVertex fVertex);

    // friend func: to use swap outsides
    MY_SFRIEND_FUNC_DECL void swap(FVertex& first, FVertex& second) {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // by swapping the members of two objects,
        // the two objects are effectively swapped
        swap(first.point, second.point);
        swap(first.rgba, second.rgba);
        swap(first.tex, second.tex);
    }
    MY_NFRIEND_FUNC_DECL bool inter(const FVertex& from, const FVertex& to, FVertex& out, const float t);

//private:
    FPoint4D point;
    RGBA rgba ;
    fvec2 tex;
};

#endif //SIMPLERENDER_FVERTEX_HPP
