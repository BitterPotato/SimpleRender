#include <material/FITexture.hpp>
#include "SimpleDelegate.hpp"

void SimpleDelegate::clearColor() {
    mFrameBuffer.clearColor({0, 0, 0});
}

void SimpleDelegate::keysCallback(int *screen_keys) {
    // =============== move camera positions ==================
    if (screen_keys[VK_UP]) {
        clearColor();
        mRenderState.triggerCameraCircleMove(UP_MOVE, POSITION_STEP);
        mPipeline->requestRender();
    }
    if (screen_keys[VK_DOWN]) {
        clearColor();
        mRenderState.triggerCameraCircleMove(DOWN_MOVE, POSITION_STEP);
        mPipeline->requestRender();
    }
    if (screen_keys[VK_LEFT]) {
        clearColor();
        mRenderState.triggerCameraCircleMove(LEFT_MOVE, POSITION_STEP);
        mPipeline->requestRender();
    }
    if (screen_keys[VK_RIGHT]) {
        clearColor();
        mRenderState.triggerCameraCircleMove(RIGHT_MOVE, POSITION_STEP);
        mPipeline->requestRender();
    }
    // first anticlockwise and then clockwise
    // pitch, yaw modifies cameraCenter, and roll modifies cameraUp(as for camera)
    // there first try rotate the object
    // ======== pitch ========
    if (screen_keys[VK_F1]) {
        clearColor();
        mRenderState.triggerCameraRotate(PITCH_ANTI, DEGREE_STEP);
        mPipeline->requestRender();
    }
    if (screen_keys[VK_F2]) {
        clearColor();
        mRenderState.triggerCameraRotate(PITCH, DEGREE_STEP);
        mPipeline->requestRender();
    }
    // ======== yaw ========
    if (screen_keys[VK_F3]) {
        clearColor();
        mRenderState.triggerCameraRotate(YAW_ANTI, DEGREE_STEP);
        mPipeline->requestRender();
    }
    if (screen_keys[VK_F4]) {
        clearColor();
        mRenderState.triggerCameraRotate(YAW, DEGREE_STEP);
        mPipeline->requestRender();
    }
    // ======== roll ========
    if (screen_keys[VK_F5]) {
        clearColor();
        mRenderState.triggerCameraRotate(ROLL_ANTI, DEGREE_STEP);
        mPipeline->requestRender();
    }
    if (screen_keys[VK_F6]) {
        clearColor();
        mRenderState.triggerCameraRotate(ROLL, DEGREE_STEP);
        mPipeline->requestRender();
    }

}

void SimpleDelegate::initRender(const int width, const int height) {
    mPipeline = unique_ptr<Pipeline>(new Pipeline(mRenderState));

    mRenderState.attachViewport(width, height);
    unique_ptr<VertexShader> myVertexShader(new MyVertexShader());
    unique_ptr<FragShader> myFragShader(new MyFragShader(mFrameBuffer));
    mRenderState.attachShader(myVertexShader, myFragShader);
}

void SimpleDelegate::testRectangle(int width, int height, FrameBuffer &fb) {
    RGBA rgba{255, 128, 64, 255};
    // test for a region
    int upLeftX = width / 5 * 2;
    int upLeftY = height / 5 * 2;
    for (int i = 0; i < width / 5; i++) {
        for (int j = 0; j < height / 5; j++) {
            fb.setBufferPixel(upLeftX + i, upLeftY + j, rgba);
        }
    }
}

// test the happening of jag
void SimpleDelegate::testCircleAn(int width, int height, FrameBuffer &fb) {
    RGBA rgba{255, 128, 64, 255};
    // test for a region
    int upLeftX = width / 5 * 2 - 1;
    int upLeftY = height / 5 * 2 - 1;
    for (int i = 0; i < width / 5 + 2; i++) {
        for (int j = 0; j < height / 5 + 2; j++) {
            int x = upLeftX + i;
            int y = upLeftY + j;
            if (std::pow(x - width / 2, 2) + std::pow(y - height / 2, 2) < std::pow(width / 10, 2)) {
                fb.setBufferPixel(x, y, rgba);
            }
        }
    }
}


void SimpleDelegate::testPoint() {
    RGBA rgbaB(255, 128, 64);

    vertexData.push_back(FVertex(Macro_FPoint4D(0.75f, 0.75f, 0.0f), RGBA(255, 128, 64)));

    mRenderState.attachVertexData(GL_POINTS, vertexData);
    mPipeline->requestRender();
}


void SimpleDelegate::testLine() {
    //RGBA rgbaB( 255, 255, 0 );
    //
    //vertexData.push_back({ infoB, -0.75f, -0.75f });

    //RGBA rgbaE( 0, 0, 255);
    //
    //vertexData.push_back({ infoE, 0.95f, 0.95f });
    // TODO: for precision problem, this may generate the points outsides the screen
    //vertexData.push_back({ infoE, 1.0f, 1.0f });
    vertexData.push_back(FVertex(Macro_FPoint4D(0.0f, -0.5f, -0.8f), RGBA(0, 0, 255)));
    vertexData.push_back(FVertex(Macro_FPoint4D(0.0f, 0.5f, 0.8f), RGBA(255, 255, 0)));

    // TODO: perspective matrix should be fixed
    //fmat4 front = frontviewMatrix(fvec3(-1.0f, -1.0f, 0.0f),
    //	fvec3(1.0f, 1.0f, -2.0f));
    //fmat4 persp1 = perspectiveMatrix(radians(45.0f), 1.0f, -0.1f, -3.0f);
    //fmat4 persp2 = perspectiveMatrix(radians(45.0f), 1.0f, 2.0f, -100.0f);
    //mPipeline->confProjection(persp2);
    mRenderState.attachVertexData(GL_LINES, vertexData);
    mPipeline->requestRender();
}

void SimpleDelegate::testTriangle() {
    // clip one vertex
    //vertexData.push_back({ infoA, -0.0f, -2.0f });
    //vertexData.push_back({ infoB, -0.75f, 0.5f });
    //vertexData.push_back({ infoC, 0.25f, -0.25f });
    // clip two vertexes
    //vertexData.push_back({ infoA, 0.0f, -0.75f });
    //vertexData.push_back({ infoB, -0.75f, 1.5f });
    //vertexData.push_back({ infoC, 0.25f, 1.5f });
    vertexData.push_back(FVertex(Macro_FPoint4D(0.0f, -0.75f, 0.0f), RGBA(255, 0, 0)));
    vertexData.push_back(FVertex(Macro_FPoint4D(-0.75f, 0.5f, 0.0f), RGBA(0, 255, 0)));
    vertexData.push_back(FVertex(Macro_FPoint4D(0.25f, -0.25f, 0.0f), RGBA(0, 0, 255)));

    mRenderState.attachVertexData(GL_TRIANGLES, vertexData);
    mPipeline->requestRender();
}

void SimpleDelegate::testTriangleStrip() {
    vertexData.push_back(FVertex(Macro_FPoint4D(0.0f, -0.75f, 0.0f), RGBA(255, 0, 0)));
    vertexData.push_back(FVertex(Macro_FPoint4D(-0.75f, 0.5f, 0.0f), RGBA(0, 255, 0)));
    vertexData.push_back(FVertex(Macro_FPoint4D(0.25f, -0.25f, 0.0f), RGBA(0, 0, 255)));
    vertexData.push_back(FVertex(Macro_FPoint4D(0.875f, -0.375f, 0.0f), RGBA(255, 255, 255)));

    mRenderState.mPattern = GL_WIREFRAME;
    mRenderState.attachVertexData(GL_TRIANGLES, vertexData);
    mPipeline->requestRender();
}

void SimpleDelegate::testCube() {
    Parser scfParser;
    scfParser.scfParse("media/cube.scj", vertexData);
    unique_ptr<Texture> texture(new FITexture("media/test.jpg"));
    mRenderState.triggerCameraCircleMove(UP_MOVE, 3 * POSITION_STEP);

    // TODO: change near plane seems don't have any effect
    //mPipeline->confProjection(perspectiveMatrix(radians(45.0f), 1.0f, 2.0f, -10.0f));
    mRenderState.mTexture.reset(texture.release());
    mRenderState.attachVertexData(GL_TRIANGLES, vertexData);
    mPipeline->requestRender();
}

// Attention: Render order is important
void SimpleDelegate::testBlend() {
    int alpha = 153;

    // back
    RGBA rgbaB(216, 179, 79);
    // front
    RGBA rgbaF(102, 137, 155, alpha);

    vertexData.push_back(FVertex(Macro_FPoint4D(-0.6f, 0.0f, 0.5f), rgbaB));
    vertexData.push_back(FVertex(Macro_FPoint4D(0.2f, -0.4f, 0.5f), rgbaB));
    vertexData.push_back(FVertex(Macro_FPoint4D(0.2f, 0.4f, 0.5f), rgbaB));

    vertexData.push_back(FVertex(Macro_FPoint4D(0.6f, 0.0f, -0.5f), rgbaF));
    vertexData.push_back(FVertex(Macro_FPoint4D(-0.2f, -0.4f, -0.5f), rgbaF));
    vertexData.push_back(FVertex(Macro_FPoint4D(-0.2f, 0.4f, -0.5f), rgbaF));

    mRenderState.attachVertexData(GL_TRIANGLES, vertexData);
    mPipeline->requestRender();
}