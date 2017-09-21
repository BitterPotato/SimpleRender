#include "color.hpp"

#include <algorithm>

using std::max;
using std::min;

inline float toFloat(int comp) {
	return static_cast<float>(comp) / LIMIT;
}

HSV fromRGB(int r, int g, int b) {
	int maxV = max(r, max(g, b));
	int minV = min(r, min(g, b));

	int h;
	float s, v;

	int diffV = maxV - minV;
	if (diffV == 0)
		h = 0;
	else if (maxV == r) {
		if (g >= b)
			h = 60 * (g - b) / diffV;
		else
			h = 60 * (g - b) / diffV + 360;
	}
	else if (maxV == g)
		h = 60 * (b - r) / diffV + 120;
	else
		h = 60 * (r - g) / diffV + 240;

	if (maxV == 0)
		s = 0;
	else
		s = static_cast<float>(diffV) / maxV;
		
	v = toFloat(maxV);

	return HSV(h, s, v);
}