//
// Created by WJ Yang on 2017/9/24.
//

#ifndef SIMPLERENDER_FRAGSHADER_HPP_HPP
#define SIMPLERENDER_FRAGSHADER_HPP_HPP

#include "platform/FrameBuffer.hpp"

class FragShader {
public:
    FragShader(FrameBuffer& framebuffer) : mFrameBuffer(framebuffer){}
    MY_COMP_FUNC_DECL virtual void shade(const Frag& frag) const = 0;

protected:
    FrameBuffer& mFrameBuffer;
};

#endif //SIMPLERENDER_FRAGSHADER_HPP_HPP
