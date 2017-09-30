//
// Created by WJ Yang on 2017/9/23.
//

#ifndef SIMPLERENDER_SHAPE_HPP
#define SIMPLERENDER_SHAPE_HPP

#include "common/setup.hpp"
#include "mesh/Container.hpp"

class FVertex;

namespace Mesh {
    class Shape {
    public:
        virtual void tessellate(FVertexContainer &outVertexData, IndexContainer& indexContainer) const = 0;
    };
}

#endif //SIMPLERENDER_SHAPE_HPP
