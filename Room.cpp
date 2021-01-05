#include "Room.h"
#include "Scene.h"
#include "GameEngine.h"
#define _STATE_CURSOR_OUT 0		//鼠标在控件外部
#define _STATE_CURSOR_IN_UP 1	//鼠标在控件内部，没有按下
#define _STATE_CURSOR_IN_DOWN 2	//鼠标在控件内部，按下
#define _STATE_UNACT 3			//控件不可用
CRoom::CRoom(int x, int y, int w, int h, bool View, bool Act)
	:CUI(x, y, w, h, View, Act)
{
	m_sign=_MAP_RAND;//地图标志
	m_no=1;//房间编号
	m_num=0;//房间人数
	m_str="神奇帽子";
	m_state=_STATE_CURSOR_OUT;//控件状态
	m_in=false;
	m_tag=ROOM_STATE_WAIT;//游戏开始 准备 状态标志
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	CGameEngine::GetGE()->GetGO()->LoadFont("房间名",9, 13, 1, false, false ,false, "楷体");
	pGO->LoadImg("房间1",L"pic\\房间盒子1.png");
	pGO->LoadImg("房间2",L"pic\\房间盒子2.png");
	pGO->LoadImg("房间3",L"pic\\房间盒子3.png");
	pGO->LoadImg("地图1",L"pic\\飞鞋.png");
	pGO->LoadImg("地图2",L"pic\\磁铁.png");
	pGO->LoadImg("地图3",L"pic\\翅膀.png");
	pGO->LoadImg("地图4",L"pic\\问号.png");
	pGO->LoadImg("数字1",L"pic\\01.png");
	pGO->LoadImg("数字2",L"pic\\02.png");
	pGO->LoadImg("数字3",L"pic\\03.png");
	pGO->LoadImg("数字4",L"pic\\04.png");
	pGO->LoadImg("0_2",L"pic\\0_2.png");
	pGO->LoadImg("1_2",L"pic\\1_2.png");
	pGO->LoadImg("2_2",L"pic\\2_2.png");
	pGO->LoadImg("游戏状态1",L"pic\\茶杯.png");
}
//设置显示数据
void CRoom::SetData(int sign, int no,const char * str,int num ,int tag)
{
	m_sign=sign;
	m_no=no;
	m_str=str;
	m_num=num;
	m_tag=tag;
}
//获取房间编号
int CRoom::GetNo()
{
	return m_no;
}
//获取房间人数
int CRoom::GetNum()
{
	return m_num;
}
//初始化
void CRoom::ActRender()
{
	//获取显示设备
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	char buf[15];//拼装字符用
	if(m_state!=3)
	{
		sprintf(buf,"房间%d",m_state+1);
		pGO->DrawImg(buf,m_X,m_Y,200,81);
	}
	sprintf(buf,"数字%d",m_no);//215 242
	pGO->DrawImg(buf,m_X+81,m_Y+6,18,19);
	sprintf(buf,"地图%d",m_sign);//215 242   373 265
	pGO->DrawImg(buf,m_X+4,m_Y+2,51,57);
	pGO->DrawStringS("房间名",m_X+106,m_Y+7,m_str.c_str(),RGB(248,232,0));
	sprintf(buf,"%d_2",m_num);
	pGO->DrawImg(buf,m_X+101,m_Y+46,36,20);
	sprintf(buf,"游戏状态%d",m_tag);
	pGO->DrawImg(buf,m_X+158,m_Y+33,29,34);
}
//非激活渲染
void CRoom::UnActRender()
{}
//获取消息
//如果是光标类消息: p1为 x坐标 p2 为 y坐标(相对控件的矩形)
//如果是键盘消息: p1为传入的键值
//如果是字符消息: p1为传入的字符, p2表示是否为双字节（1为是 0为否）
void CRoom::OnMsg(int msg, int p1, int p2)
{
	switch(msg)
	{
	case _UIM_C_ENTER: 
		{
			m_in = true; 
			m_state = _STATE_CURSOR_IN_UP;
			break;
		}
	case _UIM_C_QUIT: 
		{
			m_state = _STATE_CURSOR_OUT;
			m_in = false; 
			break;
		}
	case _UIM_C_LBD_IN: 
		{
			m_Scene->OnUIMsg(m_Name.c_str(), _ROOM_CLICK);
			m_state = _STATE_CURSOR_IN_DOWN;
			break;
		}
	case _UIM_C_LBU_IN:
		{
			m_state = _STATE_CURSOR_IN_UP;
			break;			
		}
	}
}