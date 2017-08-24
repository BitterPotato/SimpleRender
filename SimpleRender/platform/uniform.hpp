#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include "framebuffer.hpp"
#include "../util/type_def.hpp"

#include <windows.h>
#include <tchar.h>


class uniform {
public:
	int screen_w, screen_h;

	f_keys mKeyCallback;

	uniform(int width, int height, framebuffer* framebuffer);

	void runRender();

private:
	framebuffer* mFrameBuffer;

	int screen_init(int w, int h, const TCHAR *title);	// ��Ļ��ʼ��
	int screen_close(void);								// �ر���Ļ
	void screen_dispatch(void);							// ������Ϣ
	void screen_update(void);							// ��ʾ FrameBuffer
};

#endif