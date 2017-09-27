#ifndef FRAG_SHADER_HPP
#define FRAG_SHADER_HPP

#include "FragShader.hpp"

class FrameBuffer;

class MyFragShader : public FragShader {
public:
	MyFragShader(FrameBuffer& framebuffer) : mFrameBuffer(framebuffer){}
	MY_COMP_FUNC_DECL void shade(const Frag& frag) const override ;
private:
	FrameBuffer& mFrameBuffer;
};

// frag shader fun pointer
//typedef void(FragShader::*FsPtr)(const Frag&) const;

#endif