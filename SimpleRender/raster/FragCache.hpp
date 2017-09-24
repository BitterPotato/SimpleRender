#ifndef FRAGCACHE_HPP
#define FRAGCACHE_HPP

#include "common/Frag.hpp"
#include "pipeline/MyFragShader.hpp"
#include "pipeline/BlendOptions.hpp"

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

    MY_COMP_FUNC_DECL void addFrag(Frag&& frag);
    MY_COMP_FUNC_DECL void runFrags(const unique_ptr<FragShader>& fragShader) const;
//    void pixelFrag(int x, int y, Frag& outFrag) const;
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
