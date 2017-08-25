#ifndef FRAGCACHE_HPP
#define FRAGCACHE_HPP

#include "Frag.hpp"

#include <vector>
#include <algorithm>

class FragCache {
public:
	void addFrag(const Frag& frag);
	void runFrags(fragShader fs);
private:
	std::vector<Frag> mFragData;
};
#endif
