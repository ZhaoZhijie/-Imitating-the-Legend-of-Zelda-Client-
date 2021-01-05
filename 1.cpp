#include "1.h"
#include "GameEngine.h"
#include <iostream>
#include <time.h>
#include "Scene.h"
#include "SceneChange.h"
#include "Room.h"
#include "BmpButton.h"
#include "EditRoom.h"
#include "PlayerBox.h"
#include "MsgBox.h"
#include "GameProtocol.h"
#define _SCENE_STATE_HALL 0
#define _SCENE_STATE_CREATE 1
#define _SCENE_STATE_ROOM 2
#define _MSG_SHOW 0
#define _MSG_KICK 1
#define _MSG_NET_ERROR 2
#define PLAYER_STATE_HALL 0		//�ڴ���
#define PLAYER_STATE_UNPRE 1		//�ڷ��� δ׼��
#define PLAYER_STATE_PRE 2			//�ڷ���׼��
#define PLAYER_STATE_ADMIN 3			//�ڷ��䷿��
#define PLAYER_STATE_LOAD 4		//������Ϸ��
#define PLAYER_STATE_WAIT 5		//������ϵȴ���Ϸ��ʼ
#define PLAYER_STATE_GAME 6		//�Ѿ�������Ϸ
void C1::Init()
{
	m_x=0;
	m_y=0;
	m_curtag=false;
	m_state=_SCENE_STATE_HALL;
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	pGO->LoadFont("��������",12, 17, 1, false, false ,false, "����");	
	pGO->LoadImg("����", L"pic\\����.bmp");
	pGO->LoadImg("����1", L"pic\\b1.bmp");
	pGO->LoadImg("����2", L"pic\\b2.bmp");
	pGO->LoadImg("����3", L"pic\\b3.bmp");
	pGO->LoadImg("����4", L"pic\\b4.bmp");
	pGO->LoadImg("�½�����1", L"pic\\�½�����1.png");
	pGO->LoadImg("�½�����2", L"pic\\�½�����2.png");
	pGO->LoadImg("�½�����3", L"pic\\�½�����3.png");
	pGO->LoadImg("���ټ���1", L"pic\\���ټ���1.png");
	pGO->LoadImg("���ټ���2", L"pic\\���ټ���2.png");
	pGO->LoadImg("���ټ���3", L"pic\\���ټ���3.png");
	pGO->LoadImg("ԲȦ��Ь", L"pic\\ԲȦ��Ь.png");
	pGO->LoadImg("��ť��ʼ1", L"pic\\��ť��ʼ1.png");
	pGO->LoadImg("��ť��ʼ2", L"pic\\��ť��ʼ2.png");
	pGO->LoadImg("��ť׼��1", L"pic\\��ť׼��1.png");
	pGO->LoadImg("��ť׼��2", L"pic\\��ť׼��2.png");
	pGO->LoadImg("��ťȡ��1", L"pic\\��ťȡ��1.png");
	pGO->LoadImg("��ťȡ��2", L"pic\\��ťȡ��2.png");
	pGO->LoadImg("��ť����1", L"pic\\��ť����1.png");
	pGO->LoadImg("��ť����2", L"pic\\��ť����2.png");
	pGO->LoadImg("��ǰ����0", L"pic\\0_2.png");
	pGO->LoadImg("��ǰ����1", L"pic\\1_2.png");
	pGO->LoadImg("��ǰ����2", L"pic\\2_2.png");
	pGO->LoadImg("��ǰ״̬1", L"pic\\�豭.png");
	m_AutoShow=new CAutoPlay(240,31,163,161,261);
	m_AutoShow->AddPic("����1");
	m_AutoShow->AddPic("����2");
	m_AutoShow->AddPic("����3");
	m_AutoShow->AddPic("����4");

	//���UI��ҪInit
	LoadUI("������",new CEditRoom(202,183,236,113));
	GetUI("������")->Init();

	//��Ϣ��
	LoadUI("��Ϣ��",new CMsgBox(184,173,271,134));
	GetUI("��Ϣ��")->Init();

	//��ʼ ׼�� ȡ�� ���˰�ť
	LoadUI("��ť��ʼ",new CBmpButton("��ť��ʼ1", "��ť��ʼ2", "��ť��ʼ2", 321,182,95,67));
	LoadUI("��ť׼��",new CBmpButton("��ť׼��1", "��ť׼��2", "��ť׼��2", 321,182,95,67));
	LoadUI("��ťȡ��",new CBmpButton("��ťȡ��1", "��ťȡ��2", "��ťȡ��2", 321,182,95,67));
	LoadUI("��ť����",new CBmpButton("��ť����1", "��ť����2", "��ť����2", 488,182,95,67));

	//���ټ�����½����䰴ť
	LoadUI("�½�����",new CBmpButton("�½�����1", "�½�����2", "�½�����3", 241,157,125,27));
	LoadUI("���ټ���",new CBmpButton("���ټ���1", "���ټ���2", "���ټ���3", 445,157,125,57));

	//������Һ���
	LoadUI("�����",new CPlayerBox(259,257,131,167));
	LoadUI("�����",new CPlayerBox(460,257,131,167));

	//�ĸ��������
	LoadUI("����1",new CRoom(215,242,200,81));
	LoadUI("����2",new CRoom(424,242,200,81));
	LoadUI("����3",new CRoom(215,330,200,81));
	LoadUI("����4",new CRoom(424,330,200,81));
	ShowCursor(FALSE);
}

void C1::OutputRun()
{
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	pGO->DrawImg("����",0,0,640,480,0,0,640,480);
	m_AutoShow->Render();

	if(m_state==_SCENE_STATE_HALL||m_state==_SCENE_STATE_CREATE)
	{
		GetUI("�½�����")->ActRender();
		GetUI("���ټ���")->ActRender();
		char *uiname[4]={"����1","����2","����3","����4"};
		for(int i=0;i<4;i++)
		{
			CRoom* tmpRoom=((CRoom*)GetUI(uiname[i]));
			if(tmpRoom->GetView())
				tmpRoom->ActRender();
		}
		if(m_state==_SCENE_STATE_CREATE)
			GetUI("������")->ActRender();
	}
	else if(m_state==_SCENE_STATE_ROOM)
	{
		pGO->DrawImg("ԲȦ��Ь",212,122,105,115);
		pGO->DrawStringS("��������",360,150,m_RName.c_str(),RGB(221,228,31));
		//pGO->DrawStringS("������",360,150,"����ɭ��",RGB(255,255,0));
		if(m_num==1)
			pGO->DrawImg("��ǰ����1",504,150,36,20);
		else
			pGO->DrawImg("��ǰ����2",504,150,36,20);
		
		pGO->DrawImg("��ǰ״̬1",566,135,29,34);
		if(m_Owner._state==PLAYER_STATE_ADMIN)
			GetUI("��ť��ʼ")->ActRender();
		else
			GetUI("��ť׼��")->ActRender();
		GetUI("��ť����")->ActRender();
		GetUI("�����")->ActRender();
		GetUI("�����")->ActRender();
	}
	if(GetUI("��Ϣ��")->GetView())
		GetUI("��Ϣ��")->ActRender();
	if(m_curtag)
		pGO->DrawImg("�����", m_x,m_y,40,40,0,0,40,40,_MIRROR_NONE, 1);
	else
		pGO->DrawImg("�����", m_x,m_y,40,40,0,0,40,40,_MIRROR_NONE, 1);
}

void C1::LogicInputRun()
{
	//���������¼�
	CTcpClient * pClient=CGameEngine::GetGE()->GetClient();
	pClient->Run();
	_TC_NET_EVENT evt;
	while(pClient->GetTCNetEvent(&evt))
	{
		switch(evt.type)
		{
			case _TCNE_S_DISCONNECT:
			case _TCNE_C_DISCONNECT:
			case _TCNE_E_DISCONNECT:
				{
					((CMsgBox*)GetUI("��Ϣ��"))->RunText("������������µ�½",_MSG_NET_ERROR);
					break;
				}
			case _TCNE_DATA:	
				{
					_GAME_PROTOCOL * gp=(_GAME_PROTOCOL *)evt.data;
					switch(gp->id)
					{	
					case _ROOM_DATA:
						{
							_S_C_GP4 *gp4=(_S_C_GP4 *)evt.data;
							RoomData rd;
							strcpy(rd._name,gp4->name);
							rd._num=gp4->num;
							rd._tag=gp4->tag;
							rd._type=gp4->type;
							m_Room.Insert(gp4->no,rd);
							break;
						}
					case _CREATE_RESULT:
						{
							_S_C_GP7 *gp7=(_S_C_GP7 *)evt.data;
							if(gp7->result)
							{
								m_num=1;
								m_state=_SCENE_STATE_ROOM;
								m_Owner._order=0;
								m_Owner._uid="�����";
								m_Owner._state=PLAYER_STATE_ADMIN;
								((CPlayerBox*)GetUI("�����"))->Enter(m_Owner._name,"��ñ��");
								((CPlayerBox*)GetUI("�����"))->SetState(_PBOX_ADMIN);
							}
							else
								((CMsgBox*)GetUI("��Ϣ��"))->RunText("��������ʧ�ܣ��������ﵽ���ޣ�", _MSG_SHOW);
							break;
						}
					case _CUR_ROOM:
						{
							_S_C_GP12 *gp12=(_S_C_GP12 *)evt.data;
							m_RName=gp12->_name;
							m_no=gp12->_no;
							m_type=gp12->_type;
							break;
						}
					case _PLAYER_DATA:
						{//������һ����ҵ���Ϣ
							m_num=2;
							_S_C_GP9 * gp9=(_S_C_GP9 * )evt.data;
							strcpy(m_Mate._name,gp9->_name);
							m_Mate._order=gp9->_order;
							m_Mate._state=gp9->_state;
							SetWindowTextA(CGameEngine::GetGE()->GetWnd(),gp9->_name);
							m_Mate._uid=m_Mate._order==0?"�����":"�����";
							if(m_Owner._state==PLAYER_STATE_HALL)
							{
								m_Owner._order=(gp9->_order+1)%2;
								m_Owner._uid=m_Owner._order==0?"�����":"�����";
								m_Owner._state=PLAYER_STATE_UNPRE;
								m_state=_SCENE_STATE_ROOM;
								((CPlayerBox*)GetUI(m_Owner._uid.c_str()))->Enter(m_Owner._name,"��ñ��");
								((CPlayerBox*)GetUI(m_Owner._uid.c_str()))->SetState(_PBOX_UNPRE);
							}

							CPlayerBox* matebox=((CPlayerBox*)GetUI(m_Mate._uid.c_str()));
							matebox->Enter(m_Mate._name,"��ñ��");
							if(m_Mate._state==PLAYER_STATE_ADMIN)
								matebox->SetState(_PBOX_ADMIN);
							else
								matebox->SetState(_PBOX_UNPRE);
							break;
						}
					case _OWNER_DATA:
						{
							_S_C_GP11 * gp11=(_S_C_GP11 *)evt.data;
							strcpy(m_Owner._name,gp11->_name);
							m_Owner._order=-1;
							m_Owner._state=PLAYER_STATE_HALL;
							break;
						}
					case _EROOM_RESULT:
						{
							//_S_C_GP10 * gp10=(_S_C_GP10 *)evt.data;
							//if(!gp10->result)
							//	((CMsgBox*)GetUI("��Ϣ��"))->RunText("�÷�����������", _MSG_SHOW);
							break;
						}
					case _ENTER_GAME:
						{
							CGameEngine::GetGE()->SetCurScene("��Ϸ����");
						}
					case _PRE_CLICK_RESULT:
						{
							_S_C_GP14 * gp14=(_S_C_GP14 *)evt.data;
							PlayerData * pdata[2]={&m_Owner,&m_Mate};
							for(int i=0;i<2;i++)
							{
								if(strcmp(gp14->_name,pdata[i]->_name)==0)
								{
									pdata[i]->_state=gp14->_state;
									CPlayerBox* box=(CPlayerBox*)GetUI(pdata[i]->_uid.c_str());
									if(pdata[i]->_state==PLAYER_STATE_UNPRE)
										box->SetState(_PBOX_UNPRE);
									else if(pdata[i]->_state==PLAYER_STATE_PRE)
										box->SetState(_PBOX_PRE);
									else if(pdata[i]->_state==PLAYER_STATE_ADMIN)
										box->SetState(_PBOX_ADMIN);
									break;
								}
							}
							break;
						}
					case _H_QUIT:
						{
							_S_C_GP16 * gp16=(_S_C_GP16 *)evt.data;
							m_num--;
							((CPlayerBox*)GetUI(m_Mate._uid.c_str()))->SetState(_PBOX_NULL);
							break;
						}
					case _ROOM_DEL:
						{
							_S_C_GP17 * gp17=(_S_C_GP17 *)evt.data;
							m_Room.Erase((short)gp17->no);
							break;
						}
					}
					pClient->ReleaseTSNetEvent(&evt);
				}
		}
	}
	if(!CGameEngine::GetGE()->GetAct())
		return;
	if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_RETURN)==_KS_DC)
		CGameEngine::GetGE()->SetCurScene("��¼����");
	if(CGameEngine::GetGE()->GetGI()->Get(_GI_M_L) == _KS_DC||CGameEngine::GetGE()->GetGI()->Get(_GI_M_L) == _KS_DH)
		m_curtag=true;
	else
		m_curtag=false;
	char *uiname[4]={"����1","����2","����3","����4"};
	for(int i=0;i<4;i++)
		((CRoom*)GetUI(uiname[i]))->SetView(false);
	for(int i=0;i<m_Room.Length();i++)
	{
		if(i>3)
			break;
		CMap<short,RoomData>::PAIR* rp=m_Room.At(i);
		((CRoom*)GetUI(uiname[i]))->SetData(rp->data._type, rp->key, rp->data._name, rp->data._num, rp->data._tag);
		((CRoom*)GetUI(uiname[i]))->SetView(true);
	}
	//���ݲ�ͬ״ֵ̬����UI
	std::string uid[20];
	int len=0;
	if(GetUI("��Ϣ��")->GetView())
	{
		uid[0]="��Ϣ��";
		len=1;	
	}
	else if(m_state==_SCENE_STATE_CREATE)
	{
		uid[0]="������";
		len=1;
		if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_LEFT)==_KS_DC)
			GetUI("������")->OnMsg(_UIM_K_CHAR, 37, 0);
		if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_RIGHT)==_KS_DC)
			GetUI("������")->OnMsg(_UIM_K_CHAR, 39, 0);
	}
	else if(m_state==_SCENE_STATE_HALL)
	{
		uid[0]="�½�����";
		uid[1]="���ټ���";
		uid[2]="����1";
		uid[3]="����2";
		uid[4]="����3";
		uid[5]="����4";
		len =6;
		for(int i=5;i>1;i--)
		{
			if(!GetUI(uid[i].c_str())->GetView())
				len--;
		}
	}
	else if(m_state==_SCENE_STATE_ROOM)
	{
		uid[0]=m_Owner._state==PLAYER_STATE_ADMIN?"��ť��ʼ":"��ť׼��";
		uid[1]="��ť����";
		uid[2]="�����";
		uid[3]="�����";
		len=4;
	}
	//��ȡ�������
	CGameEngine::GetGE()->GetGI()->GetCursor(&m_x, &m_y);
	POINT p = {m_x, m_y};
	//��ȡ��ť����λ��
	RECT r;
	for(int i=0;i<len;i++)
	{
		GetUI(uid[i].c_str())->GetRect((int*)&r.left, (int*)&r.top, (int*)&r.right, (int*)&r.bottom);
		r.right += r.left;
		r.bottom += r.top;
		if(PtInRect(&r, p))
		{
			if(CGameEngine::GetGE()->GetGI()->Get(_GI_M_L) == _KS_DC)
			{
				GetUI(uid[i].c_str())->OnMsg(_UIM_C_LBD_IN, p.x, p.y);
				GetUI(uid[i].c_str())->SetAct(true);
			}
			else if(CGameEngine::GetGE()->GetGI()->Get(_GI_M_L) == _KS_UC)
			{
				GetUI(uid[i].c_str())->OnMsg(_UIM_C_LBU_IN, p.x, p.y);
			}
			else if(CGameEngine::GetGE()->GetGI()->Get(_GI_M_L) == _KS_UH)
			{
				GetUI(uid[i].c_str())->OnMsg(_UIM_C_ENTER, p.x, p.y);
			}
		}
		else
		{
			GetUI(uid[i].c_str())->OnMsg(_UIM_C_QUIT, p.x, p.y);
			if(CGameEngine::GetGE()->GetGI()->Get(_GI_M_L) == _KS_DC)
			{
				GetUI(uid[i].c_str())->OnMsg(_UIM_C_LBD_OUT, p.x, p.y);
				GetUI(uid[i].c_str())->SetAct(false);
			}
		}	
	}
}
void C1::OnUIMsg(const char* id, int UIMsg)
{
	CTcpClient *pClient=CGameEngine::GetGE()->GetClient();
	if(strcmp(id,"�½�����")==0&&UIMsg==_BUTTON_CLICK)
	{
		m_state=_SCENE_STATE_CREATE;
		GetUI("������")->SetAct(true);
	}
	if((strcmp(id,"����1")==0||strcmp(id,"����2")==0||strcmp(id,"����3")==0||strcmp(id,"����4")==0)
		&&UIMsg==_ROOM_CLICK)
	{
		if(((CRoom*)GetUI(id))->GetNum()<2)
		{
			_C_S_GP8 gp8;
			gp8.no=((CRoom*)GetUI(id))->GetNo();
			pClient->SendData((const char*)&gp8,sizeof(gp8));	
		}
	}
	if(strcmp(id,"��Ϣ��-ȷ��")==0&&UIMsg==_BUTTON_CLICK)
	{
		GetUI("��Ϣ��")->SetView(false);
		switch(((CMsgBox*)GetUI("��Ϣ��"))->GetCode())
		{
		case _MSG_SHOW:
			{
				break;
			}
		}
	}
	if(strcmp(id,"��Ϣ��-ȡ��")==0&&UIMsg==_BUTTON_CLICK)
	{
		GetUI("��Ϣ��")->SetView(false);
	}
	if(strcmp(id,"������-ȷ��")==0&&UIMsg==_BUTTON_CLICK)
	{
		GetUI("������")->SetAct(false);
		_C_S_GP6 gp6;
		strcpy(gp6.name,((CEditRoom*)GetUI("������"))->GetText());
		pClient->SendData((const char*)&gp6,sizeof(gp6));	
		//m_state=_SCENE_STATE_ROOM;
	}
	if(strcmp(id,"������-ȡ��")==0&&UIMsg==_BUTTON_CLICK)//��ť׼��
	{
		GetUI("������")->SetAct(false);
		m_state=_SCENE_STATE_HALL;
	}
	if(strcmp(id,"��ť׼��")==0&&UIMsg==_BUTTON_CLICK)
	{
		_C_S_GP13 gp13;
		gp13._no=m_no;
		pClient->SendData((const char*)&gp13,sizeof(gp13));
	}
	if(strcmp(id,"��ť��ʼ")==0&&UIMsg==_BUTTON_CLICK)
	{
		if(m_num==2&&m_Mate._state==PLAYER_STATE_PRE)
		{
			_C_S_GP20 gp20;
			gp20._no=m_no;
			pClient->SendData((const char*)&gp20,sizeof(gp20));
		}
	}
	if(strcmp(id,"�����")==0&&UIMsg==_PLAYER_CLICK)
	{
		((CMsgBox*)GetUI("��Ϣ��"))->RunText("ȷ��Ҫ�߳��������", _MSG_KICK);
	}
	if(strcmp(id,"��ť����")==0&&UIMsg==_BUTTON_CLICK )
	{
		m_state=_SCENE_STATE_HALL;
		_C_S_GP15 gp15;
		m_Room.Clear();
		gp15._no=m_no;
		pClient->SendData((const char*)&gp15,sizeof(gp15));//�˳�����	
		_C_S_GP5 gp5;
		pClient->SendData((const char*)&gp5,sizeof(gp5));	//�������
		m_Owner._state=PLAYER_STATE_HALL;
		((CPlayerBox*)GetUI("�����"))->SetState(_PBOX_NULL);
		((CPlayerBox*)GetUI("�����"))->SetState(_PBOX_NULL);
	}
}

//�Դ�����Ϣ�Ĵ���
void C1::HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CHAR:
		{
			if(m_state==_SCENE_STATE_CREATE&&GetUI("������")->GetAct())
				GetUI("������")->OnMsg(_UIM_K_CHAR, wParam, lParam);	
			break;
		}
	}
}

void C1::Enter()
{
	//��֪�������ѽ��볡�������󴫵ݳ�������
	_C_S_GP5 gp5;
	CGameEngine::GetGE()->GetClient()->SendData((const char*)&gp5,sizeof(gp5));	
}
void C1::Quit()
{
	
}
