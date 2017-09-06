// SimpleRender.cpp : Defines the entry point for the console application.
//

#include "../util/type_def.hpp"
#include "../platform/uniform.hpp"
#include "../platform/framebuffer.hpp"
#include "../raster/Point.hpp"
#include "../raster/Line.hpp"
#include "../raster/Triangle.hpp"
#include "../pipeline/stage_flow.hpp"
#include "../pipeline/vertex_shader.hpp"
#include "../pipeline/frag_shader.hpp"
#include "../format/scf_parser.hpp"
#include "../math/tvector_trans.hpp"
#include "../math/tmatrix_trans.hpp"
#include "../third/FreeImagePlus.h"

#include <iostream>
#include <cmath>
#include <string>

using gl::Pipeline;
using math::perspectiveMatrix;
using math::lookatMatrix;
using math::eulerAsMatrix;
using math::asMat4;
using math::radians;

using std::cout;
using std::cin;

#define WIDTH 800
#define HEIGHT 800
#define POSITION_STEP 0.2f
#define DEGREE_STEP 2

const string EULER_ORDER = "xyz";

//=====================================================================
// Ö÷³ÌÐò
//=====================================================================

FrameBuffer mFramebuffer;
BGRA bgra{ 255, 128, 64, 255 };

Pipeline mPipeline;
vector<FVertex> vertexData;
MyVertexShader myVertexShader;
MyFragShader myFragShader(&mFramebuffer);

// default camera
fvec3 cameraPosition(0.0f, 0.0f, 1.0f);
fvec3 cameraCenter(0.0f, 0.0f, 0.0f);
fvec3 cameraUp(0.0f, 1.0f, 0.0f);
int pitch = 0, yaw = 0, roll = 0;

void refreshFrame() {
	mPipeline.confCamera(lookatMatrix(cameraPosition, cameraCenter, cameraUp));
	mPipeline.confTransform(asMat4(eulerAsMatrix(pitch, yaw, roll, EULER_ORDER)));
	mPipeline.useProgram(vertexData, myVertexShader, myFragShader);
}
void keysCallback(int* screen_keys) {
	// =============== move camera positions ==================
	if (screen_keys[VK_UP]) {
		//cout << "up keys have been clicked\n";
		mFramebuffer.clearColor({0, 0, 0});

		cameraPosition[1] += POSITION_STEP;
		//cameraCenter[1] += POSITION_STEP;

		refreshFrame();
	}
	if (screen_keys[VK_DOWN]) {
		mFramebuffer.clearColor({ 0, 0, 0 });
		
		cameraPosition[1] -= POSITION_STEP;
		//cameraCenter[1] -= POSITION_STEP;
		
		refreshFrame();
	}
	if (screen_keys[VK_LEFT]) {
		mFramebuffer.clearColor({ 0, 0, 0 });

		cameraPosition[0] -= POSITION_STEP;
		cameraCenter[0] -= POSITION_STEP;

		refreshFrame();
	}
	if (screen_keys[VK_RIGHT]) {
		mFramebuffer.clearColor({ 0, 0, 0 });

		cameraPosition[0] += POSITION_STEP;
		cameraCenter[0] += POSITION_STEP;

		refreshFrame();
	}
	// first anticlockwise and then clockwise
	// pitch, yaw modifies cameraCenter, and roll modifies cameraUp(as for camera)
	// there first try rotate the object
	// ======== pitch ========
	if (screen_keys[VK_F1]) {
		mFramebuffer.clearColor({ 0, 0, 0 });

		pitch += DEGREE_STEP;

		refreshFrame();
	}
	if (screen_keys[VK_F2]) {
		mFramebuffer.clearColor({ 0, 0, 0 });

		pitch -= DEGREE_STEP;

		refreshFrame();
	}
	// ======== yaw ========
	if (screen_keys[VK_F3]) {
		mFramebuffer.clearColor({ 0, 0, 0 });

		yaw += DEGREE_STEP;

		refreshFrame();
	}
	if (screen_keys[VK_F4]) {
		mFramebuffer.clearColor({ 0, 0, 0 });

		yaw -= DEGREE_STEP;

		refreshFrame();
	}
	// ======== roll ========
	if (screen_keys[VK_F5]) {
		mFramebuffer.clearColor({ 0, 0, 0 });

		roll += DEGREE_STEP;

		refreshFrame();
	}
	if (screen_keys[VK_F6]) {
		mFramebuffer.clearColor({ 0, 0, 0 });

		roll -= DEGREE_STEP;

		refreshFrame();
	}

}

void testRectangle(int width, int height, FrameBuffer& fb) {
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
void testCircleAn(int width, int height, FrameBuffer& fb) {
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

// function plays the role of fragment shader
//void fsImpl(const Frag& frag) {
//	//if (frag.x < 400) {
//		mFramebuffer.setBufferPixel(frag.x, frag.y, *frag.info.bgra);
//	//}
//}

// ========== rasterization =============
//inline void testRasterPoint() {
//	BGRA bgra{ 255, 128, 64, 255 };
//	Info info{ &bgra };
//
//	Vertex vertex{ info, 760, 760 };
//	rasterPoint(vertex, 40).runFrags(*fsImpl);
//}

inline void testPoint() {
	BGRA* bgraB = new BGRA(255, 128, 64);
	Info* infoB = new Info(bgraB);
	vertexData.push_back({ infoB, 0.75f, 0.75f });

	mPipeline.confViewport(WIDTH, HEIGHT);
	mPipeline.confMode(GL_POINTS);
	mPipeline.useProgram(vertexData, myVertexShader, myFragShader);
}

//inline void testRasterLine() {
//	//BGRA bgra{ 255, 128, 64, 255 };
//	//Info info{ bgra, 0, 0 };
//	BGRA bgraB{ 255, 255, 0, 255 };
//	Info infoB{ &bgraB };
//	BGRA bgraE{ 0, 0, 255, 255 };
//	Info infoE{ &bgraE };
//
//	//Vertex vertexBegin{ 100, 100, info };
//	//Vertex vertexEnd{ 100, 150, info };
//	//Vertex vertexBegin{ 100, 100, info };
//	//Vertex vertexEnd{ 150, 100, info };
//	//Vertex vertexBegin{ 100, 100, info };
//	//Vertex vertexEnd{ 150, 150, info };
//
//	//Vertex vertexBegin{ 100, 100, info };
//	//Vertex vertexEnd{ 300, 150, info };
//	//Vertex vertexBegin{ 100, 150, info };
//	//Vertex vertexEnd{ 300, 100, info };
//	//Vertex vertexBegin{ 100, 100, info };
//	//Vertex vertexEnd{ 200, 300, info };
//	Vertex vertexBegin{ infoB, 100, 100 };
//	Vertex vertexEnd{ infoE, 800, 800 };
//
//	FragCache fragCache;
//	rasterLine(vertexBegin, vertexEnd, 1, fragCache);
//	fragCache.runFrags(*fsImpl);
//}

inline void testLine() {
	BGRA* bgraB = new BGRA( 255, 255, 0 );
	Info* infoB = new Info( bgraB );
	vertexData.push_back({ infoB, -0.75f, -0.75f });

	BGRA* bgraE = new BGRA( 0, 0, 255);
	Info* infoE = new Info( bgraE );
	vertexData.push_back({ infoE, 1.0f, 1.0f });

	mPipeline.confViewport(WIDTH, HEIGHT);
	mPipeline.confMode(GL_LINES);
	mPipeline.useProgram(vertexData, myVertexShader, myFragShader);
}

//inline void testRasterTriangle() {
//	BGRA bgraA{255, 0, 0};
//	Info infoA{ &bgraA };
//	Vertex vertexA{ infoA, 400, 100 };
//
//	BGRA bgraB{ 0, 255, 0 };
//	Info infoB{ &bgraB };
//	Vertex vertexB{ infoB, 100, 600 };
//
//	BGRA bgraC{ 0, 0, 255 };
//	Info infoC{ &bgraC };
//	Vertex vertexC{ infoC, 500, 300 };
//
//	BGRA bgraD{ 255, 255, 255 };
//	Info infoD{ &bgraD };
//	Vertex vertexD{ infoD, 750, 250 };
//
//	FragCache fragCache;
//	rasterTriangle(vertexA, vertexB, vertexC, fragCache);
//	fragCache.runFrags(*fsImpl);
//	//rasterTriangle(vertexA, vertexC, vertexD).runFrags(*fsImpl);
//	//rasterTriangle(vertexB, vertexC, vertexD).runFrags(*fsImpl);
//
//	//rasterTriangle({ 400, 99, infoA }, { 100, 599, infoB }, { 499, 299, infoC }).runFrags(*fsImpl);
//	//rasterTriangle(vertexA, { 500, 299, infoC }, { 750, 249, infoD }).runFrags(*fsImpl);
//	//rasterTriangle(vertexB, vertexC, vertexD).runFrags(*fsImpl);
//}

inline void testTriangle() {
	BGRA* bgraA = new BGRA( 255, 0, 0 );
	Info* infoA = new Info ( bgraA );
	vertexData.push_back({ infoA, 0.0f, -0.75f });

	BGRA* bgraB = new BGRA( 0, 255, 0 );
	Info* infoB = new Info(bgraB);
	vertexData.push_back({ infoB, -0.75f, 0.5f });

	BGRA* bgraC = new BGRA( 0, 0, 255 );
	Info* infoC = new Info( bgraC );
	vertexData.push_back({ infoC, 0.25f, -0.25f });
	
	mPipeline.confViewport(WIDTH, HEIGHT);
	mPipeline.confMode(GL_TRIANGLES);
	mPipeline.useProgram(vertexData, myVertexShader, myFragShader);
}

inline void testTriangleStrip() {
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

	mPipeline.confViewport(WIDTH, HEIGHT);
	mPipeline.confMode(GL_TRIANGLES_STRIP);
	mPipeline.confPattern(GL_WIREFRAME);
	mPipeline.useProgram(vertexData, myVertexShader, myFragShader);
}

void testCube() {
	//float const edgeLen = 0.2f;
	//int const mature = 128;

	//// TODO: save structure as a file, and impl the parser module
	//BGRA* bgraA = new BGRA(mature, mature, 0);
	//Info* infoA = new Info(bgraA);
	//FVertex vertexA = { infoA, -edgeLen, -edgeLen, -edgeLen };

	//BGRA* bgraB = new BGRA(0, mature, mature);
	//Info* infoB = new Info(bgraB);
	//FVertex vertexB = { infoB, edgeLen, -edgeLen, -edgeLen };

	//BGRA* bgraC = new BGRA(mature, 0, mature);
	//Info* infoC = new Info(bgraC);
	//FVertex vertexC = { infoC, -edgeLen, edgeLen, -edgeLen };

	//BGRA* bgraD = new BGRA(mature, 0, 0);
	//Info* infoD = new Info(bgraD);
	//FVertex vertexD = { infoD, -edgeLen, -edgeLen, edgeLen };

	//BGRA* bgraE = new BGRA(0, mature, 0);
	//Info* infoE = new Info(bgraE);
	//FVertex vertexE = { infoE, -edgeLen, edgeLen, edgeLen };

	//BGRA* bgraF = new BGRA(0, 0, mature);
	//Info* infoF = new Info(bgraF);
	//FVertex vertexF = { infoF, edgeLen, -edgeLen, edgeLen };

	//BGRA* bgraG = new BGRA(0, 0, 0);
	//Info* infoG = new Info(bgraG);
	//FVertex vertexG = { infoG, edgeLen, edgeLen, -edgeLen };

	//BGRA* bgraH = new BGRA(mature, mature, mature);
	//Info* infoH = new Info(bgraH);
	//FVertex vertexH = { infoH, edgeLen, edgeLen, edgeLen };

	//vertexData.push_back();
	scfParse("media/cube.scj", vertexData);
	Texture* texture = new FITexture("media/test.jpg");
	mPipeline.confViewport(WIDTH, HEIGHT);
	cameraPosition[1] += 3*POSITION_STEP;
	// TODO: change near plane seems don't have any effect
	mPipeline.confProjection(perspectiveMatrix(radians(45.0f), 1.0f, 2.0f, -10.0f));
	mPipeline.confTexture(texture);
	mPipeline.confMode(GL_TRIANGLES);
	refreshFrame();
}
void testTrivia() {
	FVertex vertexData;
}

int main(void)
{
	int indicator = 0;
	int kbhit = 0;
	float alpha = 1;
	float pos = 3.5;

	// TODO: the order between uniform and framebuffer storage is so weird
	Uniform mUniform(WIDTH, HEIGHT, &mFramebuffer);
	mUniform.mKeyCallback = *keysCallback;

	mFramebuffer.setBufferStorage(WIDTH, HEIGHT);
	
	//testRectangle(width, height, mFramebuffer);
	//testCircleAn(width, height, mFramebuffer);

	//testRasterLine();
	//testRasterPoint();
	//testRasterTriangle();
	//testTrivia();

	//testPoint();
	//testLine();
	//testTriangle();
	//testTriangleStrip();
	testCube();

	mUniform.runRender();

	return 0;
}

//int main(void) {
//	//const char* img = "test.jpg";
//	//FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(img);
//	//FIBITMAP *bmp = FreeImage_Load(fif, img);
//
//	//unsigned width = FreeImage_GetWidth(bmp);
//	//unsigned height = FreeImage_GetHeight(bmp);
//	//int bpp = FreeImage_GetBPP(bmp);
//
//	//FIBITMAP* bitmap = FreeImage_Allocate(width, height, bpp);
//	//RGBQUAD color; FreeImage_GetPixelColor(bitmap,50, 50, &color);
//
//	//float r, g, b;
//	//r = color.rgbRed;
//	//g = color.rgbGreen;
//	//b = color.rgbBlue;
//
//	//cout << r << g << b;
//
//	fipImage input;
//	RGBQUAD pixel;
//
//	input.load("test.jpg");
//	int height = input.getHeight();
//
//	input.getPixelColor(50, height - 1 - 50, &pixel);
//
//	int blue = pixel.rgbBlue;
//	int green = pixel.rgbGreen;
//	int red = pixel.rgbRed;
//	cout << blue << green << red << endl;
//
//	int wait;
//	cin >> wait;
//}
