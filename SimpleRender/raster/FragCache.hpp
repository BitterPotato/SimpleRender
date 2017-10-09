#ifndef FRAGCACHE_HPP
#define FRAGCACHE_HPP

#include "common/setup.hpp"

#include "pipeline/BlendOptions.hpp"

class Frag;
class FragShader;

//#define Z_BUFFERTEST
//#define Z_BUFFERWRITE
// TODO: complex reason, clip when use perspective have some problems
#define BUFFER_PROTECT
//#define BLEND

class FragCache {
public:
	FragCache(int w, int h) : width(w), height(h) {
		mFragIndexes = vector<vector<int>>(h, vector<int>(w, -1));
	}
	//FragCache(const FragCache& fragCache) {
	//	this->mFragData = fragCache.mFragData;
	//	std::cout << "FragCache: copy\n";
	//}
	FragCache(const FragCache& fragCache) = delete;

	~FragCache() {
		mFragData.clear();
		mFragIndexes.clear();
//		std::cout << "FragCache: dispose\n";
	}

    MY_COMP_FUNC_DECL void addFrag(const Frag& frag);
    MY_COMP_FUNC_DECL void runFrags(const unique_ptr<FragShader>& fragShader) const;
//    void pixelFrag(int x, int y, Frag& outFrag) const;
private:
	int width, height;
	vector<Frag> mFragData;
	vector<vector<int>> mFragIndexes;

#ifdef BLEND
    // TODO: modified by RenderState

// normal
  BlendOptions mBlendOption;

//  soft additive
//	BlendOptions mBlendOption = BlendOptions(OneMinusDstColor, One);

// Multiply
//	BlendOptions mBlendOption = BlendOptions(DstColor, Zero);
// 2x Multiply
//	BlendOptions mBlendOption = BlendOptions(DstColor, SrcColor);
// Darken
//	BlendOptions mBlendOption = BlendOptions(One, One, Min);
// Lighten
//	BlendOptions mBlendOption = BlendOptions(One, One, Max);
// Screen
//	BlendOptions mBlendOption = BlendOptions(OneMinusDstColor, One, Max);
//	BlendOptions mBlendOption = BlendOptions(One, OneMinusSrcColor, Max);
// Linear Dodge
//	BlendOptions mBlendOption = BlendOptions(One, One);


#endif
};
#endif
