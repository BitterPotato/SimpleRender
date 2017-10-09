#include <mesh/Sphere.hpp>
#include "SimpleDelegate.hpp"

#include "material/FITexture.hpp"
#include "format/parser.hpp"
#include "platform/FrameBuffer.hpp"
#include "pipeline/MyFragShader.hpp"
#include "pipeline/MyVertexShader.hpp"
#include "mesh/Cube.hpp"

#include <ctime>

void SimpleDelegate::clearColor() {
    mFrameBuffer.clearColor({0, 0, 0});
}

void SimpleDelegate::keysCallback(int *screen_keys) {
    // first anticlockwise and then clockwise
    // pitch, yaw modifies cameraCenter, and roll modifies cameraUp(as for camera)
    // there first try rotate the object
    if (screen_keys[VK_UP]) {
        clearColor();
        mRenderState.triggerCameraRotate(PITCH_ANTI, DEGREE_STEP);
        mPipeline->requestRender();
    }
    if (screen_keys[VK_DOWN]) {
        clearColor();
        mRenderState.triggerCameraRotate(PITCH, DEGREE_STEP);
        mPipeline->requestRender();
    }
    if (screen_keys[VK_LEFT]) {
        clearColor();
        mRenderState.triggerCameraRotate(YAW_ANTI, DEGREE_STEP);
        mPipeline->requestRender();
    }
    if (screen_keys[VK_RIGHT]) {
        clearColor();
        mRenderState.triggerCameraRotate(YAW, DEGREE_STEP);
        mPipeline->requestRender();
    }

    // =============== move camera positions ==================
    // ======== front and back ========
    if (screen_keys[VK_F1]) {
        clearColor();
        mRenderState.triggerCameraCircleMove(FRONT_MOVE, POSITION_STEP);
        mPipeline->requestRender();
    }
    if (screen_keys[VK_F2]) {
        clearColor();
        mRenderState.triggerCameraCircleMove(BACK_MOVE, POSITION_STEP);
        mPipeline->requestRender();
    }
    // ======== left and right ========
    if (screen_keys[VK_F3]) {
        clearColor();
        mRenderState.triggerCameraCircleMove(LEFT_MOVE, POSITION_STEP);
        mPipeline->requestRender();
    }
    if (screen_keys[VK_F4]) {
        clearColor();
        mRenderState.triggerCameraCircleMove(RIGHT_MOVE, POSITION_STEP);
        mPipeline->requestRender();
    }
    // ======== up and down ========
    if (screen_keys[VK_F5]) {
        clearColor();
        mRenderState.triggerCameraCircleMove(UP_MOVE, POSITION_STEP);
        mPipeline->requestRender();
    }
    if (screen_keys[VK_F6]) {
        clearColor();
        mRenderState.triggerCameraCircleMove(DOWN_MOVE, POSITION_STEP);
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
    FVertexContainer vertexData = FVertexContainer();
    IndexContainer indexContainer = IndexContainer();

    vertexData.push_back(FVertex(Macro_FPoint4D(0.75f, 0.75f, 0.0f), RGBA(255, 128, 64)));
    Mesh::createIndexContainer(GL_POINTS, vertexData.size(), indexContainer);
    mRenderState.attachVertexData(GL_POINTS, vertexData, indexContainer);
    mPipeline->requestRender();
}


void SimpleDelegate::testLine() {
    FVertexContainer vertexData = FVertexContainer();
    IndexContainer indexContainer = IndexContainer();

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
    Mesh::createIndexContainer(GL_LINES, vertexData.size(), indexContainer);
    mRenderState.attachVertexData(GL_LINES, vertexData, indexContainer);
    mPipeline->requestRender();
}

void SimpleDelegate::testTriangle() {
    FVertexContainer vertexData = FVertexContainer();
    IndexContainer indexContainer = IndexContainer();

    // clip one vertex
    //vertexData.push_back({ infoA, -0.0f, -2.0f });
    //vertexData.push_back({ infoB, -0.75f, 0.5f });
    //vertexData.push_back({ infoC, 0.25f, -0.25f });
    // clip two vertexes
    //vertexData.push_back({ infoA, 0.0f, -0.75f });
    //vertexData.push_back({ infoB, -0.75f, 1.5f });
    //vertexData.push_back({ infoC, 0.25f, 1.5f });
    vertexData.push_back(FVertex(Macro_FPoint4D(0.0f, -0.75f, 0.0f), RGBA(255, 0, 0), TexCoord(0, 1)));
    vertexData.push_back(FVertex(Macro_FPoint4D(-0.75f, 0.5f, 0.0f), RGBA(0, 255, 0), TexCoord(1, 1)));
    vertexData.push_back(FVertex(Macro_FPoint4D(0.25f, -0.25f, 0.0f), RGBA(0, 0, 255), TexCoord(1, 1)));

    unique_ptr<Texture> texture(new FITexture("media/test.jpg"));
    mRenderState.mTexture.reset(texture.release());

    Mesh::createIndexContainer(GL_TRIANGLES, vertexData.size(), indexContainer);
    mRenderState.attachVertexData(GL_TRIANGLES, vertexData, indexContainer);
    mPipeline->requestRender();
}

void SimpleDelegate::testTriangleStrip() {
    FVertexContainer vertexData = FVertexContainer();
    IndexContainer indexContainer = IndexContainer();

    vertexData.push_back(FVertex(Macro_FPoint4D(0.0f, -0.75f, 0.0f), RGBA(255, 0, 0)));
    vertexData.push_back(FVertex(Macro_FPoint4D(-0.75f, 0.5f, 0.0f), RGBA(0, 255, 0)));
    vertexData.push_back(FVertex(Macro_FPoint4D(0.25f, -0.25f, 0.0f), RGBA(0, 0, 255)));
    vertexData.push_back(FVertex(Macro_FPoint4D(0.875f, -0.375f, 0.0f), RGBA(255, 255, 255)));

    mRenderState.mPattern = GL_WIREFRAME;
    Mesh::createIndexContainer(GL_TRIANGLES, vertexData.size(), indexContainer);
    mRenderState.attachVertexData(GL_TRIANGLES, vertexData, indexContainer);
    mPipeline->requestRender();
}

void SimpleDelegate::testCube() {
    FVertexContainer vertexData = FVertexContainer();
    IndexContainer indexContainer = IndexContainer();

    Parser scfParser;
    scfParser.scfParse("media/cube1.scj", vertexData);
    unique_ptr<Texture> texture(new FITexture("media/test.jpg"));
//    mRenderState.triggerCameraCircleMove(UP_MOVE, 3 * POSITION_STEP);

    mRenderState.mTexture.reset(texture.release());
    Mesh::createIndexContainer(GL_TRIANGLES, vertexData.size(), indexContainer);
    mRenderState.attachVertexData(GL_TRIANGLES, vertexData, indexContainer);
    mPipeline->requestRender();
}

void subGeneCube(FPoint4D left_bottom_back, float radius, FVertexContainer &outVertexData, IndexContainer& indexContainer) {
    FVertex fVertex(left_bottom_back, RGBA(128, 128, 128));
    Mesh::Cube cube(fVertex, radius);
    cube.tessellate(outVertexData, indexContainer);
}

float randomFloat(float from, float to) {
    float len = to - from;
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * len + from;
}
void randomGeneCube(FVertexContainer &outVertexData, IndexContainer& indexContainer) {
    srand (static_cast <unsigned> (time(0)));
    int cubeNum = 5;
    for(int i=0; i<cubeNum; i++) {
        subGeneCube(Macro_FPoint4D(randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f),
                    randomFloat(-1.0f, 1.0f)), randomFloat(0.0f, 0.4f), outVertexData, indexContainer);
    }
}

void SimpleDelegate::testGeneCube() {
    FVertexContainer vertexData;
    IndexContainer indexContainer;

    subGeneCube(Macro_FPoint4D(-0.2f, -0.2f, -0.2f), 0.4f, vertexData, indexContainer);
//    subGeneCube(Macro_FPoint4D(0.3f, 0.4f, -0.2f), 0.2f, vertexData, indexContainer);
//    randomGeneCube(vertexData, indexContainer);

//    Mesh::Sphere sphere(fVertex, 0.2f);
//    sphere.tessellate(vertexData, indexContainer);

    unique_ptr<Texture> texture(new FITexture("media/test.jpg"));
    mRenderState.mTexture.reset(texture.release());

    mRenderState.attachVertexData(GL_TRIANGLES, vertexData, indexContainer);
    mPipeline->requestRender();
}

// Attention: Render order is important
void SimpleDelegate::testBlend() {
    FVertexContainer vertexData = FVertexContainer();
    IndexContainer indexContainer = IndexContainer();

    int alpha = 153;

    // back
    RGBA rgbaB(79, 179, 216);
    // front
    RGBA rgbaF(155, 137, 102, alpha);

    vertexData.push_back(FVertex(Macro_FPoint4D(-0.6f, 0.0f, 0.5f), rgbaB));
    vertexData.push_back(FVertex(Macro_FPoint4D(0.2f, -0.4f, 0.5f), rgbaB));
    vertexData.push_back(FVertex(Macro_FPoint4D(0.2f, 0.4f, 0.5f), rgbaB));

    vertexData.push_back(FVertex(Macro_FPoint4D(0.6f, 0.0f, -0.5f), rgbaF));
    vertexData.push_back(FVertex(Macro_FPoint4D(-0.2f, -0.4f, -0.5f), rgbaF));
    vertexData.push_back(FVertex(Macro_FPoint4D(-0.2f, 0.4f, -0.5f), rgbaF));

    Mesh::createIndexContainer(GL_TRIANGLES, vertexData.size(), indexContainer);
    mRenderState.attachVertexData(GL_TRIANGLES, vertexData, indexContainer);
    mPipeline->requestRender();
}