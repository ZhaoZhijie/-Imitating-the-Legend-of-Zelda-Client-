#include "EditRoom.h"
#include "GameEngine.h"
#include "Scene.h"
#include "Edit.h"
#include "BmpButton.h"
CEditRoom::CEditRoom(int x, int y, int w, int h)
:CUI(x,y,w,h,true,true)
{
}
void CEditRoom::Init()
{
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	pGO->LoadFont("CEditRoom-�༭",9, 13, 1, false, false ,false, "����");
	pGO->LoadImg("CEditRoom-������",L"pic\\������.png");
	pGO->LoadImg("CEditRoom-ȷ��1",L"pic\\ȷ��1.png");
	pGO->LoadImg("CEditRoom-ȷ��2",L"pic\\ȷ��2.png");
	pGO->LoadImg("CEditRoom-ȡ��1",L"pic\\ȡ��1.png");  
	pGO->LoadImg("CEditRoom-ȡ��2",L"pic\\ȡ��2.png");

	m_Scene->LoadUI("������-�༭", new CEdit("CEditRoom-�༭", RGB(30,30,0), m_X+28,m_Y+42,180,28));
	m_Scene->LoadUI("������-ȷ��", new CBmpButton("CEditRoom-ȷ��1","CEditRoom-ȷ��1","CEditRoom-ȷ��2",m_X+50,m_Y+80,27,12));
	m_Scene->LoadUI("������-ȡ��", new CBmpButton("CEditRoom-ȡ��1","CEditRoom-ȡ��1","CEditRoom-ȡ��2",m_X+132,m_Y+80,27,12));

	sid[0]="������-�༭";
	sid[1]="������-ȷ��";
	sid[2]="������-ȡ��";
}
void CEditRoom::ActRender()
{
	CGameEngine::GetGE()->GetGO()->DrawImg("CEditRoom-������",m_X,m_Y,m_W,m_H);
	for(int i=0;i<3;i++)
		m_Scene->GetUI(sid[i].c_str())->ActRender();
}

//��ȡ��������
const char * CEditRoom::GetText()
{
	return ((CEdit*)(m_Scene->GetUI("������-�༭")))->GetText();
}

//��Ϣ����
void CEditRoom::OnMsg(int msg, int p1, int p2)
{
	switch(msg)
	{
	case _UIM_C_ENTER:
	case _UIM_C_LBD_IN:
	case _UIM_C_LBU_IN:
		{
			POINT p = {p1, p2};
			RECT r;
			for(int i=0;i<3;i++)
			{
				m_Scene->GetUI(sid[i].c_str())->GetRect((int*)&r.left, (int*)&r.top, (int*)&r.right, (int*)&r.bottom);
				r.right += r.left;
				r.bottom += r.top;
				//�жϹ���Ƿ��� ��ť��
				if(PtInRect(&r, p))
				{
					m_Scene->GetUI(sid[i].c_str())->OnMsg(msg,p1,p2);
					if(i==0&&msg==_UIM_C_LBD_IN)
						m_Scene->GetUI(sid[i].c_str())->SetAct(true);
				}
			}
			break;
		}
	case _UIM_C_QUIT:
		{
			for(int i=0;i<3;i++)
				m_Scene->GetUI(sid[i].c_str())->OnMsg(_UIM_C_QUIT,p1,p2);
			break;
		}
	case _UIM_C_LBD_OUT:
		{
			for(int i=0;i<3;i++)
				m_Scene->GetUI(sid[i].c_str())->OnMsg(_UIM_C_LBD_OUT,p1,p2);
			break;
		}
	case _UIM_K_CHAR:
		{
			m_Scene->GetUI("������-�༭")->OnMsg(_UIM_K_CHAR, p1, p2);
			break;
		}
	}
}