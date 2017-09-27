#ifndef SIMPLE_DELEGATE_HPP
#define SIMPLE_DELEGATE_HPP

#include "common/setup.hpp"
#include "pipeline/RenderState.hpp"
// TODO: stl vector cannot get together with forward declaration also
#include "common/FVertex.hpp"
#include "pipeline/Pipeline.hpp"

class Form;
class FrameBuffer;
class Pipeline;

const float POSITION_STEP = 0.2f;
const float DEGREE_STEP = 2;

class SimpleDelegate {
public:
    SimpleDelegate(FrameBuffer &frameBuffer,
                   const int width, const int height) :
            mFrameBuffer(frameBuffer) {
        initRender(width, height);
    }

    ~SimpleDelegate() {
    }

    MY_COMP_FUNC_DECL void keysCallback(int *screen_keys);

    MY_COMP_FUNC_DECL void testRectangle(int width, int height, FrameBuffer &fb);

    MY_COMP_FUNC_DECL void testCircleAn(int width, int height, FrameBuffer &fb);

    MY_COMP_FUNC_DECL void testPoint();

    MY_COMP_FUNC_DECL void testLine();

    MY_COMP_FUNC_DECL void testTriangle();

    MY_COMP_FUNC_DECL void testTriangleStrip();

    MY_COMP_FUNC_DECL void testCube();

    MY_COMP_FUNC_DECL void testBlend();

private:
    // members
    FrameBuffer &mFrameBuffer;

    vector<FVertex> vertexData;
    RenderState mRenderState;
    unique_ptr<Pipeline> mPipeline;

    void initRender(const int width, const int height);

    void clearColor();
};

#endif