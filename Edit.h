#ifndef _EDIT_H
#define _EDIT_H
#include "ui.h"
#include <string>
class CEdit : public CUI
{
protected:
	char m_Text[200];	//编辑框的文字
	int m_pos;//插入符位置
	std::string m_FontName;
	bool m_tag;//是否闪动
	int m_cf;
	unsigned int m_cor;
public:
	CEdit(char *fn, unsigned int c, int x, int y, int w, int h, bool View = true, bool Act = true);
	//获取编辑框文本
	const char * GetText();
	//设置编辑框文本
	void SetText(const char * txt);
	void ActRender();
	//非激活渲染
	void UnActRender();
	//获取消息
	//如果是光标类消息: p1为 x坐标 p2 为 y坐标(相对控件的矩形)
	//如果是键盘消息: p1为传入的键值
	//如果是字符消息: p1为传入的字符, p2表示是否为双字节（1为是 0为否）
	void OnMsg(int msg, int p1, int p2);
};
#endif