// SimpleRender.cpp : Defines the entry point for the console application.
//

#include "SimpleDelegate.hpp"

SimpleDelegate* simpleDelegate;

void keysCallback(int* screen_keys) {
	if (simpleDelegate)
		simpleDelegate->keysCallback(screen_keys);
}

int main(void)
{
	const int width = 800;
	const int height = 800;
	// TODO: the order between uniform and framebuffer storage is so weird
	FrameBuffer frameBuffer;
	Uniform uniform(width, height, &frameBuffer);
	frameBuffer.setBufferStorage(width, height);

	simpleDelegate = new SimpleDelegate(uniform, frameBuffer, width, height);
	uniform.mKeyCallback = keysCallback;
	
	simpleDelegate->testCube();

	uniform.runRender();

	int wait;
	cin >> wait;
	return 0;
}