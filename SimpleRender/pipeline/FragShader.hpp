//
// Created by WJ Yang on 2017/9/24.
//

#ifndef SIMPLERENDER_FRAGSHADER_HPP_HPP
#define SIMPLERENDER_FRAGSHADER_HPP_HPP

#include "common/setup.hpp"

class Frag;

class FragShader {
public:
    MY_COMP_FUNC_DECL virtual void shade(const Frag& frag) const = 0;
};

#endif //SIMPLERENDER_FRAGSHADER_HPP_HPP
