#ifndef _MSG_BOX_H_
#define _MSG_BOX_H_
#include "ui.h"
#include <string>
class CMsgBox : public CUI
{
private:
	std::string sid[2];
	std::string m_Text;
	int m_Code;
public:
	CMsgBox(int x, int y, int w, int h);
	void Init();
	void ActRender();
	void RunText(const char * txt,int code);
	//获取消息框标志，消息框可能多次用到，可以借此标志来区分是哪一次调用
	int GetCode();
	void OnMsg(int msg, int p1, int p2);
};

#endif