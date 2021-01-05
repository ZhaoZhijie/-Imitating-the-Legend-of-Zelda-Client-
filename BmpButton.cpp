#include "GameEngine.h"
#include "BmpButton.h"
#include "Scene.h"

CBmpButton::CBmpButton(
		const char* bmp_cursor_out,
		const char* bmp_cursor_in_up,
		const char* bmp_cursor_in_down,
		int x, int y, int w, int h)
		:
CButton("", x, y, w, h, true, true)
{
	s[0] = bmp_cursor_out;
	s[1] = bmp_cursor_in_up;
	s[2] = bmp_cursor_in_down;
}

void CBmpButton::ActRender()
{
	//��ȡ��ʾ�豸
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	switch(m_ButtonState)
	{
	case _BUTTON_STATE_CURSOR_OUT:	//����ڿؼ�����
		{
			pGO->DrawImg(s[0].c_str(), m_X, m_Y, m_W, m_H, 0, 0, m_W, m_H);
			break;
		}
	case _BUTTON_STATE_CURSOR_IN_UP:	//����ڿؼ�����
		{
			pGO->DrawImg(s[1].c_str(), m_X, m_Y, m_W, m_H, 0, 0, m_W, m_H);
			break;
		}
	case _BUTTON_STATE_CURSOR_IN_DOWN:	//����ڿؼ����水��
		{
			pGO->DrawImg(s[2].c_str(), m_X, m_Y, m_W, m_H, 0, 0, m_W, m_H);
			break;
		}
	}
}
