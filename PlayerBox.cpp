#include "PlayerBox.h"	
#include "Scene.h"
#include "GameEngine.h"
#define _STATE_CURSOR_IN_UP 0
#define _STATE_CURSOR_IN_DOWN 1
#define _STATE_CURSOR_OUT 2
CPlayerBox::CPlayerBox(int x, int y, int w, int h, bool View, bool Act)
	:CUI(x, y, w, h, View, Act)
{
	m_state=_PBOX_NULL;
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	pGO->LoadFont("��Һ���-����",9, 13, 1, false, false ,false, "����");
	pGO->LoadImg("״̬-����", L"pic\\״̬-����.png");
	pGO->LoadImg("״̬-δ׼��", L"pic\\״̬-׼��1.png");
	pGO->LoadImg("״̬-׼��", L"pic\\״̬-׼��2.png");
	pGO->LoadImg("��Һ���", L"pic\\��Һ���2.png");
}
void CPlayerBox::ActRender()
{
		CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
		pGO->DrawImg("��Һ���",m_X-47,m_Y-21,210,220);
		if(m_state!=_PBOX_NULL)
		{//260 256 290 284 
			pGO->DrawStringS("��Һ���-����",m_X+30,m_Y+28,m_name.c_str(),RGB(227,227,30));
			if(m_state==_PBOX_PRE)
				pGO->DrawImg("״̬-׼��",m_X+50,m_Y+138,34,17);//259  256   309 394 
			else if(m_state==_PBOX_UNPRE)
				pGO->DrawImg("״̬-δ׼��",m_X+50,m_Y+138,34,17);//259  256   309 394 
			else if(m_state==_PBOX_ADMIN)
				pGO->DrawImg("״̬-����",m_X+50,m_Y+138,34,17);//259  256   309 394 
		}
}
bool CPlayerBox::Enter(const char * name,const char * img)
{
	//if(m_state!=_PBOX_NULL)
	//	return false;
	m_state=_PBOX_UNPRE;
	m_name=name;
	m_img=img;
	return true;
}
bool CPlayerBox::SetState(int s)
{
	if(s<0||s>3)
		return false;
	m_state=s;
}
int CPlayerBox::GetState()
{
	return m_state;
}
void CPlayerBox::Quit()
{
	m_state=_PBOX_NULL;
}
void CPlayerBox::OnMsg(int msg, int p1, int p2)
{
	switch(msg)
	{
	case _UIM_C_ENTER: 
		{
			m_cursor = _STATE_CURSOR_IN_UP;
			break;
		}
	case _UIM_C_QUIT: 
		{
			m_cursor = _STATE_CURSOR_OUT;
			break;
		}
	case _UIM_C_LBD_IN: 
		{
			m_cursor = _STATE_CURSOR_IN_DOWN;
			break;
		}
	case _UIM_C_LBU_IN:
		{
			m_cursor = _STATE_CURSOR_IN_UP;
			m_Scene->OnUIMsg(m_Name.c_str(), _PLAYER_CLICK);
			break;			
		}
	}
}