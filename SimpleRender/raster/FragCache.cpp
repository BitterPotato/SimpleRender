#include "FragCache.hpp"

void FragCache::addFrag(const Frag& frag) {
	// do z-buffer test
#ifdef Z_BUFFERTEST
	smallestX = smallestX > frag.x ? frag.x : smallestX;
	smallestY = smallestY > frag.y ? frag.y : smallestY;
	biggestX = biggestX < frag.x ? frag.x : biggestX;
	biggestY = biggestY < frag.y ? frag.y : biggestY;

	int index = mFragIndexes[frag.y][frag.x];
	//try {
		if (index == -1 || (index != -1 &&
			frag.info->depth < mFragData[index].info->depth)) {
			mFragData.push_back(frag);
			mFragIndexes[frag.y][frag.x] = mFragData.size() - 1;
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
	if (!havePrinted) {
		std::cout << smallestX << smallestY << biggestX << biggestY << endl;
		havePrinted = true;
	}
		
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