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
	pGO->LoadFont("CEditRoom-编辑",9, 13, 1, false, false ,false, "楷体");
	pGO->LoadImg("CEditRoom-建房框",L"pic\\建房框.png");
	pGO->LoadImg("CEditRoom-确定1",L"pic\\确定1.png");
	pGO->LoadImg("CEditRoom-确定2",L"pic\\确定2.png");
	pGO->LoadImg("CEditRoom-取消1",L"pic\\取消1.png");  
	pGO->LoadImg("CEditRoom-取消2",L"pic\\取消2.png");

	m_Scene->LoadUI("建房框-编辑", new CEdit("CEditRoom-编辑", RGB(30,30,0), m_X+28,m_Y+42,180,28));
	m_Scene->LoadUI("建房框-确定", new CBmpButton("CEditRoom-确定1","CEditRoom-确定1","CEditRoom-确定2",m_X+50,m_Y+80,27,12));
	m_Scene->LoadUI("建房框-取消", new CBmpButton("CEditRoom-取消1","CEditRoom-取消1","CEditRoom-取消2",m_X+132,m_Y+80,27,12));

	sid[0]="建房框-编辑";
	sid[1]="建房框-确定";
	sid[2]="建房框-取消";
}
void CEditRoom::ActRender()
{
	CGameEngine::GetGE()->GetGO()->DrawImg("CEditRoom-建房框",m_X,m_Y,m_W,m_H);
	for(int i=0;i<3;i++)
		m_Scene->GetUI(sid[i].c_str())->ActRender();
}

//获取房间名称
const char * CEditRoom::GetText()
{
	return ((CEdit*)(m_Scene->GetUI("建房框-编辑")))->GetText();
}

//消息分流
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
				//判断光标是否在 按钮中
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
			m_Scene->GetUI("建房框-编辑")->OnMsg(_UIM_K_CHAR, p1, p2);
			break;
		}
	}
}