#ifndef BASIC_INL
#define BASIC_INL

inline int ipart(float x) {
	return static_cast<int>(x);
}

inline float fpart(float x) {
	return x - static_cast<float>(ipart(x));
}

inline float rfpart(float x) {
	return 1.0f - fpart(x);
}

inline int mround(float x) {
	return ipart(x + 0.5f);
}

#endif