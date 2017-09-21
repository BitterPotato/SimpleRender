#ifndef TMATRIX_ROTATE_HPP
#define TMATRIX_ROTATE_HPP

//#define M_PI 3.1415926

#include "tmatrix.hpp"
#include "tvector_trans.hpp"

#include <cmath>
#include <exception>
#include <stdexcept>
#include <string>

using std::sin;
using std::cos;
using std::string;
using std::logic_error;

using math::normalize;
using math::transpose;
using math::length;

// ----------------- matrix ------------------
namespace math {
	// should be called by input type: float
	template <typename T>
	static inline T radians(const T angleInDegrees) {
		return angleInDegrees*static_cast<T>(M_PI / 180.0);
	}
	template <typename T>
	static inline T degrees(const T angleInRadians) {
		return angleInRadians*static_cast<T>(180.0 / M_PI);
	}
	static inline fmat3 asXRotateMat(const float radians) {
		fmat3 mat3(1.0f);
		float sinv = sin(radians);
		float cosv = cos(radians);

		mat3[1][1] = cosv;
		mat3[1][2] = sinv;
		mat3[2][1] = -sinv;
		mat3[2][2] = cosv;

		return mat3;
	}
	static inline fmat3 asYRotateMat(const float radians) {
		fmat3 mat3(1.0f);
		float sinv = sin(radians);
		float cosv = cos(radians);

		mat3[0][0] = cosv;
		mat3[0][2] = -sinv;
		mat3[2][0] = sinv;
		mat3[2][2] = cosv;

		return mat3;
	}
	static inline fmat3 asZRotateMat(const float radians) {
		fmat3 mat3(1.0f);
		float sinv = sin(radians);
		float cosv = cos(radians);

		mat3[0][0] = cosv;
		mat3[0][1] = sinv;
		mat3[1][0] = -sinv;
		mat3[1][1] = cosv;

		return mat3;
	}

	static inline fvec3 noncollinear(const fvec3& axis) {
		/** input should be normalized**/
		if (length(axis) > 1.0f) {
			throw logic_error("not an appropriate input parameter!\n");
		}

		if (axis[0] <= axis[1])
			if (axis[0] <= axis[2])
				return fvec3(1.0f, axis[1], axis[2]);
			else
				return fvec3(axis[0], axis[1], 1.0f);
		else
			if (axis[1] <= axis[2])
				return fvec3(axis[0], 1.0f, axis[2]);
			else
				return fvec3(axis[0], axis[1], 1.0f);
	}
	static inline fmat3 asRotateMat(const fvec3& axis, const float radians) {
		fvec3 axis_z = normalize(axis);
		fvec3 axis_ty = normalize(noncollinear(axis_z));
		fvec3 axis_x = normalize(cross(axis_ty, axis_z));
		// ������λ�����Ĳ����Ϊ��λ����
		fvec3 axis_y = cross(axis_z, axis_x);

		fmat3 axis_trans = fmat3(
			axis_x,
			axis_y,
			axis_z
		);
		fmat3 inver_axis_trans = transpose(axis_trans);

		return axis_trans * asZRotateMat(radians) * inver_axis_trans;
	}

	// ----------------- euler ------------------
	// radians version
	static fmat3 eulerAsMatrix(const float pitch, const float yaw, const float roll, const string& order) {
		if (order == "xyz") {
			return asXRotateMat(pitch)*asYRotateMat(yaw)*asZRotateMat(roll);
		}
		else if (order == "xzy") {
			return asXRotateMat(pitch)*asZRotateMat(roll)*asYRotateMat(yaw);
		}
		else if (order == "yzx") {
			return asYRotateMat(yaw)*asZRotateMat(roll)*asXRotateMat(pitch);
		}
		else if (order == "yxz") {
			return asYRotateMat(yaw)*asXRotateMat(pitch)*asZRotateMat(roll);
		}
		else if (order == "zxy") {
			return asZRotateMat(roll)*asXRotateMat(pitch)*asYRotateMat(yaw);
		}
		else if (order == "zyx") {
			return asZRotateMat(roll)*asYRotateMat(yaw)*asXRotateMat(pitch);
		}
		else {
			throw logic_error("not valid parameter");
		}
	}

	// degrees version
	static fmat3 eulerAsMatrix(const int pi, const int ya, const int ro, const string& order) {
		return eulerAsMatrix(radians(static_cast<float>(pi)), radians(static_cast<float>(ya)), radians(static_cast<float>(ro)), order);
	}

	// ----------------- quaternion ------------------

}

#endif