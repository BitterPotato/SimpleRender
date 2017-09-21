#include "FragCache.hpp"

void FragCache::addFrag(Frag&& frag) {
	// do z-buffer test
#ifdef Z_BUFFERTEST

	int index = mFragIndexes[frag.y][frag.x];
	//try {
	if (index == -1) {
#ifdef Z_BUFFERWRITE
		mFragIndexes[frag.y][frag.x] = mFragData.size();
#endif
		mFragData.push_back(std::move(frag));
	} 
	else if(index != -1 && frag.info->depth < mFragData[index].info->depth) {
#ifdef Z_BUFFERWRITE
			mFragIndexes[frag.y][frag.x] = mFragData.size();
#endif
#ifdef BLEND
			mFragData.push_back(std::move(frag));
#endif
#ifndef BLEND
			mFragData.push_back(std::move(frag));
#endif
		}
	//}
	//catch (...) {

	//}
#endif
#ifndef Z_BUFFERTEST
	mFragData.push_back(frag);
	// mFragIndexes of no use
#endif

}
void FragCache::runFrags(const unique_ptr<FragShader>& fragShader) {
	//std::for_each(mFragData.begin(), mFragData.end(), fs);
	// access by reference to avoid copying
#ifdef Z_BUFFERTEST
	for (const auto indexVec : mFragIndexes) {
		for (const int index : indexVec) {
			if(index != -1)
				fragShader->shade(mFragData[index]);
		}
	}
#endif
#ifndef Z_BUFFERTEST
	for (const Frag& frag : mFragData) {
		fragShader.shade(frag);
	}
#endif
}