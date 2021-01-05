#ifndef _PLAYER_BOX_H
#define _PLAYER_BOX_H
#include "ui.h"
#include <string>
#define _PBOX_NULL 0//û��
#define _PBOX_PRE 1//׼��
#define _PBOX_UNPRE 2//δ׼��
#define _PBOX_ADMIN 3//����
#define _PLAYER_CLICK 0//������
class CPlayerBox : public CUI
{
protected:
	std::string m_name;//�������
	std::string m_img;//���ͷ��
	int m_state;//���״̬  ���� ׼��  δ׼��  û��
	int m_cursor;//���״̬
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