//
// Created by WJ Yang on 2017/9/29.
//

#ifndef SIMPLERENDER_CUBE_HPP
#define SIMPLERENDER_CUBE_HPP

#include "Shape.hpp"

class FVertex;

namespace Mesh {
    class Cube : public Shape{
    public:
        Cube(FVertex& p, float e) :
                left_bottom_back(p), edge(e){}
        MY_COMP_FUNC_DECL void tessellate(FVertexContainer &outVertexData, IndexContainer& indexContainer) const override;
    private:
        FVertex& left_bottom_back;
        float edge;
    };
}

#endif //SIMPLERENDER_CUBE_HPP
