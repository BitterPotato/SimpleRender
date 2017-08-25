#ifndef TYPEDEF_HPP
#define TYPEDEF_HPP
typedef void(*f_keys) (int*);

template<typename T>
inline void swap(T* outA, T* outB) {
	T temp = *outA;
	*outA = *outB;
	*outB = temp;
}

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