//
// Created by WJ Yang on 2017/9/23.
//

#ifndef SIMPLERENDER_SHAPE_HPP
#define SIMPLERENDER_SHAPE_HPP

#include "common/setup.hpp"

class FVertex;

namespace Mesh {
    class Shape {
    public:
        virtual void tessellate(vector<FVertex> &outVertexData) const = 0;
    };
}

#endif //SIMPLERENDER_SHAPE_HPP
