//
// Created by WJ Yang on 2017/9/22.
//

#ifndef SIMPLERENDER_FVERTEX_HPP
#define SIMPLERENDER_FVERTEX_HPP

#include "setup.hpp"
#include "Info.hpp"
#include "Point.hpp"

// input
class FVertex {
public:

    FVertex(FPoint4D p, RGBA r = RGBA(), TexCoord t = TexCoord()) :
            point(p), rgba(r), tex(t){}
    FVertex(const FVertex& fVertex) :
            point(fVertex.point), rgba(fVertex.rgba), tex(fVertex.tex){}
    ~FVertex() {}

    FVertex& operator=(FVertex fVertex);

    // friend func: to use swap outsides
    MY_SFRIEND_FUNC_DECL void swap(FVertex& first, FVertex& second);
    MY_NFRIEND_FUNC_DECL bool inter(const FVertex& from, const FVertex& to, const float t, FVertex& out);

//private:
    FPoint4D point;
    RGBA rgba ;
    TexCoord tex;
};

#endif //SIMPLERENDER_FVERTEX_HPP
