#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include "framebuffer.hpp"

#include <windows.h>
#include <tchar.h>

typedef void(*f_keys) (int*);

class Uniform {
public:
	int screen_w, screen_h;

	f_keys mKeyCallback;

	Uniform(int width, int height, FrameBuffer* framebuffer);

	void runRender();

private:
	FrameBuffer* mFrameBuffer;

	int screen_init(int w, int h, const TCHAR *title);	// 屏幕初始化
	int screen_close(void);								// 关闭屏幕
	void screen_dispatch(void);							// 处理消息
	void screen_update(void);							// 显示 FrameBuffer
};

#endif