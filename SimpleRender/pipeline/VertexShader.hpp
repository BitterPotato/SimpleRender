//
// Created by WJ Yang on 2017/9/24.
//

#ifndef SIMPLERENDER_VERTEXSHADER_HPP
#define SIMPLERENDER_VERTEXSHADER_HPP

#include "common/FVertex.hpp"

class VertexShader {
public:
    MY_COMP_FUNC_DECL virtual void shade(const FVertex& input, FVertex& output) const = 0;
};

#endif //SIMPLERENDER_VERTEXSHADER_HPP
