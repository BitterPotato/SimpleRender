//
// Created by WJ Yang on 2017/9/24.
//

#ifndef SIMPLERENDER_WINFORM_HPP
#define SIMPLERENDER_WINFORM_HPP

#include "Form.hpp"

#include <windows.h>
//#include <winuser.h>
#include <tchar.h>

class WinForm : public Form{
public:
    WinForm(int width, int height, FrameBuffer* framebuffer);
    MY_COMP_FUNC_DECL void runRender() const override ;
private:
    // 屏幕初始化
    MY_COMP_FUNC_DECL int screen_init(int w, int h, const TCHAR *title) const;
    // 关闭屏幕
    MY_COMP_FUNC_DECL int screen_close(void) const;
    MY_UTIL_DECL LRESULT screen_events(HWND hWnd, UINT msg,
                                   WPARAM wParam, LPARAM lParam) ;
    // 处理消息
    MY_COMP_FUNC_DECL void screen_dispatch(void) const;
    // 显示FrameBuffer
    MY_COMP_FUNC_DECL void screen_update(void) const;
};


#endif //SIMPLERENDER_WINFORM_HPP
