#ifndef _BMP_BUTTON_H_
#define _BMP_BUTTON_H_

#include "Button.h"
#include <string>
#include <windows.h>

class CBmpButton : public CButton
{
	std::string s[3];	//图片路径保存
public: 
	CBmpButton(
		const char* bmp_cursor_out,		//鼠标在控件外部的图片
		const char* bmp_cursor_in_up,	//鼠标在控件内部没有按下的图片
		const char* bmp_cursor_in_down,	//鼠标在控件内部按下后的图片
		int x, int y, int w, int h);					

	void ActRender();

};

#endif