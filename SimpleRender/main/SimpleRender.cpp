// SimpleRender.cpp : Defines the entry point for the console application.
//

#include "SimpleDelegate.hpp"

#include <iostream>
#include <vector>
#include <platform/WinForm.hpp>

using std::vector;
using std::cout;
//SimpleDelegate* simpleDelegate;

//void keysCallback(int* screen_keys) {
//	if (simpleDelegate)
//		simpleDelegate->keysCallback(screen_keys);
//}

int main(void)
{
	const int width = 800;
	const int height = 800;
	// TODO: the order between uniform and framebuffer storage is so weird
	FrameBuffer frameBuffer;
	shared_ptr<Form> uniform = make_shared<WinForm>(width, height, &frameBuffer);
	frameBuffer.setBufferStorage(width, height);

	SimpleDelegate simpleDelegate(uniform, frameBuffer, width, height);
	uniform->mKeyCallback = [&simpleDelegate](int* screen_keys) {simpleDelegate.keysCallback(screen_keys); };
	
	simpleDelegate.testBlend();

	uniform->runRender();
	

	int wait;
	cin >> wait;
	return 0;
}