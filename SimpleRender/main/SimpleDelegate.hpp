#ifndef SIMPLE_DELEGATE_HPP
#define SIMPLE_DELEGATE_HPP

#include "../platform/uniform.hpp"
#include "../platform/framebuffer.hpp"
#include "../pipeline/stage_flow.hpp"

#include "../format/scf_parser.hpp"
#include "../third/FreeImagePlus.h"
#include "../pipeline/render_state.hpp"

#include <iostream>
#include <cmath>
#include <string>
#include <memory>

using gl::Pipeline;

using std::cout;
using std::cin;
using std::unique_ptr;

const float POSITION_STEP = 0.2f;
const float DEGREE_STEP = 2;

class SimpleDelegate {
public:
	SimpleDelegate(Uniform& uniform, FrameBuffer& frameBuffer,
	const int width, const int height) : 
		mUniform(uniform), mFrameBuffer(frameBuffer) {
		initRender(width, height);
	}
	~SimpleDelegate() {
	}
	void keysCallback(int* screen_keys);
	void testRectangle(int width, int height, FrameBuffer& fb);
	void testCircleAn(int width, int height, FrameBuffer& fb);

	void testPoint();
	void testLine();
	void testTriangle();
	void testTriangleStrip();
	void testCube();

private:
	// members
	Uniform& mUniform;
	FrameBuffer& mFrameBuffer;

	vector<FVertex> vertexData;
	RenderState mRenderState;
	unique_ptr<Pipeline> mPipeline;

	void initRender(const int width, const int height);
	void clearColor();
};

#endif