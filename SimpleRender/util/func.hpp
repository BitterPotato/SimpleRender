#ifndef FUNC_INL
#define FUNC_INL

template<typename T>
inline void myswap(T* a, T* b) {
	T temp = *a;
	*a = *b;
	*b = temp;
}

#endif