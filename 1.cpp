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
#define PLAYER_STATE_HALL 0		//在大厅
#define PLAYER_STATE_UNPRE 1		//在房间 未准备
#define PLAYER_STATE_PRE 2			//在房间准备
#define PLAYER_STATE_ADMIN 3			//在房间房主
#define PLAYER_STATE_LOAD 4		//加载游戏中
#define PLAYER_STATE_WAIT 5		//加载完毕等待游戏开始
#define PLAYER_STATE_GAME 6		//已经进入游戏
void C1::Init()
{
	m_x=0;
	m_y=0;
	m_curtag=false;
	m_state=_SCENE_STATE_HALL;
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	pGO->LoadFont("房间名称",12, 17, 1, false, false ,false, "楷体");	
	pGO->LoadImg("大厅", L"pic\\大厅.bmp");
	pGO->LoadImg("画面1", L"pic\\b1.bmp");
	pGO->LoadImg("画面2", L"pic\\b2.bmp");
	pGO->LoadImg("画面3", L"pic\\b3.bmp");
	pGO->LoadImg("画面4", L"pic\\b4.bmp");
	pGO->LoadImg("新建房间1", L"pic\\新建房间1.png");
	pGO->LoadImg("新建房间2", L"pic\\新建房间2.png");
	pGO->LoadImg("新建房间3", L"pic\\新建房间3.png");
	pGO->LoadImg("快速加入1", L"pic\\快速加入1.png");
	pGO->LoadImg("快速加入2", L"pic\\快速加入2.png");
	pGO->LoadImg("快速加入3", L"pic\\快速加入3.png");
	pGO->LoadImg("圆圈飞鞋", L"pic\\圆圈飞鞋.png");
	pGO->LoadImg("按钮开始1", L"pic\\按钮开始1.png");
	pGO->LoadImg("按钮开始2", L"pic\\按钮开始2.png");
	pGO->LoadImg("按钮准备1", L"pic\\按钮准备1.png");
	pGO->LoadImg("按钮准备2", L"pic\\按钮准备2.png");
	pGO->LoadImg("按钮取消1", L"pic\\按钮取消1.png");
	pGO->LoadImg("按钮取消2", L"pic\\按钮取消2.png");
	pGO->LoadImg("按钮后退1", L"pic\\按钮后退1.png");
	pGO->LoadImg("按钮后退2", L"pic\\按钮后退2.png");
	pGO->LoadImg("当前人数0", L"pic\\0_2.png");
	pGO->LoadImg("当前人数1", L"pic\\1_2.png");
	pGO->LoadImg("当前人数2", L"pic\\2_2.png");
	pGO->LoadImg("当前状态1", L"pic\\茶杯.png");
	m_AutoShow=new CAutoPlay(240,31,163,161,261);
	m_AutoShow->AddPic("画面1");
	m_AutoShow->AddPic("画面2");
	m_AutoShow->AddPic("画面3");
	m_AutoShow->AddPic("画面4");

	//组合UI都要Init
	LoadUI("建房框",new CEditRoom(202,183,236,113));
	GetUI("建房框")->Init();

	//消息框
	LoadUI("消息框",new CMsgBox(184,173,271,134));
	GetUI("消息框")->Init();

	//开始 准备 取消 后退按钮
	LoadUI("按钮开始",new CBmpButton("按钮开始1", "按钮开始2", "按钮开始2", 321,182,95,67));
	LoadUI("按钮准备",new CBmpButton("按钮准备1", "按钮准备2", "按钮准备2", 321,182,95,67));
	LoadUI("按钮取消",new CBmpButton("按钮取消1", "按钮取消2", "按钮取消2", 321,182,95,67));
	LoadUI("按钮后退",new CBmpButton("按钮后退1", "按钮后退2", "按钮后退2", 488,182,95,67));

	//快速加入和新建房间按钮
	LoadUI("新建房间",new CBmpButton("新建房间1", "新建房间2", "新建房间3", 241,157,125,27));
	LoadUI("快速加入",new CBmpButton("快速加入1", "快速加入2", "快速加入3", 445,157,125,57));

	//两个玩家盒子
	LoadUI("玩家左",new CPlayerBox(259,257,131,167));
	LoadUI("玩家右",new CPlayerBox(460,257,131,167));

	//四个房间盒子
	LoadUI("盒子1",new CRoom(215,242,200,81));
	LoadUI("盒子2",new CRoom(424,242,200,81));
	LoadUI("盒子3",new CRoom(215,330,200,81));
	LoadUI("盒子4",new CRoom(424,330,200,81));
	ShowCursor(FALSE);
}

void C1::OutputRun()
{
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	pGO->DrawImg("大厅",0,0,640,480,0,0,640,480);
	m_AutoShow->Render();

	if(m_state==_SCENE_STATE_HALL||m_state==_SCENE_STATE_CREATE)
	{
		GetUI("新建房间")->ActRender();
		GetUI("快速加入")->ActRender();
		char *uiname[4]={"盒子1","盒子2","盒子3","盒子4"};
		for(int i=0;i<4;i++)
		{
			CRoom* tmpRoom=((CRoom*)GetUI(uiname[i]));
			if(tmpRoom->GetView())
				tmpRoom->ActRender();
		}
		if(m_state==_SCENE_STATE_CREATE)
			GetUI("建房框")->ActRender();
	}
	else if(m_state==_SCENE_STATE_ROOM)
	{
		pGO->DrawImg("圆圈飞鞋",212,122,105,115);
		pGO->DrawStringS("房间名称",360,150,m_RName.c_str(),RGB(221,228,31));
		//pGO->DrawStringS("房间编号",360,150,"神奇森林",RGB(255,255,0));
		if(m_num==1)
			pGO->DrawImg("当前人数1",504,150,36,20);
		else
			pGO->DrawImg("当前人数2",504,150,36,20);
		
		pGO->DrawImg("当前状态1",566,135,29,34);
		if(m_Owner._state==PLAYER_STATE_ADMIN)
			GetUI("按钮开始")->ActRender();
		else
			GetUI("按钮准备")->ActRender();
		GetUI("按钮后退")->ActRender();
		GetUI("玩家左")->ActRender();
		GetUI("玩家右")->ActRender();
	}
	if(GetUI("消息框")->GetView())
		GetUI("消息框")->ActRender();
	if(m_curtag)
		pGO->DrawImg("鼠标下", m_x,m_y,40,40,0,0,40,40,_MIRROR_NONE, 1);
	else
		pGO->DrawImg("鼠标上", m_x,m_y,40,40,0,0,40,40,_MIRROR_NONE, 1);
}

void C1::LogicInputRun()
{
	//处理网络事件
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
					((CMsgBox*)GetUI("消息框"))->RunText("网络错误，请重新登陆",_MSG_NET_ERROR);
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
								m_Owner._uid="玩家左";
								m_Owner._state=PLAYER_STATE_ADMIN;
								((CPlayerBox*)GetUI("玩家左"))->Enter(m_Owner._name,"白帽子");
								((CPlayerBox*)GetUI("玩家左"))->SetState(_PBOX_ADMIN);
							}
							else
								((CMsgBox*)GetUI("消息框"))->RunText("创建房间失败，房间数达到上限！", _MSG_SHOW);
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
						{//房间另一个玩家的信息
							m_num=2;
							_S_C_GP9 * gp9=(_S_C_GP9 * )evt.data;
							strcpy(m_Mate._name,gp9->_name);
							m_Mate._order=gp9->_order;
							m_Mate._state=gp9->_state;
							SetWindowTextA(CGameEngine::GetGE()->GetWnd(),gp9->_name);
							m_Mate._uid=m_Mate._order==0?"玩家左":"玩家右";
							if(m_Owner._state==PLAYER_STATE_HALL)
							{
								m_Owner._order=(gp9->_order+1)%2;
								m_Owner._uid=m_Owner._order==0?"玩家左":"玩家右";
								m_Owner._state=PLAYER_STATE_UNPRE;
								m_state=_SCENE_STATE_ROOM;
								((CPlayerBox*)GetUI(m_Owner._uid.c_str()))->Enter(m_Owner._name,"疯帽子");
								((CPlayerBox*)GetUI(m_Owner._uid.c_str()))->SetState(_PBOX_UNPRE);
							}

							CPlayerBox* matebox=((CPlayerBox*)GetUI(m_Mate._uid.c_str()));
							matebox->Enter(m_Mate._name,"疯帽子");
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
							//	((CMsgBox*)GetUI("消息框"))->RunText("该房间人已满！", _MSG_SHOW);
							break;
						}
					case _ENTER_GAME:
						{
							CGameEngine::GetGE()->SetCurScene("游戏场景");
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
		CGameEngine::GetGE()->SetCurScene("登录场景");
	if(CGameEngine::GetGE()->GetGI()->Get(_GI_M_L) == _KS_DC||CGameEngine::GetGE()->GetGI()->Get(_GI_M_L) == _KS_DH)
		m_curtag=true;
	else
		m_curtag=false;
	char *uiname[4]={"盒子1","盒子2","盒子3","盒子4"};
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
	//根据不同状态值遍历UI
	std::string uid[20];
	int len=0;
	if(GetUI("消息框")->GetView())
	{
		uid[0]="消息框";
		len=1;	
	}
	else if(m_state==_SCENE_STATE_CREATE)
	{
		uid[0]="建房框";
		len=1;
		if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_LEFT)==_KS_DC)
			GetUI("建房框")->OnMsg(_UIM_K_CHAR, 37, 0);
		if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_RIGHT)==_KS_DC)
			GetUI("建房框")->OnMsg(_UIM_K_CHAR, 39, 0);
	}
	else if(m_state==_SCENE_STATE_HALL)
	{
		uid[0]="新建房间";
		uid[1]="快速加入";
		uid[2]="盒子1";
		uid[3]="盒子2";
		uid[4]="盒子3";
		uid[5]="盒子4";
		len =6;
		for(int i=5;i>1;i--)
		{
			if(!GetUI(uid[i].c_str())->GetView())
				len--;
		}
	}
	else if(m_state==_SCENE_STATE_ROOM)
	{
		uid[0]=m_Owner._state==PLAYER_STATE_ADMIN?"按钮开始":"按钮准备";
		uid[1]="按钮后退";
		uid[2]="玩家左";
		uid[3]="玩家右";
		len=4;
	}
	//获取光标坐标
	CGameEngine::GetGE()->GetGI()->GetCursor(&m_x, &m_y);
	POINT p = {m_x, m_y};
	//获取按钮矩形位置
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
	if(strcmp(id,"新建房间")==0&&UIMsg==_BUTTON_CLICK)
	{
		m_state=_SCENE_STATE_CREATE;
		GetUI("建房框")->SetAct(true);
	}
	if((strcmp(id,"盒子1")==0||strcmp(id,"盒子2")==0||strcmp(id,"盒子3")==0||strcmp(id,"盒子4")==0)
		&&UIMsg==_ROOM_CLICK)
	{
		if(((CRoom*)GetUI(id))->GetNum()<2)
		{
			_C_S_GP8 gp8;
			gp8.no=((CRoom*)GetUI(id))->GetNo();
			pClient->SendData((const char*)&gp8,sizeof(gp8));	
		}
	}
	if(strcmp(id,"消息框-确定")==0&&UIMsg==_BUTTON_CLICK)
	{
		GetUI("消息框")->SetView(false);
		switch(((CMsgBox*)GetUI("消息框"))->GetCode())
		{
		case _MSG_SHOW:
			{
				break;
			}
		}
	}
	if(strcmp(id,"消息框-取消")==0&&UIMsg==_BUTTON_CLICK)
	{
		GetUI("消息框")->SetView(false);
	}
	if(strcmp(id,"建房框-确定")==0&&UIMsg==_BUTTON_CLICK)
	{
		GetUI("建房框")->SetAct(false);
		_C_S_GP6 gp6;
		strcpy(gp6.name,((CEditRoom*)GetUI("建房框"))->GetText());
		pClient->SendData((const char*)&gp6,sizeof(gp6));	
		//m_state=_SCENE_STATE_ROOM;
	}
	if(strcmp(id,"建房框-取消")==0&&UIMsg==_BUTTON_CLICK)//按钮准备
	{
		GetUI("建房框")->SetAct(false);
		m_state=_SCENE_STATE_HALL;
	}
	if(strcmp(id,"按钮准备")==0&&UIMsg==_BUTTON_CLICK)
	{
		_C_S_GP13 gp13;
		gp13._no=m_no;
		pClient->SendData((const char*)&gp13,sizeof(gp13));
	}
	if(strcmp(id,"按钮开始")==0&&UIMsg==_BUTTON_CLICK)
	{
		if(m_num==2&&m_Mate._state==PLAYER_STATE_PRE)
		{
			_C_S_GP20 gp20;
			gp20._no=m_no;
			pClient->SendData((const char*)&gp20,sizeof(gp20));
		}
	}
	if(strcmp(id,"玩家左")==0&&UIMsg==_PLAYER_CLICK)
	{
		((CMsgBox*)GetUI("消息框"))->RunText("确定要踢出该玩家吗？", _MSG_KICK);
	}
	if(strcmp(id,"按钮后退")==0&&UIMsg==_BUTTON_CLICK )
	{
		m_state=_SCENE_STATE_HALL;
		_C_S_GP15 gp15;
		m_Room.Clear();
		gp15._no=m_no;
		pClient->SendData((const char*)&gp15,sizeof(gp15));//退出房间	
		_C_S_GP5 gp5;
		pClient->SendData((const char*)&gp5,sizeof(gp5));	//进入大厅
		m_Owner._state=PLAYER_STATE_HALL;
		((CPlayerBox*)GetUI("玩家左"))->SetState(_PBOX_NULL);
		((CPlayerBox*)GetUI("玩家右"))->SetState(_PBOX_NULL);
	}
}

//对窗口消息的处理
void C1::HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CHAR:
		{
			if(m_state==_SCENE_STATE_CREATE&&GetUI("建房框")->GetAct())
				GetUI("建房框")->OnMsg(_UIM_K_CHAR, wParam, lParam);	
			break;
		}
	}
}

void C1::Enter()
{
	//告知服务器已进入场景，请求传递场景数据
	_C_S_GP5 gp5;
	CGameEngine::GetGE()->GetClient()->SendData((const char*)&gp5,sizeof(gp5));	
}
void C1::Quit()
{
	
}
