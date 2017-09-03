#include "FragCache.hpp"

void FragCache::addFrag(const Frag& frag) {
	mFragData.push_back(frag);
}
void FragCache::runFrags(const FragShader& fragShader) {
	//std::for_each(mFragData.begin(), mFragData.end(), fs);
	// access by reference to avoid copying
	for (const Frag& frag : mFragData) {
		fragShader.shade(frag);
	}
}