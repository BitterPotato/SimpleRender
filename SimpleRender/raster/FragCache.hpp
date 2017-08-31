#ifndef FRAGCACHE_HPP
#define FRAGCACHE_HPP

#include "Frag.hpp"

#include <vector>
#include <algorithm>

class FragCache {
public:
	void addFrag(const Frag& frag);
	void runFrags(fragShader fs);
	FragCache() {

	}
	FragCache(const FragCache& fragCache) {
		this->mFragData = fragCache.mFragData;
		std::cout << "FragCache: copy\n";
	}
	~FragCache() {
		mFragData.clear();
		std::cout << "FragCache: dispose\n";
	}
private:
	std::vector<Frag> mFragData;
};
#endif
