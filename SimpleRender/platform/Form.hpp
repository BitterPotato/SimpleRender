#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include "FrameBuffer.hpp"

#include <windows.h>
#include <winuser.h>
#include <tchar.h>

//typedef void(*f_keys) (int*);

class Form {
public:
	function<void (int* screen_keys)> mKeyCallback;

	MY_COMP_FUNC_DECL virtual void runRender() const = 0;

protected:
	int screen_w, screen_h;
	FrameBuffer* mFrameBuffer;
};

#endif