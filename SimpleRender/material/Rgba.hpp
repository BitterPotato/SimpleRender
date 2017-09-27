#ifndef COLOR_HPP
#define COLOR_HPP

#define LIMIT 255

#include "Hsv.hpp"
#include "common/setup.hpp"
#include "math/TVector.hpp"

const int R = 2;
const int G = 1;
const int B = 0;
const int A = 3;
const int CAPACITY = 4;

class RGBA : public TVectorN<int, 4> {
public:
	RGBA(int bb = 0, int gg = 0, int rr = 0, int aa = LIMIT) {
		data[R] = rr;
		data[G] = gg;
		data[B] = bb;
		data[A] = aa;
//		std::cout << "constructor";
	}

	~RGBA() {
//		std::cout << "deconstructor";
	}

	MY_OPERATOR_DECL int& operator[](int n) {
		return data[n];
	}
	MY_OPERATOR_DECL const int& operator[](int n) const {
		return data[n];
	}

	RGBA& operator*(const float ratio);
	RGBA& operator*=(const float ratio);

	// assert: move
	MY_SFRIEND_FUNC_DECL RGBA inter(const RGBA& from, const RGBA& to, const float t);
    MY_SFRIEND_FUNC_DECL RGBA inter(const RGBA& first, const RGBA& second, const RGBA& third, RGBA& outRGBA, const fvec3& ratio);
	MY_SFRIEND_FUNC_DECL RGBA operator*(const RGBA& bgra, const float ratio);
	MY_SMALL_UTIL_DECL float toFloat(int comp) {
		return static_cast<float>(comp) / LIMIT;
	}
	MY_NFRIEND_FUNC_DECL HSV toHSV(const RGBA& rgba);
//private:
//	int b; int g;  int r; int a;
};

#include "Rgba.inl"

#endif