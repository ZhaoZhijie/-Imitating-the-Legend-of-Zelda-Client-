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
	pGO->LoadFont("CMsgBox-文本",9, 13, 1, false, false ,false, "楷体");
	pGO->LoadImg("CMsgBox-消息框",L"pic\\消息框.png");
	pGO->LoadImg("CMsgBox-确定1",L"pic\\确定1.png");
	pGO->LoadImg("CMsgBox-确定2",L"pic\\确定2.png");
	pGO->LoadImg("CMsgBox-取消1",L"pic\\取消1.png");  
	pGO->LoadImg("CMsgBox-取消2",L"pic\\取消2.png");
	m_Scene->LoadUI("消息框-确定", new CBmpButton("CEditRoom-确定1","CEditRoom-确定1","CEditRoom-确定2",m_X+70,m_Y+94,27,12));
	m_Scene->LoadUI("消息框-取消", new CBmpButton("CEditRoom-取消1","CEditRoom-取消1","CEditRoom-取消2",m_X+155,m_Y+94,27,12));
	sid[0]="消息框-确定";
	sid[1]="消息框-取消";
}
void CMsgBox::ActRender()
{
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	pGO->DrawImg("CMsgBox-消息框",m_X,m_Y,m_W,m_H);
	pGO->DrawString("CMsgBox-文本",m_X+23,m_Y+43,227,47,m_Text.c_str(),RGB(225,225,30));
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
				//判断光标是否在 按钮中
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