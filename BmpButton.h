#ifndef _BMP_BUTTON_H_
#define _BMP_BUTTON_H_

#include "Button.h"
#include <string>
#include <windows.h>

class CBmpButton : public CButton
{
	std::string s[3];	//ͼƬ·������
public: 
	CBmpButton(
		const char* bmp_cursor_out,		//����ڿؼ��ⲿ��ͼƬ
		const char* bmp_cursor_in_up,	//����ڿؼ��ڲ�û�а��µ�ͼƬ
		const char* bmp_cursor_in_down,	//����ڿؼ��ڲ����º��ͼƬ
		int x, int y, int w, int h);					

	void ActRender();

};

#endif