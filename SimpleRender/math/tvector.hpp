#ifndef TVECTOR_HPP
#define TVECTOR_HPP

//#define NDEBUG 

#include <iostream>
#include <assert.h>
#include <cmath>

using std::cout;
using std::endl;
using std::sqrt;

template <typename T, const int len>
class TVectorN {
public:
	TVectorN() {
	}
	TVectorN(T x, T y) {
		assert(len == 2);
		data[0] = x;
		data[1] = y;
	}
	TVectorN(T x, T y, T z) {
		assert(len == 3);
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}
	TVectorN(T x, T y, T z, T w) {
		assert(len == 4);
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
	}
	inline TVectorN(const TVectorN& vecN) {
		assign(vecN);
	}
	inline TVectorN operator-(const TVectorN& vecN) const {
		TVectorN res;
		for (int i = 0; i < len; i++)
			res[i] = data[i] - vecN[i];
		return res;
	}
	inline TVectorN operator/(const T& ratio) const {
		TVectorN res;
		for (int i = 0; i < len; i++)
			res[i] = data[i] / ratio;
		return res;
	}
	// TODO: deep in the difference
	inline T& operator[](int n) {
		return data[n];
	}
	inline const T& operator[](int n) const {
		return data[n];
	}
	inline TVectorN& operator=(const TVectorN& vecN) {
		assign(vecN);
		return *this;
	}
	inline bool operator==(const TVectorN& vecN) const {
		for (int i = 0; i < len; i++) {
			if (data[i] != vecN[i])
				return false;
		}
		return true;
	}
	~TVectorN() {
		//cout << "TVector: dispose" << endl;
	}
protected:
	T data[len];
	inline void assign(const TVectorN& vecN)
	{
		for (int i = 0; i < len; i++)
			data[i] = vecN[i];
	}
//public:
//	TVectorN() {
//		data = new T[len];
//	}
//	inline T& operator[](int n) const {
//		return data[n];
//	}
//	~TVectorN() {
//		// many small io operations may waste plenty of time
//		//cout << "TVector: dispose" << endl;
//		if (data != nullptr)
//			delete(data);
//	}
//protected:
//	T* data;
};

using ivec2 = TVectorN<int, 2>;
using fvec2 = TVectorN<float, 2>;
using ivec3 = TVectorN<int, 3>;
using fvec3 = TVectorN<float, 3>;
using ivec4 = TVectorN<int, 4>;
using fvec4 = TVectorN<float, 4>;

template <typename T, const int len>
using VecN = TVectorN<T, len>;

#endif