#ifndef _EDIT_ROOM_H_
#define _EDIT_ROOM_H_
#include "ui.h"
#include <string>
class CEditRoom : public CUI
{
private:
	std::string sid[3];
public:
	CEditRoom(int x, int y, int w, int h);
	void Init();
	void ActRender();
	void OnMsg(int msg, int p1, int p2);
	//获取编辑框文本
	const char * GetText();
};

#endif