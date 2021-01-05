#include "Button.h"
#include "Scene.h"
#include "GameEngine.h"

CButton::CButton(const char* t, int x, int y, int w, int h, bool View, bool Act)
:
//构造父类
CUI(x,y,w,h,View,Act)
{
	m_In = false;
	m_Text = t;
	m_ButtonState = _BUTTON_STATE_CURSOR_OUT;
}

void CButton::ActRender()
{
	//获取绘制工具
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();

	//绘制实心矩形  根据光标是否在按钮中 改变颜色绘制
	pGO->DrawSRectangle(m_X, m_Y, m_X + m_W, m_Y + m_H,
		RGB(0, 0, 0), m_In ? RGB(255, 0, 0) : RGB(0, 255, 0));

	//绘制文字
	pGO->DrawString(0,  m_X, m_Y, m_W, m_H, m_Text.c_str(), RGB(0, 0, 0));
}

void CButton::UnActRender()
{
	//获取绘制工具
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();

	//绘制实心矩形
	pGO->DrawSRectangle(m_X, m_Y, m_X + m_W, m_Y + m_H,
		RGB(0, 0, 0), RGB(127, 127, 127));

	//绘制文字								c_str 返回一个char*
	pGO->DrawString(0,  m_X, m_Y, m_W, m_H, m_Text.c_str(), RGB(0, 0, 0));
}


void CButton::OnMsg(int msg, int p1, int p2)
{
	switch(msg)
	{
	case _UIM_C_ENTER: 
		{
			m_In = true; 
			m_ButtonState = _BUTTON_STATE_CURSOR_IN_UP;
			break;
		}
	case _UIM_C_QUIT: 
		{
			m_ButtonState = _BUTTON_STATE_CURSOR_OUT;
			m_In = false; 
			break;
		}
	case _UIM_C_LBD_IN: 
		{
			//m_Scene->OnUIMsg(m_Name.c_str(), _BUTTON_CLICK);
			m_ButtonState = _BUTTON_STATE_CURSOR_IN_DOWN;
			break;
		}
	case _UIM_C_LBU_IN: 
		{
			m_Scene->OnUIMsg(m_Name.c_str(), _BUTTON_CLICK);
			m_ButtonState = _BUTTON_STATE_CURSOR_IN_UP;
			break;
		}
	}
}

//设置按钮文字
void CButton::SetText(const char* t)
{
	m_Text = t;	
}
const char* CButton::GetText()
{
	return m_Text.c_str();
}


