// SimpleRenderTests.cpp : Defines the entry point for the console application.
//

#include "gtest/gtest.h"
#include "math/TVector_Trans.hpp"
#include "math/TMatrix_Trans.hpp"
#include "common/Frag.hpp"
#include "pipeline/BlendOptions.hpp"
#include "common/Info.hpp"

#include <iostream>
#include <string>
#include <common/FVertex.hpp>
#include <common/Vertex.hpp>

using std::cin;
using std::cout;
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
using math::eulerAsMatrix;
using math::asMat4;


class MathFixture : public ::testing::Test {};
class RenderFixture : public ::testing::Test {};

TEST_F(MathFixture, Dot)
{
	int res = dot(ivec2(1, 0), ivec2(2, 2));
	EXPECT_EQ(2, res);
}

TEST_F(MathFixture, Transpose)
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

TEST_F(MathFixture, Multiply)
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

TEST_F(MathFixture, Length) {
	ivec3 vec(3, 4, 0);
	int len = length(vec);
	EXPECT_EQ(5, len);
}

TEST_F(MathFixture, Normalize) {
	fvec3 vec(3, 4, 0);
	fvec3 vec_unit(0.6f, 0.8f, 0.0f);
	EXPECT_EQ(vec_unit, normalize(vec));
}

TEST_F(MathFixture, Det) {
	ivec2 vec1(1, 2);
	ivec2 vec2(2, 3);
	EXPECT_EQ(-1, det(vec1, vec2));
}

TEST_F(MathFixture, Cross) {
	ivec3 vec1(1, 2, 3);
	ivec3 vec2(2, -1, -2);
	ivec3 res(-1, 8, -5);
	EXPECT_EQ(res, cross(vec1, vec2));
}

TEST_F(MathFixture, Translate) {
	ivec3 trans(-1, -2, -3);
	imat4 trans_mat4 = translate(trans);

	ivec4 orig(3, 4, 5, 1);
	ivec4 res(2, 2, 2, 1);
	ivec4 tres = trans_mat4 * orig;
	EXPECT_EQ(res, tres);
}

TEST_F(MathFixture, Scale) {
	ivec3 scal(2, 1, 3);
	imat3 scal_mat3 = scale3T(scal);

	ivec3 orig(1, 1, 1);
	ivec3 res(2, 1, 3);
	ivec3 tres = scal_mat3 * orig;
	EXPECT_EQ(res, tres);
}

TEST_F(MathFixture, degree) {
	//float degreeA = 180;
	//float radiansA = 3.1415926f;
	//EXPECT_EQ(radiansA, radians(degreeA));

	float degreeB = 90;
	float radiansB = 3.1415926f / 2;
	EXPECT_EQ(degrees(radiansB), degreeB);
}
TEST_F(MathFixture, Rotate) {
	fvec3 axis(1, 2, 0);
	fmat3 rotate_mat3 = asRotateMat(axis, radians(180.0f));

	fvec3 orig(3, 1, 0);
	fvec3 res(-1, 3, 0);
	fvec3 tres = rotate_mat3*orig;

	// float error
	EXPECT_EQ(res, tres);
}
// not for test
TEST_F(MathFixture, Euler) {
	//int pitch = 10, yaw = 0, roll = 0;
	const string EULER_ORDER = "xyz";
	//fmat4 mat = asMat4(eulerAsMatrix(pitch, yaw, roll, EULER_ORDER));
	fmat4 mat = asMat4(eulerAsMatrix(10, 0, 0, EULER_ORDER));
	fmat4 emat = fmat4(1.0f);
	EXPECT_EQ(emat, mat);
}

TEST_F(RenderFixture, RET) {
	RGBA rgba(128, 128, 128, 0);
	EXPECT_EQ(rgba[R], 128);
}

TEST_F(RenderFixture, Point) {
	FPoint4D test = Macro_FPoint4D(1.0f, 0.0f, 0.0f);
	FPoint4D testTwo = Macro_FPoint4D(0.0f, 0.0f, 0.0f);

	EXPECT_EQ(test[3], testTwo[3]);
}

TEST_F(RenderFixture, FVertex) {
	FVertex test(Macro_FPoint4D(0.75f, 0.75f, 0.0f), RGBA(255, 128, 64));
	FVertex testTwo(Macro_FPoint4D(0.75f, 0.75f, 0.0f), RGBA(255, 128, 64));

	EXPECT_EQ(test.point[3], testTwo.point[3]);
}

TEST_F(RenderFixture, Vertex) {
	Vertex vertex;

	EXPECT_EQ(vertex.point[X], 0);
}

//TEST_F(RenderFixture, Ratio) {
//	RGBA rgba(255, 0, 0, 0);
//	float ratio = 0.5f;
//	RGBA tmpBGRA = rgba*ratio;
//
//	int wait;
//	cin >> wait;
//}
//TEST_F(RenderFixture, Eff) {
//	RGBA first(128, 128, 128, 128);
//	RGBA second(255, 128, 255, 64);
//
//	RGBA output;
//	BlendOptions options;
//	blend(options, first, second, output);
//}