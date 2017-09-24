#ifndef FRAG_SHADER_HPP
#define FRAG_SHADER_HPP

#include "FragShader.hpp"

class MyFragShader : public FragShader {
	using FragShader::FragShader;
	MY_COMP_FUNC_DECL void shade(const Frag& frag) const override ;
};

// frag shader fun pointer
//typedef void(FragShader::*FsPtr)(const Frag&) const;

#endif