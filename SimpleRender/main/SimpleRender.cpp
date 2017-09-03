// SimpleRender.cpp : Defines the entry point for the console application.
//

#define LINE_Bresenham
//#define LINE_WuXiaolin

#include "../util/type_def.hpp"
#include "../platform/uniform.hpp"
#include "../platform/framebuffer.hpp"
#include "../raster/Point.hpp"
#include "../raster/Line.hpp"
#include "../raster/Triangle.hpp"
#include "../pipeline/stage_flow.hpp"
#include "../pipeline/vertex_shader.hpp"
#include "../pipeline/frag_shader.hpp"

#include <iostream>
#include <cmath>

using gl::Pipeline;

using std::cout;

#define WIDTH 800
#define HEIGHT 800

//=====================================================================
// Ö÷³ÌÐò
//=====================================================================

FrameBuffer mFramebuffer;
BGRA bgra{ 255, 128, 64, 255 };

void keysCallback(int* screen_keys) {
	if (screen_keys[VK_UP]) {
		//cout << "up keys have been clicked\n";
	}
	if (screen_keys[VK_DOWN]) {

	}
	if (screen_keys[VK_LEFT]) {

	}
	if (screen_keys[VK_RIGHT]) {

	}
	if (screen_keys[VK_SPACE]) {

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

void testPipeline() {
	vector<FVertex> vertexData;

	BGRA* bgraA = new BGRA( 255, 0, 0 );
	Info* infoA = new Info ( bgraA );
	vertexData.push_back({ infoA, 0.0f, -0.75f });

	BGRA* bgraB = new BGRA( 0, 255, 0 );
	Info* infoB = new Info(bgraB);
	vertexData.push_back({ infoB, -0.75f, 0.5f });

	BGRA* bgraC = new BGRA( 0, 0, 255 );
	Info* infoC = new Info( bgraC );
	vertexData.push_back({ infoC, 0.25f, -0.25f });
	
	MyVertexShader myVertexShader;
	MyFragShader myFragShader(&mFramebuffer);
	Pipeline pipeline;
	pipeline.confViewport(WIDTH, HEIGHT);
	pipeline.confMode(GL_TRIANGLES);
	pipeline.useProgram(vertexData, myVertexShader, myFragShader);
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
	testPipeline();
	//testTrivia();

	mUniform.runRender();

	return 0;
}
