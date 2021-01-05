#include "MsgBox.h"
#include "GameEngine.h"
#include "Scene.h"
#include "BmpButton.h"
CMsgBox::CMsgBox(int x, int y, int w, int h)
	:CUI(x,y,w,h,false,true)
{}
void CMsgBox::Init()
{
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	pGO->LoadFont("CMsgBox-�ı�",9, 13, 1, false, false ,false, "����");
	pGO->LoadImg("CMsgBox-��Ϣ��",L"pic\\��Ϣ��.png");
	pGO->LoadImg("CMsgBox-ȷ��1",L"pic\\ȷ��1.png");
	pGO->LoadImg("CMsgBox-ȷ��2",L"pic\\ȷ��2.png");
	pGO->LoadImg("CMsgBox-ȡ��1",L"pic\\ȡ��1.png");  
	pGO->LoadImg("CMsgBox-ȡ��2",L"pic\\ȡ��2.png");
	m_Scene->LoadUI("��Ϣ��-ȷ��", new CBmpButton("CEditRoom-ȷ��1","CEditRoom-ȷ��1","CEditRoom-ȷ��2",m_X+70,m_Y+94,27,12));
	m_Scene->LoadUI("��Ϣ��-ȡ��", new CBmpButton("CEditRoom-ȡ��1","CEditRoom-ȡ��1","CEditRoom-ȡ��2",m_X+155,m_Y+94,27,12));
	sid[0]="��Ϣ��-ȷ��";
	sid[1]="��Ϣ��-ȡ��";
}
void CMsgBox::ActRender()
{
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	pGO->DrawImg("CMsgBox-��Ϣ��",m_X,m_Y,m_W,m_H);
	pGO->DrawString("CMsgBox-�ı�",m_X+23,m_Y+43,227,47,m_Text.c_str(),RGB(225,225,30));
	for(int i=0;i<2;i++)
		m_Scene->GetUI(sid[i].c_str())->ActRender();
}
void CMsgBox::RunText(const char * txt,int code)
{
	m_Text=txt;
	m_View=true;
}
int CMsgBox::GetCode()
{
	return m_Code;
}
void CMsgBox::OnMsg(int msg, int p1, int p2)
{
	switch(msg)
	{
	case _UIM_C_ENTER:
	case _UIM_C_LBD_IN:
	case _UIM_C_LBU_IN:
		{
			POINT p = {p1, p2};
			RECT r;
			for(int i=0;i<2;i++)
			{
				m_Scene->GetUI(sid[i].c_str())->GetRect((int*)&r.left, (int*)&r.top, (int*)&r.right, (int*)&r.bottom);
				r.right += r.left;
				r.bottom += r.top;
				//�жϹ���Ƿ��� ��ť��
				if(PtInRect(&r, p))
					m_Scene->GetUI(sid[i].c_str())->OnMsg(msg,p1,p2);
			}
			break;
		}
	case _UIM_C_QUIT:
		{
			for(int i=0;i<2;i++)
				m_Scene->GetUI(sid[i].c_str())->OnMsg(_UIM_C_QUIT,p1,p2);
			break;
		}
	case _UIM_C_LBD_OUT:
		{
			for(int i=0;i<2;i++)
				m_Scene->GetUI(sid[i].c_str())->OnMsg(_UIM_C_LBD_OUT,p1,p2);
			break;
		}
	}
}