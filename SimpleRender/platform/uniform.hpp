#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include "framebuffer.hpp"

#include <windows.h>
#include <winuser.h>
#include <tchar.h>
#include <functional>

//typedef void(*f_keys) (int*);

using std::function;

class Uniform {
public:
	int screen_w, screen_h;

	function<void (int* screen_keys)> mKeyCallback;

	Uniform(int width, int height, FrameBuffer* framebuffer);

	void runRender();

private:
	FrameBuffer* mFrameBuffer;

	int screen_init(int w, int h, const TCHAR *title);	// ��Ļ��ʼ��
	int screen_close(void);								// �ر���Ļ
	void screen_dispatch(void);							// ������Ϣ
	void screen_update(void);							// ��ʾ FrameBuffer
};

#endif