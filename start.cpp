#include "start.h"
#include "Button.h"
#include "Edit.h"
#include "BmpButton.h"
#include "GameProtocol.h"

#define _STATE_LJ_PRE 0
#define _STATE_LJ_MID 1
#define _STATE_LJ_ERROR 2
#define _STATE_PASS_YES 3
#define _STATE_PASS_NO 4
#define _STATE_PASS_ERROR 5
#define _STATE_PASS_ALREADY 6
void CStart::Init()
{
	m_state=_STATE_LJ_PRE;
	m_curtag=false;
	m_Client=CGameEngine::GetGE()->GetClient();
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	pGO->LoadImg("鼠标上", L"pic\\鼠标上.png");
	pGO->LoadImg("鼠标下", L"pic\\鼠标下.png");
	pGO->LoadImg("登陆", L"pic\\登录框.png");
	pGO->LoadImg("背景1", L"pic\\bg1.bmp");
	pGO->LoadImg("背景2", L"pic\\bg2.bmp");
	pGO->LoadImg("背景3", L"pic\\bg3.bmp");
	pGO->LoadImg("背景4", L"pic\\bg4.bmp");
	pGO->LoadImg("标志", L"pic\\logo.bmp");
	pGO->LoadImg("确定1",L"pic\\确定1.bmp");
	pGO->LoadImg("确定2",L"pic\\确定2.bmp");

	m_AutoShow=new CAutoPlay(240,0,0,640,480);
	m_AutoShow->SetLogo("标志",465,0,172,108);
	m_AutoShow->AddPic("背景1");
	m_AutoShow->AddPic("背景2");
	m_AutoShow->AddPic("背景3");
	m_AutoShow->AddPic("背景4");

	CGameEngine::GetGE()->GetGO()->LoadFont("标准",9, 13, 1, false, false ,false, "新体");		
	LoadUI("用户名", new CEdit("标准", RGB(248,232,0), 252, 218, 175, 22));//423
	LoadUI("密码", new CEdit("标准", RGB(248,232,0), 252, 261, 175, 22));
	LoadUI("服务器", new CEdit("标准", RGB(248,232,0), 212, 301, 89, 17));
	LoadUI("端口", new CEdit("标准", RGB(248,232,0), 361, 301, 42, 17));
	GetUI("用户名")->SetAct(true);

	//消息框
	LoadUI("消息框",new CMsgBox(184,173,271,134));
	GetUI("消息框")->Init();

	((CEdit*)GetUI("用户名"))->SetText("jack");
	((CEdit*)GetUI("密码"))->SetText("123456");
	((CEdit*)GetUI("服务器"))->SetText("127.0.0.1");
	((CEdit*)GetUI("端口"))->SetText("8888");
	LoadUI("确定", new CBmpButton("确定1", "确定2", "确定2", 397,330, 92, 39));
	ShowCursor(FALSE); 
}

void CStart::OutputRun()
{
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	m_AutoShow->Render();
	pGO->DrawImg("登陆", 133,150,373,235,0,0,373,235,_MIRROR_NONE, 1);
	GetUI("用户名")->ActRender();	
	GetUI("密码")->ActRender();	
	GetUI("服务器")->ActRender();	
	GetUI("端口")->ActRender();	
	if(GetUI("确定")->GetAct())
		GetUI("确定")->ActRender();	
	else
		GetUI("确定")->UnActRender();	
	if(GetUI("消息框")->GetView())
		GetUI("消息框")->ActRender();
	switch(m_state)
	{
	case _STATE_LJ_PRE:
		{
			//pGO->DrawStringS("标准",0,0,"连接前",RGB(255,0,0));
			break;
		}
	case _STATE_LJ_MID:
		{
			//pGO->DrawStringS("标准",0,0,"连接中",RGB(255,0,0));
			break;
		}
	case _STATE_LJ_ERROR:
		{
			//pGO->DrawStringS("标准",0,0,"连接失败",RGB(255,0,0));
			break;
		}
	case _STATE_PASS_YES:
		{
			//pGO->DrawStringS("标准",0,0,"验证成功",RGB(255,0,0));
			break;
		}
	case _STATE_PASS_NO:
		{
			//pGO->DrawStringS("标准",0,0,"验证失败",RGB(255,0,0));
			break;
		}
	case _STATE_PASS_ERROR:
		{
			//pGO->DrawStringS("标准",0,0,"服务器错误",RGB(255,0,0));
			break;
		}
	case _STATE_PASS_ALREADY:
		{
			//pGO->DrawStringS("标准",0,0,"该账号已经登录",RGB(255,0,0));
			break;
		}
	}
	if(m_curtag)
		pGO->DrawImg("鼠标下", m_x,m_y,40,40,0,0,40,40,_MIRROR_NONE, 1);
	else
		pGO->DrawImg("鼠标上", m_x,m_y,40,40,0,0,40,40,_MIRROR_NONE, 1);
}

void CStart::LogicInputRun()	//输入和逻辑
{
	m_Client->Run();
	_TC_NET_EVENT evt;
	while(m_Client->GetTCNetEvent(&evt))
	{
		switch(evt.type)
		{
		case _TCNE_CONNECT_OK:
			{
				_C_S_GP2 gp2;
				const char * username=((CEdit*)GetUI("用户名"))->GetText();
				const char * userpass=((CEdit*)GetUI("密码"))->GetText();
				strncpy(gp2.uname,username,20);
				strncpy(gp2.upass,userpass,20);
				m_Client->SendData((const char*)&gp2,sizeof(gp2));
				break;
			}
		case _TCNE_CONNECT_FAIL:
			{
				m_state=_STATE_LJ_ERROR;
				break;
			}
		case _TCNE_S_DISCONNECT:
		case _TCNE_C_DISCONNECT:
		case _TCNE_E_DISCONNECT:
			{
				m_state=_STATE_LJ_ERROR;
				break;
			}
		case _TCNE_DATA:
			{
				_GAME_PROTOCOL * gp=(_GAME_PROTOCOL *)evt.data;
				switch(gp->id)
				{
				case _TRY_RESULT:
					{
						_S_C_GP3 *gp3=(_S_C_GP3 *)evt.data;
						if(gp3->result==_TRY_YES)
						{
							m_state=_STATE_PASS_YES;
							CGameEngine::GetGE()->SetCurScene("大厅场景");
						}
						else if(gp3->result==_TRY_NO)
						{
							((CMsgBox*)GetUI("消息框"))->RunText("用户名密码错误",0);
							m_state=_STATE_PASS_NO;
						}
						else if(gp3->result==_TRY_ERROR)
						{
							((CMsgBox*)GetUI("消息框"))->RunText("服务器错误",0);
							m_state=_STATE_PASS_ERROR;
						}
						else if(gp3->result==_TRY_ALREADY)
						{
							((CMsgBox*)GetUI("消息框"))->RunText("该账号已经登录",0);
							m_state=_STATE_PASS_ERROR;
						}
						break;
					}
				}
				m_Client->ReleaseTSNetEvent(&evt);
				break;
			}
		}
	}


	if(CGameEngine::GetGE()->GetGI()->Get(_GI_M_L) == _KS_DC||CGameEngine::GetGE()->GetGI()->Get(_GI_M_L) == _KS_DH)
		m_curtag=true;
	else
		m_curtag=false;
	//获取光标坐标
	CGameEngine::GetGE()->GetGI()->GetCursor(&m_x, &m_y);
	POINT p = {m_x, m_y};
	//获取按钮矩形位置
	RECT r;
	char * editstr[6]={"用户名","密码","服务器","端口","确定","消息框"};
	if(CGameEngine::GetGE()->GetAct())
	{
		for(int i=0;i<6;i++)
		{
			GetUI(editstr[i])->GetRect((int*)&r.left, (int*)&r.top, (int*)&r.right, (int*)&r.bottom);
			r.right += r.left;
			r.bottom += r.top;
			//判断光标是否在 按钮中
			if(PtInRect(&r, p))
			{
				GetUI(editstr[i])->OnMsg(_UIM_C_ENTER, p.x, p.y);
				if(CGameEngine::GetGE()->GetGI()->Get(_GI_M_L) == _KS_DC)
				{
					GetUI(editstr[i])->OnMsg(_UIM_C_LBD_IN, p.x, p.y);
					GetUI(editstr[i])->SetAct(true);
				}
				if(CGameEngine::GetGE()->GetGI()->Get(_GI_M_L) == _KS_UC)
				{
					GetUI(editstr[i])->OnMsg(_UIM_C_LBU_IN, p.x, p.y);
				}
			}
			else
			{
				GetUI(editstr[i])->OnMsg(_UIM_C_QUIT, p.x, p.y);
				if(CGameEngine::GetGE()->GetGI()->Get(_GI_M_L) == _KS_DC)
				{
					GetUI(editstr[i])->OnMsg(_UIM_C_LBD_OUT, p.x, p.y);
					GetUI(editstr[i])->SetAct(false);
				}
			}
			if(GetUI(editstr[i])->GetAct())
			{
				if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_LEFT)==_KS_DC)
					GetUI(editstr[i])->OnMsg(_UIM_K_CHAR, 37, 0);
				if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_RIGHT)==_KS_DC)
					GetUI(editstr[i])->OnMsg(_UIM_K_CHAR, 39, 0);
			}	
		}
	}
}

void CStart::OnUIMsg(const char* id, int UIMsg)
{
	if(strcmp(id,"消息框-确定")==0&&UIMsg==_BUTTON_CLICK)
	{
		GetUI("消息框")->SetView(false);
	}
	if(strcmp(id,"确定")==0)
	{
		if(UIMsg==_BUTTON_CLICK)
		{
			if(m_state==_STATE_LJ_PRE||m_state==_STATE_LJ_ERROR)
			{
				const char *ip=((CEdit*)GetUI("服务器"))->GetText();
				const char *portstr=((CEdit*)GetUI("端口"))->GetText();
				unsigned short port=atoi(portstr);
				if(m_Client->ConnectByIP(ip,port,5,2,5))
					m_state=_STATE_LJ_MID;
				else
					m_state=_STATE_LJ_ERROR;
			}
			else if(m_state==_STATE_PASS_NO||m_state==_STATE_PASS_ERROR)
			{
				_C_S_GP2 gp2;
				const char * username=((CEdit*)GetUI("用户名"))->GetText();
				const char * userpass=((CEdit*)GetUI("密码"))->GetText();
				strncpy(gp2.uname,username,20);
				strncpy(gp2.upass,userpass,20);
				m_Client->SendData((const char*)&gp2,sizeof(gp2));	
				m_state=_STATE_LJ_MID;
			}
		}
	}
}
//对窗口消息的处理
void CStart::HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CHAR:
		{
			char * editstr[4]={"用户名","密码","服务器","端口"};
			for(int i=0;i<4;i++)
			{
				if(GetUI(editstr[i])->GetAct())
				{
					GetUI(editstr[i])->OnMsg(_UIM_K_CHAR, wParam, lParam);	
					break;
				}
			}
			break;
		}
	}
}