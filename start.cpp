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
	pGO->LoadImg("�����", L"pic\\�����.png");
	pGO->LoadImg("�����", L"pic\\�����.png");
	pGO->LoadImg("��½", L"pic\\��¼��.png");
	pGO->LoadImg("����1", L"pic\\bg1.bmp");
	pGO->LoadImg("����2", L"pic\\bg2.bmp");
	pGO->LoadImg("����3", L"pic\\bg3.bmp");
	pGO->LoadImg("����4", L"pic\\bg4.bmp");
	pGO->LoadImg("��־", L"pic\\logo.bmp");
	pGO->LoadImg("ȷ��1",L"pic\\ȷ��1.bmp");
	pGO->LoadImg("ȷ��2",L"pic\\ȷ��2.bmp");

	m_AutoShow=new CAutoPlay(240,0,0,640,480);
	m_AutoShow->SetLogo("��־",465,0,172,108);
	m_AutoShow->AddPic("����1");
	m_AutoShow->AddPic("����2");
	m_AutoShow->AddPic("����3");
	m_AutoShow->AddPic("����4");

	CGameEngine::GetGE()->GetGO()->LoadFont("��׼",9, 13, 1, false, false ,false, "����");		
	LoadUI("�û���", new CEdit("��׼", RGB(248,232,0), 252, 218, 175, 22));//423
	LoadUI("����", new CEdit("��׼", RGB(248,232,0), 252, 261, 175, 22));
	LoadUI("������", new CEdit("��׼", RGB(248,232,0), 212, 301, 89, 17));
	LoadUI("�˿�", new CEdit("��׼", RGB(248,232,0), 361, 301, 42, 17));
	GetUI("�û���")->SetAct(true);

	//��Ϣ��
	LoadUI("��Ϣ��",new CMsgBox(184,173,271,134));
	GetUI("��Ϣ��")->Init();

	((CEdit*)GetUI("�û���"))->SetText("jack");
	((CEdit*)GetUI("����"))->SetText("123456");
	((CEdit*)GetUI("������"))->SetText("127.0.0.1");
	((CEdit*)GetUI("�˿�"))->SetText("8888");
	LoadUI("ȷ��", new CBmpButton("ȷ��1", "ȷ��2", "ȷ��2", 397,330, 92, 39));
	ShowCursor(FALSE); 
}

void CStart::OutputRun()
{
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	m_AutoShow->Render();
	pGO->DrawImg("��½", 133,150,373,235,0,0,373,235,_MIRROR_NONE, 1);
	GetUI("�û���")->ActRender();	
	GetUI("����")->ActRender();	
	GetUI("������")->ActRender();	
	GetUI("�˿�")->ActRender();	
	if(GetUI("ȷ��")->GetAct())
		GetUI("ȷ��")->ActRender();	
	else
		GetUI("ȷ��")->UnActRender();	
	if(GetUI("��Ϣ��")->GetView())
		GetUI("��Ϣ��")->ActRender();
	switch(m_state)
	{
	case _STATE_LJ_PRE:
		{
			//pGO->DrawStringS("��׼",0,0,"����ǰ",RGB(255,0,0));
			break;
		}
	case _STATE_LJ_MID:
		{
			//pGO->DrawStringS("��׼",0,0,"������",RGB(255,0,0));
			break;
		}
	case _STATE_LJ_ERROR:
		{
			//pGO->DrawStringS("��׼",0,0,"����ʧ��",RGB(255,0,0));
			break;
		}
	case _STATE_PASS_YES:
		{
			//pGO->DrawStringS("��׼",0,0,"��֤�ɹ�",RGB(255,0,0));
			break;
		}
	case _STATE_PASS_NO:
		{
			//pGO->DrawStringS("��׼",0,0,"��֤ʧ��",RGB(255,0,0));
			break;
		}
	case _STATE_PASS_ERROR:
		{
			//pGO->DrawStringS("��׼",0,0,"����������",RGB(255,0,0));
			break;
		}
	case _STATE_PASS_ALREADY:
		{
			//pGO->DrawStringS("��׼",0,0,"���˺��Ѿ���¼",RGB(255,0,0));
			break;
		}
	}
	if(m_curtag)
		pGO->DrawImg("�����", m_x,m_y,40,40,0,0,40,40,_MIRROR_NONE, 1);
	else
		pGO->DrawImg("�����", m_x,m_y,40,40,0,0,40,40,_MIRROR_NONE, 1);
}

void CStart::LogicInputRun()	//������߼�
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
				const char * username=((CEdit*)GetUI("�û���"))->GetText();
				const char * userpass=((CEdit*)GetUI("����"))->GetText();
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
							CGameEngine::GetGE()->SetCurScene("��������");
						}
						else if(gp3->result==_TRY_NO)
						{
							((CMsgBox*)GetUI("��Ϣ��"))->RunText("�û����������",0);
							m_state=_STATE_PASS_NO;
						}
						else if(gp3->result==_TRY_ERROR)
						{
							((CMsgBox*)GetUI("��Ϣ��"))->RunText("����������",0);
							m_state=_STATE_PASS_ERROR;
						}
						else if(gp3->result==_TRY_ALREADY)
						{
							((CMsgBox*)GetUI("��Ϣ��"))->RunText("���˺��Ѿ���¼",0);
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
	//��ȡ�������
	CGameEngine::GetGE()->GetGI()->GetCursor(&m_x, &m_y);
	POINT p = {m_x, m_y};
	//��ȡ��ť����λ��
	RECT r;
	char * editstr[6]={"�û���","����","������","�˿�","ȷ��","��Ϣ��"};
	if(CGameEngine::GetGE()->GetAct())
	{
		for(int i=0;i<6;i++)
		{
			GetUI(editstr[i])->GetRect((int*)&r.left, (int*)&r.top, (int*)&r.right, (int*)&r.bottom);
			r.right += r.left;
			r.bottom += r.top;
			//�жϹ���Ƿ��� ��ť��
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
	if(strcmp(id,"��Ϣ��-ȷ��")==0&&UIMsg==_BUTTON_CLICK)
	{
		GetUI("��Ϣ��")->SetView(false);
	}
	if(strcmp(id,"ȷ��")==0)
	{
		if(UIMsg==_BUTTON_CLICK)
		{
			if(m_state==_STATE_LJ_PRE||m_state==_STATE_LJ_ERROR)
			{
				const char *ip=((CEdit*)GetUI("������"))->GetText();
				const char *portstr=((CEdit*)GetUI("�˿�"))->GetText();
				unsigned short port=atoi(portstr);
				if(m_Client->ConnectByIP(ip,port,5,2,5))
					m_state=_STATE_LJ_MID;
				else
					m_state=_STATE_LJ_ERROR;
			}
			else if(m_state==_STATE_PASS_NO||m_state==_STATE_PASS_ERROR)
			{
				_C_S_GP2 gp2;
				const char * username=((CEdit*)GetUI("�û���"))->GetText();
				const char * userpass=((CEdit*)GetUI("����"))->GetText();
				strncpy(gp2.uname,username,20);
				strncpy(gp2.upass,userpass,20);
				m_Client->SendData((const char*)&gp2,sizeof(gp2));	
				m_state=_STATE_LJ_MID;
			}
		}
	}
}
//�Դ�����Ϣ�Ĵ���
void CStart::HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CHAR:
		{
			char * editstr[4]={"�û���","����","������","�˿�"};
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