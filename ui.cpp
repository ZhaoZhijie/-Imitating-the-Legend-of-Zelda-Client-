#include "ui.h"

CUI::CUI(int x, int y, int w, int h, bool View, bool Act)
:
m_X(x),
m_Y(y),
m_W(w),
m_H(h),
m_View(View),
m_Act(Act),
m_Scene(0)
{}

CUI::~CUI(){}

//设置UI的矩形
void CUI::SetRect(int x, int y, int w, int h)
{
	m_X = x;
	m_Y = y;
	m_W = w;
	m_H = h;
}
//获取UI的矩形
void CUI::GetRect(int* x, int* y, int* w, int* h)
{
	*x = m_X;
	*y = m_Y;
	*w = m_W;
	*h = m_H;
}
//设置是否可见
void CUI::SetView(bool View)
{
	m_View = View;
}
//获取UI是否可见
bool CUI::GetView()
{
	return m_View;
}
//设置是否可用
void CUI::SetAct(bool Act)
{
	m_Act = Act;
}
//获取UI是否可用
bool CUI::GetAct()
{
	return m_Act;
}

//初始化
void CUI::Init()
{}
//激活渲染
void CUI::ActRender()
{}
//非激活渲染
void CUI::UnActRender()
{}
//获取消息
void CUI::OnMsg(int msg, int p1, int p2)
{}
void CUI::End()
{}
