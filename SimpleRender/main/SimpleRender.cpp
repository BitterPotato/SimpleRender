// SimpleRender.cpp : Defines the entry point for the console application.
//

#include "../util/type_def.hpp"
#include "../platform/uniform.hpp"
#include "../platform/framebuffer.hpp"

#include <iostream>

using std::cout;
//=====================================================================
// Ö÷³ÌÐò
//=====================================================================

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

int main(void)
{
	int indicator = 0;
	int kbhit = 0;
	float alpha = 1;
	float pos = 3.5;

	int width = 800;
	int height = 800;

	framebuffer mFramebuffer;
	uniform mUniform(width, height, &mFramebuffer);
	mUniform.mKeyCallback = *keysCallback;

	mFramebuffer.setBufferStorage(width, height);
	
	BGRA bgra{ 255, 128, 64, 255 };
	// test for a region
	int upLeftX = width / 5 * 2;
	int upLeftY = height / 5 * 2;
	for (int i = 0; i < width / 5; i++) {
		for (int j = 0; j < height / 5; j++) {
			mFramebuffer.setBufferPixel(upLeftX + i, upLeftY + j, bgra);
		}
	}

	mUniform.runRender();

	return 0;
}

