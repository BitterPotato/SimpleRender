#ifndef FRAGCACHE_HPP
#define FRAGCACHE_HPP

#include "Frag.hpp"
#include "../pipeline/frag_shader.hpp"

#include <vector>
#include <algorithm>
#include <iostream>

using std::vector;

#define Z_BUFFERTEST

class FragCache {
public:
	void addFrag(const Frag& frag);
	void runFrags(const FragShader& fragShader);
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
private:
	vector<Frag> mFragData;
	vector<vector<int>> mFragIndexes;

	int smallestY = 800, biggestY = 0;
	int smallestX = 800, biggestX = 0;
	bool havePrinted = false;
};
#endif
