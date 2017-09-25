#ifndef SIMPLE_DELEGATE_HPP
#define SIMPLE_DELEGATE_HPP

#include "platform/Form.hpp"
#include "platform/FrameBuffer.hpp"
#include "pipeline/Pipeline.hpp"
#include "pipeline/RenderState.hpp"
#include "format/parser.hpp"

#include <tchar.h>


const float POSITION_STEP = 0.2f;
const float DEGREE_STEP = 2;

class SimpleDelegate {
public:
    SimpleDelegate(shared_ptr<Form> uniform, FrameBuffer &frameBuffer,
                   const int width, const int height) :
            mUniform(uniform), mFrameBuffer(frameBuffer) {
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
    shared_ptr<Form> mUniform;
    FrameBuffer &mFrameBuffer;

    vector<FVertex> vertexData;
    RenderState mRenderState;
    unique_ptr<Pipeline> mPipeline;

    void initRender(const int width, const int height);

    void clearColor();
};

#endif