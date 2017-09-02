// SimpleRenderTests.cpp : Defines the entry point for the console application.
//

#include "gtest/gtest.h"
#include "../SimpleRender/math/tvector_trans.hpp"
#include "../SimpleRender/math/tmatrix_trans.hpp"

#include <iostream>

using std::cin;
using math::dot;
using math::transpose;
using math::length;
using math::normalize;
using math::cross;
using math::det;
using math::translate;
using math::scale3T;
using math::asRotateMat;
using math::radians;
using math::degrees;

TEST(DotTests, Dot)
{
	int res = dot(ivec2(1, 0), ivec2(2, 2));
	EXPECT_EQ(2, res);
}

TEST(TransposeTests, Transpose)
{
	imat4 imat_a(ivec4(0, 0, 0, 0),
		ivec4(1, 1, 1, 1),
		ivec4(2, 2, 2, 2),
		ivec4(3, 3, 3, 3));
	imat4 imat_b(ivec4(0, 1, 2, 3),
		ivec4(0, 1, 2, 3),
		ivec4(0, 1, 2, 3),
		ivec4(0, 1, 2, 3));
	EXPECT_EQ(imat_a, transpose(imat_b));
}

TEST(MultiplyTests, Multiply)
{
	imat4 imat_a(ivec4(0, 0, 0, 0),
		ivec4(1, 1, 1, 1),
		ivec4(2, 2, 2, 2),
		ivec4(3, 3, 3, 3));
	imat4 imat_b(ivec4(0, 1, 2, 3),
		ivec4(0, 1, 2, 3),
		ivec4(0, 1, 2, 3),
		ivec4(0, 1, 2, 3));
	imat4 res(ivec4(0, 0, 0, 0),
		ivec4(0, 4, 8, 12),
		ivec4(0, 8, 16, 24),
		ivec4(0, 12, 24, 36));
	imat4 tres = imat_b*imat_a;
	EXPECT_EQ(res, tres);
}

TEST(LengthTests, Length) {
	ivec3 vec(3, 4, 0);
	int len = length(vec);
	EXPECT_EQ(5, len);
}

TEST(NormalizeTests, Normalize) {
	fvec3 vec(3, 4, 0);
	fvec3 vec_unit(0.6f, 0.8f, 0.0f);
	EXPECT_EQ(vec_unit, normalize(vec));
}

TEST(DetTests, Det) {
	ivec2 vec1(1, 2);
	ivec2 vec2(2, 3);
	EXPECT_EQ(-1, det(vec1, vec2));
}

TEST(CrossTests, Cross) {
	ivec3 vec1(1, 2, 3);
	ivec3 vec2(2, -1, -2);
	ivec3 res(-1, 8, -5);
	EXPECT_EQ(res, cross(vec1, vec2));
}

TEST(TranslateTests, Translate) {
	ivec3 trans(-1, -2, -3);
	imat4 trans_mat4 = translate(trans);

	ivec4 orig(3, 4, 5, 1);
	ivec4 res(2, 2, 2, 1);
	ivec4 tres = trans_mat4 * orig;
	EXPECT_EQ(res, tres);
}

TEST(ScaleTests, Scale) {
	ivec3 scal(2, 1, 3);
	imat3 scal_mat3 = scale3T(scal);

	ivec3 orig(1, 1, 1);
	ivec3 res(2, 1, 3);
	ivec3 tres = scal_mat3 * orig;
	EXPECT_EQ(res, tres);
}

TEST(DegreeTests, degree) {
	//float degreeA = 180;
	//float radiansA = 3.1415926f;
	//EXPECT_EQ(radiansA, radians(degreeA));

	float degreeB = 90;
	float radiansB = 3.1415926f / 2;
	EXPECT_EQ(degrees(radiansB), degreeB);
}
TEST(RotateTests, Rotate) {
	fvec3 axis(1, 2, 0);
	fmat3 rotate_mat3 = asRotateMat(axis, radians(180.0f));

	fvec3 orig(3, 1, 0);
	fvec3 res(-1, 3, 0);
	fvec3 tres = rotate_mat3*orig;
	EXPECT_EQ(res, tres);
}
