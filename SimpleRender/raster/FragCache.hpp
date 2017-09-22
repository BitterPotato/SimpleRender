#ifndef FRAGCACHE_HPP
#define FRAGCACHE_HPP

#include "Frag.hpp"
#include "../pipeline/frag_shader.hpp"
#include "pipeline/blend.hpp"

#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

using std::vector;
using std::unique_ptr;

#define Z_BUFFERTEST
#define Z_BUFFERWRITE
#define BLEND

class FragCache {
public:
	FragCache(int width, int height) {
		mFragIndexes = vector<vector<int>>(height, vector<int>(width, -1));
	}
	//FragCache(const FragCache& fragCache) {
	//	this->mFragData = fragCache.mFragData;
	//	std::cout << "FragCache: copy\n";
	//}
	FragCache(const FragCache& fragCache) = delete;

	~FragCache() {
		mFragData.clear();
		mFragIndexes.clear();
		std::cout << "FragCache: dispose\n";
	}

    void addFrag(Frag&& frag);
    void runFrags(const unique_ptr<FragShader>& fragShader) const;
    void pixelFrag(int x, int y, Frag& outFrag) const;
private:
	vector<Frag> mFragData;
	vector<vector<int>> mFragIndexes;

#ifdef BLEND
    // TODO: modified by RenderState

// normal
//  BlendOptions mBlendOption;

//  soft additive
	BlendOptions mBlendOption = BlendOptions(OneMinusDstColor, One);

// Multiply
//	BlendOptions mBlendOption = BlendOptions(DstColor, Zero);
// 2x Multiply
//	BlendOptions mBlendOption = BlendOptions(DstColor, SrcColor);
// Darken
//	BlendOptions mBlendOption = BlendOptions(Min, One, One);
// Lighten
//	BlendOptions mBlendOption = BlendOptions(Max, One, One);
// Screen
//	BlendOptions mBlendOption = BlendOptions(Max, OneMinusDstColor, One);
//	BlendOptions mBlendOption = BlendOptions(Max, One, OneMinusSrcColor);
// Linear Dodge
//	BlendOptions mBlendOption = BlendOptions(One, One);


#endif
};
#endif
