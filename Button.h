#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "ui.h"

#define _BUTTON_CLICK 0		//按钮被按下的消息
//控件当前状态
#define _BUTTON_STATE_CURSOR_OUT 0		//鼠标在控件外部
#define _BUTTON_STATE_CURSOR_IN_UP 1	//鼠标在控件内部，没有按下
#define _BUTTON_STATE_CURSOR_IN_DOWN 2	//鼠标在控件内部，按下
#define _BUTTON_STATE_UNACT 3			//控件不可用

class CButton : public CUI
{
protected:
	int m_ButtonState;	//按键当前的状态
	bool m_In;			//光标在按钮内的标记
	std::string m_Text;	//按钮的文字

public:
	CButton(const char* t, int x, int y, int w, int h, bool View = true, bool Act = true);
	void ActRender();
	//非激活渲染
	void UnActRender();
	//获取消息
	//如果是光标类消息: p1为 x坐标 p2 为 y坐标(相对控件的矩形)
	//如果是键盘消息: p1为传入的键值
	//如果是字符消息: p1为传入的字符, p2表示是否为双字节（1为是 0为否）
	void OnMsg(int msg, int p1, int p2);

	//设置按钮文字
	void SetText(const char* t);
	const char* GetText();
};

#endif