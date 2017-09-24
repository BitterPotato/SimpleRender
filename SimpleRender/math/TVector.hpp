#ifndef TVECTOR_HPP
#define TVECTOR_HPP

//#define NDEBUG 

#include <common/setup.hpp>


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
    MY_NFRIEND_FUNC_DECL TVectorN inter(const TVectorN &from, const TVectorN &to, const float t) {
        TVectorN ret;
        for(int i=0; i < len; i++) {
            ret.data[i] = (1-t)*from.data[i] + t*to.data[i];
        }
        return ret;
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