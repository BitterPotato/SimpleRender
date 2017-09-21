#ifndef FRAGCACHE_HPP
#define FRAGCACHE_HPP

#include "Frag.hpp"
#include "../pipeline/frag_shader.hpp"

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
	void addFrag(Frag&& frag);
	void runFrags(const unique_ptr<FragShader>& fragShader);
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
};
#endif
