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
	pGO->LoadFont("玩家盒子-名字",9, 13, 1, false, false ,false, "楷体");
	pGO->LoadImg("状态-房主", L"pic\\状态-房主.png");
	pGO->LoadImg("状态-未准备", L"pic\\状态-准备1.png");
	pGO->LoadImg("状态-准备", L"pic\\状态-准备2.png");
	pGO->LoadImg("玩家盒子", L"pic\\玩家盒子2.png");
}
void CPlayerBox::ActRender()
{
		CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
		pGO->DrawImg("玩家盒子",m_X-47,m_Y-21,210,220);
		if(m_state!=_PBOX_NULL)
		{//260 256 290 284 
			pGO->DrawStringS("玩家盒子-名字",m_X+30,m_Y+28,m_name.c_str(),RGB(227,227,30));
			if(m_state==_PBOX_PRE)
				pGO->DrawImg("状态-准备",m_X+50,m_Y+138,34,17);//259  256   309 394 
			else if(m_state==_PBOX_UNPRE)
				pGO->DrawImg("状态-未准备",m_X+50,m_Y+138,34,17);//259  256   309 394 
			else if(m_state==_PBOX_ADMIN)
				pGO->DrawImg("状态-房主",m_X+50,m_Y+138,34,17);//259  256   309 394 
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