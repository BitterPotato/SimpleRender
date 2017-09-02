#ifndef TMATRIX_HPP
#define TMATRIX_HPP

#include "tvector_trans.hpp"

using math::dot;

template<typename T> class TMatrix3;
template<typename T> class TMatrix4;

template <typename T, const int w, const int h>
class TMatrixN {
public:
	typedef TVectorN<T, h> col_type;
	typedef TVectorN<T, w> row_type;
	TMatrixN() {

	}
	inline TMatrixN(const TMatrixN& matrixN) {
		assign(matrixN);
	}
	inline col_type& operator[](int n) {
		return data[n];
	}
	inline const col_type& operator[](int n) const {
		return data[n];
	}
	inline row_type row(int n) const {
		row_type result;
		for (int i = 0; i < w; i++) {
			result[i] = data[i][n];
		}
		return result;
	}
	inline bool operator==(const TMatrixN& matrixN) const {
		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
				if (data[i][j] != matrixN[i][j])
					return false;
		return true;
	}
protected:
	col_type data[w];
	inline void assign(const TMatrixN& matrixN) {
		for (int i = 0; i < w; i++)
			data[i] = matrixN[i];
	}
	inline void assign(const T val) {
		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
				data[i][j] = val;
	}
};

template <typename T, const int w, const int h>
inline TVectorN<T, w> operator*(const TMatrixN<T, w, h>& matrixN, const TVectorN<T, w>& vecN) {
	TVectorN<T, w> ret;
	for (int j = 0; j < h; j++) {
		ret[j] = dot(matrixN.row(j), vecN);
	}
	return ret;
}
template <typename T, const int w, const int h, const int l>
inline TMatrixN<T, h, l> operator*(const TMatrixN<T, w, h>& matrixThis, const TMatrixN<T, l, w>& matrixThat) {
	TMatrixN<T, h, l> result;
	for (int i = 0; i < l; i++)
		for (int j = 0; j < h; j++)
			result[i][j] = dot(matrixThis.row(j), matrixThat[i]);
	return result;
}

template<typename T>
class TMatrix3 : public TMatrixN<T, 3, 3>{
public:
	typedef TMatrixN<T, 3, 3> base;
	TMatrix3(T t) {
		base::assign(T(0));
		base::data[0][0] = t;
		base::data[1][1] = t;
		base::data[2][2] = t;
	}
	TMatrix3(const TMatrixN<T, 3, 3>& matrixN) : TMatrixN<T, 3, 3>(matrixN) {}
	TMatrix3(const TVector3<T>& vec1, const TVector3<T>& vec2, const TVector3<T>& vec3) {
		base::data[0] = vec1;
		base::data[1] = vec2;
		base::data[2] = vec3;
	}
	// column-first
	TMatrix3(T t00, T t01, T t02, T t10, T t11, T t12, T t20, T t21, T t22) {
		base::data[0][0] = t00;
		base::data[0][1] = t01;
		base::data[0][2] = t02;

		base::data[1][0] = t10;
		base::data[1][1] = t11;
		base::data[1][2] = t12;
		
		base::data[2][0] = t20;
		base::data[2][1] = t21;
		base::data[2][2] = t22;
	}
};

template<typename T>
class TMatrix4 : public TMatrixN<T, 4, 4> {
public:
	typedef TMatrixN<T, 4, 4> base;
	TMatrix4(T t) {
		base::assign(T(0));

		base::data[0][0] = t;
		base::data[1][1] = t;
		base::data[2][2] = t;
		base::data[3][3] = t;
	}
	// notice: https://stackoverflow.com/questions/22880493/no-suitable-user-defined-conversion
	TMatrix4(const TMatrixN<T, 4, 4>& matrixN) : TMatrixN<T, 4, 4>(matrixN) {}
	TMatrix4(const TVector4<T>& vec1, const TVector4<T>& vec2, const TVector4<T>& vec3, const TVector4<T>& vec4) {
		base::data[0] = vec1;
		base::data[1] = vec2;
		base::data[2] = vec3;
		base::data[3] = vec4;
	}
	// column-first
	TMatrix4(T t00, T t01, T t02, T t03, T t10, T t11, T t12, T t13, 
		T t20, T t21, T t22, T t23, T t30, T t31, T t32, T t33) {
		base::data[0][0] = t00;
		base::data[0][1] = t01;
		base::data[0][2] = t02;
		base::data[0][3] = t03;

		base::data[1][0] = t10;
		base::data[1][1] = t11;
		base::data[1][2] = t12;
		base::data[1][3] = t13;

		base::data[2][0] = t20;
		base::data[2][1] = t21;
		base::data[2][2] = t22;
		base::data[2][3] = t23;

		base::data[3][0] = t30;
		base::data[3][1] = t31;
		base::data[3][2] = t32;
		base::data[3][3] = t33;
	}
};

typedef TMatrix3<int> imat3;
typedef TMatrix3<float> fmat3;
typedef TMatrix4<int> imat4;
typedef TMatrix4<float> fmat4;

#endif
