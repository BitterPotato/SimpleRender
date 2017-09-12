#ifndef TVECTOR_HPP
#define TVECTOR_HPP

#include <iostream>
using std::cout;
using std::endl;

template <typename T, const int len>
class TVectorN {
public:
	TVectorN() {

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

template<typename T>
class TVector2 : public TVectorN<T, 2>{
public:
	typedef TVectorN<T, 2> base;
	TVector2(T x, T y) {
		base::data[0] = x;
		base::data[1] = y;
	}
	TVector2(const TVectorN<T, 2>& vec) : TVectorN<T, 2>(vec) {}
	//TVector2(T x, T y) {
	//	data[0] = x;
	//	data[1] = y;
	//}
};

template<typename T>
class TVector3 : public TVectorN<T, 3>{
public:
	typedef TVectorN<T, 3> base;
	TVector3() {}
	TVector3(T x, T y, T z) {
		base::data[0] = x;
		base::data[1] = y;
		base::data[2] = z;
	}
	TVector3(const TVectorN<T, 3>& vec) : TVectorN<T, 3>(vec) {}
};

template<typename T>
class TVector4 : public TVectorN<T, 4> {
public:
	typedef TVectorN<T, 4> base;
	TVector4(T x, T y, T z, T w) {
		base::data[0] = x;
		base::data[1] = y;
		base::data[2] = z;
		base::data[3] = w;
	}
	TVector4(const TVectorN<T, 4>& vec) : TVectorN<T, 4>(vec) {}
};

typedef TVector2<int> ivec2;
typedef TVector2<float> fvec2;
typedef TVector3<int> ivec3;
typedef TVector3<float> fvec3;
typedef TVector4<int> ivec4;
typedef TVector4<float> fvec4;

#endif