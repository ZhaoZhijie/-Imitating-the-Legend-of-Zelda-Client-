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

//����UI�ľ���
void CUI::SetRect(int x, int y, int w, int h)
{
	m_X = x;
	m_Y = y;
	m_W = w;
	m_H = h;
}
//��ȡUI�ľ���
void CUI::GetRect(int* x, int* y, int* w, int* h)
{
	*x = m_X;
	*y = m_Y;
	*w = m_W;
	*h = m_H;
}
//�����Ƿ�ɼ�
void CUI::SetView(bool View)
{
	m_View = View;
}
//��ȡUI�Ƿ�ɼ�
bool CUI::GetView()
{
	return m_View;
}
//�����Ƿ����
void CUI::SetAct(bool Act)
{
	m_Act = Act;
}
//��ȡUI�Ƿ����
bool CUI::GetAct()
{
	return m_Act;
}

//��ʼ��
void CUI::Init()
{}
//������Ⱦ
void CUI::ActRender()
{}
//�Ǽ�����Ⱦ
void CUI::UnActRender()
{}
//��ȡ��Ϣ
void CUI::OnMsg(int msg, int p1, int p2)
{}
void CUI::End()
{}
