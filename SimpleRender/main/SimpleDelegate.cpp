#include "SimpleDelegate.hpp"
void SimpleDelegate::clearColor() {
	mFrameBuffer.clearColor({ 0, 0, 0 });
}

void SimpleDelegate::keysCallback(int* screen_keys) {
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
	mPipeline = new Pipeline(mRenderState);

	mRenderState.attachViewport(width, height);
	unique_ptr<VertexShader> myVertexShader(new MyVertexShader());
	unique_ptr<FragShader> myFragShader(new MyFragShader(mFrameBuffer));
	mRenderState.attachShader(myVertexShader, myFragShader);
}

void SimpleDelegate::testRectangle(int width, int height, FrameBuffer& fb) {
	BGRA bgra{ 255, 128, 64, 255 };
	// test for a region
	int upLeftX = width / 5 * 2;
	int upLeftY = height / 5 * 2;
	for (int i = 0; i < width / 5; i++) {
		for (int j = 0; j < height / 5; j++) {
			fb.setBufferPixel(upLeftX + i, upLeftY + j, bgra);
		}
	}
}

// test the happening of jag
void SimpleDelegate::testCircleAn(int width, int height, FrameBuffer& fb) {
	BGRA bgra{ 255, 128, 64, 255 };
	// test for a region
	int upLeftX = width / 5 * 2 - 1;
	int upLeftY = height / 5 * 2 - 1;
	for (int i = 0; i < width / 5 + 2; i++) {
		for (int j = 0; j < height / 5 + 2; j++) {
			int x = upLeftX + i;
			int y = upLeftY + j;
			if (std::pow(x - width / 2, 2) + std::pow(y - height / 2, 2) < std::pow(width / 10, 2)) {
				fb.setBufferPixel(x, y, bgra);
			}
		}
	}
}


void SimpleDelegate::testPoint() {
	BGRA* bgraB = new BGRA(255, 128, 64);
	Info* infoB = new Info(bgraB);
	vertexData.push_back({ infoB, 0.75f, 0.75f });

	mRenderState.attachVertexData(GL_POINTS, vertexData);
	mPipeline->requestRender();
}


void SimpleDelegate::testLine() {
	//BGRA* bgraB = new BGRA( 255, 255, 0 );
	//Info* infoB = new Info( bgraB );
	//vertexData.push_back({ infoB, -0.75f, -0.75f });

	//BGRA* bgraE = new BGRA( 0, 0, 255);
	//Info* infoE = new Info( bgraE );
	//vertexData.push_back({ infoE, 0.95f, 0.95f });
	// TODO: for precision problem, this may generate the points outsides the screen
	//vertexData.push_back({ infoE, 1.0f, 1.0f });

	BGRA* bgraC = new BGRA(0, 0, 255);
	Info* infoC = new Info(bgraC);
	vertexData.push_back(FVertex(infoC, 0.0f, -0.5f, -1.0f));

	BGRA* bgraF = new BGRA(255, 255, 0);
	Info* infoF = new Info(bgraF);
	vertexData.push_back(FVertex(infoF, 0.0f, 0.5f, 1.0f));

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
	BGRA* bgraA = new BGRA(255, 0, 0);
	Info* infoA = new Info(bgraA);

	BGRA* bgraB = new BGRA(0, 255, 0);
	Info* infoB = new Info(bgraB);

	BGRA* bgraC = new BGRA(0, 0, 255);
	Info* infoC = new Info(bgraC);

	// clip one vertex
	//vertexData.push_back({ infoA, -0.0f, -2.0f });
	//vertexData.push_back({ infoB, -0.75f, 0.5f });
	//vertexData.push_back({ infoC, 0.25f, -0.25f });
	// clip two vertexes
	//vertexData.push_back({ infoA, 0.0f, -0.75f });
	//vertexData.push_back({ infoB, -0.75f, 1.5f });
	//vertexData.push_back({ infoC, 0.25f, 1.5f });

	vertexData.push_back({ infoA, 0.0f, -0.75f });
	vertexData.push_back({ infoB, -0.75f, 0.5f });
	vertexData.push_back({ infoC, 0.25f, -0.25f });

	mRenderState.attachVertexData(GL_TRIANGLES, vertexData);
	mPipeline->requestRender();
}

void SimpleDelegate::testTriangleStrip() {
	BGRA* bgraA = new BGRA(255, 0, 0);
	Info* infoA = new Info(bgraA);
	vertexData.push_back({ infoA, 0.0f, -0.75f });

	BGRA* bgraB = new BGRA(0, 255, 0);
	Info* infoB = new Info(bgraB);
	vertexData.push_back({ infoB, -0.75f, 0.5f });

	BGRA* bgraC = new BGRA(0, 0, 255);
	Info* infoC = new Info(bgraC);
	vertexData.push_back({ infoC, 0.25f, -0.25f });

	BGRA* bgraD = new BGRA(255, 255, 255);
	Info* infoD = new Info(bgraD);
	vertexData.push_back({ infoD, 0.875f, -0.375f });

	mRenderState.mPattern = GL_WIREFRAME;
	mRenderState.attachVertexData(GL_TRIANGLES, vertexData);
	mPipeline->requestRender();
}

void SimpleDelegate::testCube() {
	scfParse("media/cube.scj", vertexData);
	unique_ptr<Texture> texture(new FITexture("media/test.jpg"));
	mRenderState.triggerCameraCircleMove(UP_MOVE, 3 * POSITION_STEP);

	// TODO: change near plane seems don't have any effect
	//mPipeline->confProjection(perspectiveMatrix(radians(45.0f), 1.0f, 2.0f, -10.0f));
	mRenderState.mTexture.reset(texture.release());
	mRenderState.attachVertexData(GL_TRIANGLES, vertexData);
	mPipeline->requestRender();
}