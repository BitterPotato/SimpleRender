// SimpleRender.cpp : Defines the entry point for the console application.
//

//#define LINE_Bresenham
#define LINE_WuXiaolin

#include "../util/type_def.hpp"
#include "../platform/uniform.hpp"
#include "../platform/framebuffer.hpp"
#include "../raster/Point.hpp"
#include "../raster/Line.hpp"

#include <iostream>
#include <cmath>

using std::cout;
//=====================================================================
// Ö÷³ÌÐò
//=====================================================================

framebuffer mFramebuffer;
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

void testRectangle(int width, int height, framebuffer& fb) {
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
void testCircleAn(int width, int height, framebuffer& fb) {
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
void fsImpl(const Frag& frag) {
	//if (frag.x < 400) {
		mFramebuffer.setBufferPixel(frag.x, frag.y, *frag.info.bgra);
	//}
}

// ========== rasterization =============
inline void testRasterPoint() {
	BGRA bgra{ 255, 128, 64, 255 };
	Info info{ &bgra, 0, 0 };

	Vertex vertex{ 760, 760,  info };
	rasterPoint(vertex, 40).runFrags(*fsImpl);
}

inline void testRasterLine() {
	//BGRA bgra{ 255, 128, 64, 255 };
	//Info info{ bgra, 0, 0 };
	BGRA bgraB{ 255, 255, 0, 255 };
	Info infoB{ &bgraB, 0, 0 };
	BGRA bgraE{ 0, 0, 255, 255 };
	Info infoE{ &bgraE, 0, 0 };

	//Vertex vertexBegin{ 100, 100, info };
	//Vertex vertexEnd{ 100, 150, info };
	//Vertex vertexBegin{ 100, 100, info };
	//Vertex vertexEnd{ 150, 100, info };
	//Vertex vertexBegin{ 100, 100, info };
	//Vertex vertexEnd{ 150, 150, info };

	//Vertex vertexBegin{ 100, 100, info };
	//Vertex vertexEnd{ 300, 150, info };
	//Vertex vertexBegin{ 100, 150, info };
	//Vertex vertexEnd{ 300, 100, info };
	//Vertex vertexBegin{ 100, 100, info };
	//Vertex vertexEnd{ 200, 300, info };
	Vertex vertexBegin{ 100, 100, infoB };
	Vertex vertexEnd{ 800, 800, infoE };
	rasterLine(vertexBegin, vertexEnd, 1).runFrags(*fsImpl);
}

int main(void)
{
	int indicator = 0;
	int kbhit = 0;
	float alpha = 1;
	float pos = 3.5;

	int width = 800;
	int height = 800;

	// TODO: the order between uniform and framebuffer storage is so weird
	uniform mUniform(width, height, &mFramebuffer);
	mUniform.mKeyCallback = *keysCallback;

	mFramebuffer.setBufferStorage(width, height);
	
	//testRectangle(width, height, mFramebuffer);
	//testCircleAn(width, height, mFramebuffer);

	testRasterLine();
	//testRasterPoint();

	mUniform.runRender();

	return 0;
}

