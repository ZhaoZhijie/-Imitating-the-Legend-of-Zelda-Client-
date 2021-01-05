#ifndef _AUTO_PLAY_H
#define _AUTO_PLAY_H
#include "ui.h"
#include <vector>
#include "GameEngine.h"
class CAutoPlay : public CUI
{
protected:
	std::vector<std::string> m_path;//轮播图片id
	std::string m_logo;//logo图片id
	int m_len;//图片总数
	int m_pos;//当前图片下标
	int m_cd;//图片切换间隔帧数
	int m_cf;//当前图片持续帧数
	RECT m_r;//logo矩形
	int m_state;//状态 
public:
	CAutoPlay(int cd, int x, int y, int w, int h, bool View = true, bool Act = true);
	bool AddPic(const char* id);
	bool SetLogo(const char *id, int x, int y, int w, int h);
	void Render();
};
#endif