#ifndef _PLAYER_BOX_H
#define _PLAYER_BOX_H
#include "ui.h"
#include <string>
#define _PBOX_NULL 0//没人
#define _PBOX_PRE 1//准备
#define _PBOX_UNPRE 2//未准备
#define _PBOX_ADMIN 3//房主
#define _PLAYER_CLICK 0//点击玩家
class CPlayerBox : public CUI
{
protected:
	std::string m_name;//玩家名字
	std::string m_img;//玩家头像
	int m_state;//玩家状态  房主 准备  未准备  没人
	int m_cursor;//鼠标状态
public:
	CPlayerBox(int x, int y, int w, int h, bool View = true, bool Act = true);
	void ActRender();
	bool Enter(const char * name,const char * img);
	bool SetState(int s);
	int GetState();
	void Quit();
	void OnMsg(int msg, int p1, int p2);
};
#endif