#include "Room.h"
#include "Scene.h"
#include "GameEngine.h"
#define _STATE_CURSOR_OUT 0		//����ڿؼ��ⲿ
#define _STATE_CURSOR_IN_UP 1	//����ڿؼ��ڲ���û�а���
#define _STATE_CURSOR_IN_DOWN 2	//����ڿؼ��ڲ�������
#define _STATE_UNACT 3			//�ؼ�������
CRoom::CRoom(int x, int y, int w, int h, bool View, bool Act)
	:CUI(x, y, w, h, View, Act)
{
	m_sign=_MAP_RAND;//��ͼ��־
	m_no=1;//������
	m_num=0;//��������
	m_str="����ñ��";
	m_state=_STATE_CURSOR_OUT;//�ؼ�״̬
	m_in=false;
	m_tag=ROOM_STATE_WAIT;//��Ϸ��ʼ ׼�� ״̬��־
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	CGameEngine::GetGE()->GetGO()->LoadFont("������",9, 13, 1, false, false ,false, "����");
	pGO->LoadImg("����1",L"pic\\�������1.png");
	pGO->LoadImg("����2",L"pic\\�������2.png");
	pGO->LoadImg("����3",L"pic\\�������3.png");
	pGO->LoadImg("��ͼ1",L"pic\\��Ь.png");
	pGO->LoadImg("��ͼ2",L"pic\\����.png");
	pGO->LoadImg("��ͼ3",L"pic\\���.png");
	pGO->LoadImg("��ͼ4",L"pic\\�ʺ�.png");
	pGO->LoadImg("����1",L"pic\\01.png");
	pGO->LoadImg("����2",L"pic\\02.png");
	pGO->LoadImg("����3",L"pic\\03.png");
	pGO->LoadImg("����4",L"pic\\04.png");
	pGO->LoadImg("0_2",L"pic\\0_2.png");
	pGO->LoadImg("1_2",L"pic\\1_2.png");
	pGO->LoadImg("2_2",L"pic\\2_2.png");
	pGO->LoadImg("��Ϸ״̬1",L"pic\\�豭.png");
}
//������ʾ����
void CRoom::SetData(int sign, int no,const char * str,int num ,int tag)
{
	m_sign=sign;
	m_no=no;
	m_str=str;
	m_num=num;
	m_tag=tag;
}
//��ȡ������
int CRoom::GetNo()
{
	return m_no;
}
//��ȡ��������
int CRoom::GetNum()
{
	return m_num;
}
//��ʼ��
void CRoom::ActRender()
{
	//��ȡ��ʾ�豸
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	char buf[15];//ƴװ�ַ���
	if(m_state!=3)
	{
		sprintf(buf,"����%d",m_state+1);
		pGO->DrawImg(buf,m_X,m_Y,200,81);
	}
	sprintf(buf,"����%d",m_no);//215 242
	pGO->DrawImg(buf,m_X+81,m_Y+6,18,19);
	sprintf(buf,"��ͼ%d",m_sign);//215 242   373 265
	pGO->DrawImg(buf,m_X+4,m_Y+2,51,57);
	pGO->DrawStringS("������",m_X+106,m_Y+7,m_str.c_str(),RGB(248,232,0));
	sprintf(buf,"%d_2",m_num);
	pGO->DrawImg(buf,m_X+101,m_Y+46,36,20);
	sprintf(buf,"��Ϸ״̬%d",m_tag);
	pGO->DrawImg(buf,m_X+158,m_Y+33,29,34);
}
//�Ǽ�����Ⱦ
void CRoom::UnActRender()
{}
//��ȡ��Ϣ
//����ǹ������Ϣ: p1Ϊ x���� p2 Ϊ y����(��Կؼ��ľ���)
//����Ǽ�����Ϣ: p1Ϊ����ļ�ֵ
//������ַ���Ϣ: p1Ϊ������ַ�, p2��ʾ�Ƿ�Ϊ˫�ֽڣ�1Ϊ�� 0Ϊ��
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