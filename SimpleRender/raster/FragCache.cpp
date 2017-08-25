#include "FragCache.hpp"

void FragCache::addFrag(const Frag& frag) {
	mFragData.push_back(frag);
}
void FragCache::runFrags(fragShader fs) {
	//std::for_each(mFragData.begin(), mFragData.end(), fs);
	// access by reference to avoid copying
	for (const Frag& frag : mFragData) {
		fs(frag);
	}
}