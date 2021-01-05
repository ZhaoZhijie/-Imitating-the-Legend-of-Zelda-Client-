#ifndef _AUTO_PLAY_H
#define _AUTO_PLAY_H
#include "ui.h"
#include <vector>
#include "GameEngine.h"
class CAutoPlay : public CUI
{
protected:
	std::vector<std::string> m_path;//�ֲ�ͼƬid
	std::string m_logo;//logoͼƬid
	int m_len;//ͼƬ����
	int m_pos;//��ǰͼƬ�±�
	int m_cd;//ͼƬ�л����֡��
	int m_cf;//��ǰͼƬ����֡��
	RECT m_r;//logo����
	int m_state;//״̬ 
public:
	CAutoPlay(int cd, int x, int y, int w, int h, bool View = true, bool Act = true);
	bool AddPic(const char* id);
	bool SetLogo(const char *id, int x, int y, int w, int h);
	void Render();
};
#endif