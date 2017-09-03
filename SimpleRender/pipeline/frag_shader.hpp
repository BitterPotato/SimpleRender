#ifndef FRAG_SHADER_HPP
#define FRAG_SHADER_HPP

#include "../platform/framebuffer.hpp"

class FragShader {
public:
	FragShader(FrameBuffer* framebuffer) {
		this->framebuffer = framebuffer;
	}
	virtual void shade(const Frag& frag) const = 0;

protected:
	FrameBuffer* framebuffer;
};

class MyFragShader : public FragShader {
	using FragShader::FragShader;
	void shade(const Frag& frag) const;
};

// frag shader fun pointer
//typedef void(FragShader::*FsPtr)(const Frag&) const;

#endif