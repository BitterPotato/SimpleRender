// SimpleRender.cpp : Defines the entry point for the console application.
//

#include "SimpleDelegate.hpp"
#include "platform/WinForm.hpp"
#include "platform/FrameBuffer.hpp"

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
	unique_ptr<Form> uniform(new WinForm(width, height, &frameBuffer));
	frameBuffer.setBufferStorage(width, height);

	SimpleDelegate simpleDelegate(frameBuffer, width, height);
	uniform->mKeyCallback = [&simpleDelegate](int* screen_keys) {simpleDelegate.keysCallback(screen_keys); };
	
	simpleDelegate.testCube();
//    simpleDelegate.testGeneCube();
//    simpleDelegate.testTriangle();

	uniform->runRender();
	

	int wait;
	cin >> wait;
	return 0;
}