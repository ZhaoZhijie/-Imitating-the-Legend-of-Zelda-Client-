#include "2.h"
#include "GameEngine.h"
#include "GameProtocol.h"
#include "MsgBox.h"
#pragma comment(lib,"Imm32.Lib")
#define  _SCENE_STATE_LOAD 0
#define  _SCENE_STATE_WAIT 1
#define  _SCENE_STATE_RUN 2
void C2::Init()
{
	m_x=0;
	m_y=0;
	m_curtag=false;
	m_state=_SCENE_STATE_LOAD;
	m_data=NULL;
	m_len=0;
	m_virW=240;
	m_virH=160;
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	pGO->LoadFont("��׼",12, 17, 1, false, false ,false, "����");	
	pGO->LoadBmp("����","pic\\gimg\\���ﶯ��.bmp");
	pGO->LoadBmp("��������","pic\\gimg\\��������.bmp");
	pGO->LoadBmp("��������","pic\\gimg\\��������.bmp");
	pGO->LoadBmp("��������","pic\\gimg\\��������.bmp");
	pGO->LoadBmp("������","pic\\gimg\\������.bmp");
	pGO->LoadBmp("������","pic\\gimg\\������.bmp");
	pGO->LoadBmp("������","pic\\gimg\\������.bmp");
	pGO->LoadBmp("�����","pic\\gimg\\�����.bmp");
	pGO->LoadBmp("��������","pic\\gimg\\��������.bmp");
	pGO->LoadBmp("��������","pic\\gimg\\��������.bmp");
	pGO->LoadBmp("��������","pic\\gimg\\��������.bmp");
	pGO->LoadBmp("���ӵ�����","pic\\gimg\\���ӵ�����.bmp");
	pGO->LoadBmp("���ӵ�����","pic\\gimg\\���ӵ�����.bmp");
	pGO->LoadBmp("���ӵ�����","pic\\gimg\\���ӵ�����.bmp");
	pGO->LoadBmp("�ñ�ʯ","pic\\gimg\\�ñ�ʯ.bmp");
	pGO->LoadBmp("׹��","pic\\gimg\\׹��.bmp");
	pGO->LoadBmp("ˮ��","pic\\gimg\\ˮ��.bmp");
	pGO->LoadBmp("ˮ��","pic\\gimg\\ˮ��.bmp");
	pGO->LoadBmp("����","pic\\gimg\\����.bmp");
	pGO->LoadBmp("����ʯ","pic\\gimg\\����ʯ.bmp");
	pGO->LoadBmp("�ݵض�Ч","pic\\gimg\\�ݵض�Ч.bmp");
	pGO->LoadBmp("������Ч","pic\\gimg\\������Ч.bmp");
	pGO->LoadBmp("����","pic\\gimg\\����.bmp");
	pGO->LoadBmp("����","pic\\gimg\\����.bmp");
	pGO->LoadBmp("ʧ�ܻ���","pic\\gimg\\ʧ�ܻ���.bmp");
	pGO->LoadBmp("ʧ������","pic\\gimg\\ʧ������.bmp");
	pGO->LoadBmp("��Ʒ","pic\\gimg\\��Ʒ.bmp");
	pGO->LoadBmp("��ͼ","pic\\gimg\\��ͼ.bmp");
	pGO->LoadBmp("��ͼ2","pic\\gimg\\ɭ���������ͼ.bmp");
	pGO->LoadBmp("����0","pic\\gimg\\0.bmp");
	pGO->LoadBmp("����1","pic\\gimg\\1.bmp");
	pGO->LoadBmp("����2","pic\\gimg\\2.bmp");
	pGO->LoadBmp("����3","pic\\gimg\\3.bmp");
	ShowCursor(TRUE);
	//�༭ͼ�� ����255��λ�ֽڱ�ʾ������λ�ֽڱ�ʾ֡
	Element *emts[40]={
		new Element("��ͼ2",0,0,1000,1000,0,0),	//0	��ͼ
		new Element("��Ʒ",0,0,16,16,0,0),	//1	��
		new Element("��Ʒ",16,0,16,16,0,0),	//2	���ӹ�
		new Element("��Ʒ",32,0,16,16,0,0),	//3	���ӿ�
		new Element("��Ʒ",48,0,16,16,0,0),	//4	���ص���
		new Element("��Ʒ",64,0,16,16,0,0),	//5	���ذ���
		new Element("��Ʒ",80,0,16,16,0,0),	//6	Բʯͷ
		new Element("��Ʒ",96,0,16,16,0,0),	//7	����Ĳ�
		new Element("����",0,206,14,8,8,0),	//8	Ӱ��
		new Element("��Ʒ",0,16,32,32,0,0),	//9	��ʯ��
		new Element("��Ʒ",32,16,32,32,0,0),	//10	��ʯͷ
		new Element("��Ʒ",112,0,16,16,0,0),	//11	Сʯ��
		new Element("��Ʒ",0,48,7,14,0,0),	//12	�ڱ�ʯ
		new Element("��Ʒ",7,48,7,14,0,0),	//13	�̱�ʯ
		new Element("��Ʒ",14,48,7,14,0,0),	//14	����ʯ
		new Element("��Ʒ",21,48,7,14,0,0),	//15	�챦ʯ
		new Element("��Ʒ",0,62,10,13,0,0),	//16	���ͳ��
		new Element("��Ʒ",10,62,8,11,0,0),	//17	����0
		new Element("��Ʒ",18,62,8,11,0,0),	//18	����1
		new Element("��Ʒ",26,62,8,11,0,0),	//19	����2
		new Element("��Ʒ",34,62,8,11,0,0),	//20	����3
		new Element("��Ʒ",42,62,8,11,0,0),	//21	����4
		new Element("��Ʒ",50,62,8,11,0,0),	//22	����5
		new Element("��Ʒ",58,62,8,11,0,0),	//23	����6
		new Element("��Ʒ",66,62,8,11,0,0),	//24	����7
		new Element("��Ʒ",74,62,8,11,0,0),	//25	����8
		new Element("��Ʒ",82,62,8,11,0,0),	//26	����9
		new Element("��Ʒ",0,75,9,9,0,0),		//27	Ѫ������
		new Element("��Ʒ",25,99,8,4,4,2),		//28	��ͷ�ӵ�Ӱ��
		new Element("��Ʒ",0,109,34,48,1,0),		//29	�����
		new Element("��Ʒ",34,109,16,48,0,16),//30 ��������
		new Element("��Ʒ",50,109,16,48,0,16),//31 ��������
		new Element("��Ʒ",130,109,16,48,0,16),//32Կ������
		new Element("��Ʒ",146,109,16,48,0,16),//33Կ������
		new Element("��Ʒ",74,34,15,15,0,0),//34Կ��
		new Element("��Ʒ",30,50,13,10,0,0),//35ͷ��Կ��
		new Element("ʧ�ܻ���",0,0,240,160,0,0),//36
		new Element("ʧ������",0,0,212,30,0,0),//37
		new Element("����",0,0,64,32,0,0),//38
		new Element("����",0,0,80,48,0,0)//39
	};
	for(int i=0;i<40;i++)
		m_Elements.Insert(i,emts[i]);
	//���ض�������
	//վ������
	m_Elements.Insert(MAKEWORD(0,1),new Element("����",  5,0,18,24,10,18));
	m_Elements.Insert(MAKEWORD(1,1),new Element("����",35,0,18,24,10,18));	
	m_Elements.Insert(MAKEWORD(2,1),new Element("����",65,0,18,24,10,18));	
	//��������
	m_Elements.Insert(MAKEWORD(0,2),new Element("����",  95,0,18,24,10,18));
	m_Elements.Insert(MAKEWORD(1,2),new Element("����",125,0,18,24,10,20));	
	m_Elements.Insert(MAKEWORD(2,2),new Element("����",155,0,18,24,10,20));	
	m_Elements.Insert(MAKEWORD(3,2),new Element("����",185,0,18,24,10,20));	
	m_Elements.Insert(MAKEWORD(4,2),new Element("����",215,0,18,24,10,19));	
	m_Elements.Insert(MAKEWORD(5,2),new Element("����",245,0,18,24,10,19));	
	m_Elements.Insert(MAKEWORD(6,2),new Element("����",275,0,18,24,10,19));	
	m_Elements.Insert(MAKEWORD(7,2),new Element("����",305,0,18,24,10,20));	
	m_Elements.Insert(MAKEWORD(8,2),new Element("����",335,0,18,24,10,20));	
	m_Elements.Insert(MAKEWORD(9,2),new Element("����",365,0,18,24,10,20));	
	//վ������
	m_Elements.Insert(MAKEWORD(0,3),new Element("����",5,779,18,25,10,19));
	//��������
	m_Elements.Insert(MAKEWORD(0,4),new Element("����",  95,779,18,25,10,19));
	m_Elements.Insert(MAKEWORD(1,4),new Element("����",125,779,18,25,10,19));	
	m_Elements.Insert(MAKEWORD(2,4),new Element("����",155,779,18,25,10,20));	
	m_Elements.Insert(MAKEWORD(3,4),new Element("����",185,779,18,25,10,19));	
	m_Elements.Insert(MAKEWORD(4,4),new Element("����",215,779,18,25,10,19));	
	m_Elements.Insert(MAKEWORD(5,4),new Element("����",245,779,18,25,10,19));	
	m_Elements.Insert(MAKEWORD(6,4),new Element("����",275,779,18,25,10,19));	
	m_Elements.Insert(MAKEWORD(7,4),new Element("����",305,779,18,25,10,20));	
	m_Elements.Insert(MAKEWORD(8,4),new Element("����",335,779,18,25,10,19));	
	m_Elements.Insert(MAKEWORD(9,4),new Element("����",365,779,18,25,10,19));
	//վ������
	m_Elements.Insert(MAKEWORD(0,5),new Element("����",  5,1531,17,22,  8,17));
	m_Elements.Insert(MAKEWORD(1,5),new Element("����",35,1531,17,22,  8,17));	
	m_Elements.Insert(MAKEWORD(2,5),new Element("����",65,1531,17,22,  8,17));	
	//��������
	m_Elements.Insert(MAKEWORD(0,6),new Element("����",  92,1531,23,22,  8,17));
	m_Elements.Insert(MAKEWORD(1,6),new Element("����",124,1531,20,22,  8,17));	
	m_Elements.Insert(MAKEWORD(2,6),new Element("����",154,1531,20,22,10,19));	
	m_Elements.Insert(MAKEWORD(3,6),new Element("����",184,1531,20,23,  9,19));	
	m_Elements.Insert(MAKEWORD(4,6),new Element("����",214,1531,20,23,  8,18));	
	m_Elements.Insert(MAKEWORD(5,6),new Element("����",242,1531,23,22,  8,17));	
	m_Elements.Insert(MAKEWORD(6,6),new Element("����",274,1531,19,22,  7,17));	
	m_Elements.Insert(MAKEWORD(7,6),new Element("����",304,1531,19,22,  9,19));	
	m_Elements.Insert(MAKEWORD(8,6),new Element("����",334,1531,19,22,  8,19));	
	m_Elements.Insert(MAKEWORD(9,6),new Element("����",364,1531,19,22,  8,18));
	//��������
	m_Elements.Insert(MAKEWORD(0,7),new Element("��������",    1,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(1,7),new Element("��������",  81,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(2,7),new Element("��������",161,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(3,7),new Element("��������",241,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(4,7),new Element("��������",321,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(5,7),new Element("��������",401,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(6,7),new Element("��������",481,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(7,7),new Element("��������",561,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(8,7),new Element("��������",641,1,80,80,40,40));
	//��������
	m_Elements.Insert(MAKEWORD(0,8),new Element("��������",    1,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(1,8),new Element("��������",  81,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(2,8),new Element("��������",161,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(3,8),new Element("��������",241,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(4,8),new Element("��������",321,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(5,8),new Element("��������",401,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(6,8),new Element("��������",481,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(7,8),new Element("��������",561,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(8,8),new Element("��������",641,1,80,80,40,40));
	//��������
	m_Elements.Insert(MAKEWORD(0,9),new Element("��������",    1,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(1,9),new Element("��������",  81,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(2,9),new Element("��������",161,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(3,9),new Element("��������",241,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(4,9),new Element("��������",321,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(5,9),new Element("��������",401,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(6,9),new Element("��������",481,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(7,9),new Element("��������",561,1,80,80,40,40));
	//������
	m_Elements.Insert(MAKEWORD(0,10),new Element("������",    1,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(1,10),new Element("������",  81,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(2,10),new Element("������",161,1,80,80,40,40 ));	
	m_Elements.Insert(MAKEWORD(3,10),new Element("������",241,1,80,80,40,40 ));	
	m_Elements.Insert(MAKEWORD(4,10),new Element("������",321,1,80,80,40,40 ));	
	m_Elements.Insert(MAKEWORD(5,10),new Element("������",401,1,80,80,40,40 ));	
	m_Elements.Insert(MAKEWORD(6,10),new Element("������",481,1,80,80,40,40 ));
	//������
	m_Elements.Insert(MAKEWORD(0,11),new Element("������",    1,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(1,11),new Element("������",  81,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(2,11),new Element("������",161,1,80,80,40,40 ));	
	m_Elements.Insert(MAKEWORD(3,11),new Element("������",241,1,80,80,40,40 ));	
	m_Elements.Insert(MAKEWORD(4,11),new Element("������",321,1,80,80,40,40 ));	
	m_Elements.Insert(MAKEWORD(5,11),new Element("������",401,1,80,80,40,40 ));	
	m_Elements.Insert(MAKEWORD(6,11),new Element("������",481,1,80,80,40,40 ));
	//������
	m_Elements.Insert(MAKEWORD(0,12),new Element("������",    1,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(1,12),new Element("������",  81,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(2,12),new Element("������",161,1,80,80,40,40 ));	
	m_Elements.Insert(MAKEWORD(3,12),new Element("������",241,1,80,80,40,40 ));	
	m_Elements.Insert(MAKEWORD(4,12),new Element("������",321,1,80,80,40,40 ));	
	m_Elements.Insert(MAKEWORD(5,12),new Element("������",401,1,80,80,40,40 ));	

	//���¾�����
	m_Elements.Insert(MAKEWORD(0,13),new Element("����",  95,30,18,23,10,18));
	m_Elements.Insert(MAKEWORD(1,13),new Element("����",125,31,18,22,10,19));	
	m_Elements.Insert(MAKEWORD(2,13),new Element("����",155,30,18,24,  9,20 ));	
	m_Elements.Insert(MAKEWORD(3,13),new Element("����",185,30,18,24,10,20 ));	
	m_Elements.Insert(MAKEWORD(4,13),new Element("����",215,30,18,24,10,19 ));	
	m_Elements.Insert(MAKEWORD(5,13),new Element("����",245,30,18,23,10,18 ));	
	m_Elements.Insert(MAKEWORD(6,13),new Element("����",275,31,18,22,10,19 ));
	m_Elements.Insert(MAKEWORD(7,13),new Element("����",305,30,18,24,10,20 ));	
	m_Elements.Insert(MAKEWORD(8,13),new Element("����",335,30,18,24,10,20 ));
	m_Elements.Insert(MAKEWORD(9,13),new Element("����",365,30,18,24,10,19 ));
	//���Ͼ�����
	m_Elements.Insert(MAKEWORD(0,14),new Element("����",  95,811,18,22,10,17));
	m_Elements.Insert(MAKEWORD(1,14),new Element("����",125,811,18,22,10,17));	
	m_Elements.Insert(MAKEWORD(2,14),new Element("����",155,810,18,24,10,20 ));	
	m_Elements.Insert(MAKEWORD(3,14),new Element("����",185,809,18,25,10,19 ));	
	m_Elements.Insert(MAKEWORD(4,14),new Element("����",215,810,18,24,10,21 ));	
	m_Elements.Insert(MAKEWORD(5,14),new Element("����",245,811,18,22,10,17 ));	
	m_Elements.Insert(MAKEWORD(6,14),new Element("����",275,811,18,22,  9,17 ));
	m_Elements.Insert(MAKEWORD(7,14),new Element("����",305,810,18,24,10,19 ));	
	//���������
	m_Elements.Insert(MAKEWORD(0,15),new Element("����",  92,1561,23,22,  8,17));
	m_Elements.Insert(MAKEWORD(1,15),new Element("����",124,1561,20,21,  8,17));	
	m_Elements.Insert(MAKEWORD(2,15),new Element("����",154,1561,20,21,10,19 ));	
	m_Elements.Insert(MAKEWORD(3,15),new Element("����",184,1561,20,22,  9,19 ));	
	m_Elements.Insert(MAKEWORD(4,15),new Element("����",214,1561,20,22,  8,18 ));	
	m_Elements.Insert(MAKEWORD(5,15),new Element("����",242,1561,23,22,  8,17 ));	
	m_Elements.Insert(MAKEWORD(6,15),new Element("����",274,1561,19,22,  7,17 ));
	m_Elements.Insert(MAKEWORD(7,15),new Element("����",304,1561,19,22,  9,19 ));	
	m_Elements.Insert(MAKEWORD(8,15),new Element("����",334,1561,19,22,  8,19 ));
	m_Elements.Insert(MAKEWORD(9,15),new Element("����",364,1561,20,22,  8,17 ));
	//���¾���
	m_Elements.Insert(MAKEWORD(0,16),new Element("����",  95,62,18,19,10,10));
	m_Elements.Insert(MAKEWORD(1,16),new Element("����",125,62,18,20,10,14));	
	m_Elements.Insert(MAKEWORD(2,16),new Element("����",155,62,18,20,10,15 ));	
	m_Elements.Insert(MAKEWORD(3,16),new Element("����",185,61,18,22,10,17 ));	
	//���¾���
	m_Elements.Insert(MAKEWORD(0,17),new Element("����",215,60,18,23,10,18));
	//���Ͼ���
	m_Elements.Insert(MAKEWORD(0,18),new Element("����",  96,842,16,19,  9,16));
	m_Elements.Insert(MAKEWORD(1,18),new Element("����",126,842,16,20,  9,18));	
	m_Elements.Insert(MAKEWORD(2,18),new Element("����",155,842,18,20,10,17 ));	
	m_Elements.Insert(MAKEWORD(3,18),new Element("����",185,841,18,21,10,17 ));
	//���Ͼ���
	m_Elements.Insert(MAKEWORD(0,19),new Element("����",215,841,18,21,10,17));
	//�������
	m_Elements.Insert(MAKEWORD(0,20),new Element("����",  94,1592,20,19,13,13));
	m_Elements.Insert(MAKEWORD(1,20),new Element("����",125,1592,17,19,11,14));	
	m_Elements.Insert(MAKEWORD(2,20),new Element("����",156,1592,16,20,10,15));	
	m_Elements.Insert(MAKEWORD(3,20),new Element("����",186,1592,16,21,  7,16));
	//�������
	m_Elements.Insert(MAKEWORD(0,21),new Element("����",215,1591,17,22,8,17));
	//���¾�
	m_Elements.Insert(MAKEWORD(0,22),new Element("����",335,61,18,22,10,18));
	m_Elements.Insert(MAKEWORD(1,22),new Element("����",305,61,18,21,10,17));	
	//���Ͼ�
	m_Elements.Insert(MAKEWORD(0,23),new Element("����",312,901,20,22,11,17));
	m_Elements.Insert(MAKEWORD(1,23),new Element("����",342,901,18,22,10,17));	
	//�����
	m_Elements.Insert(MAKEWORD(0,24),new Element("�����",1,1,80,80, 40, 40));
	m_Elements.Insert(MAKEWORD(1,24),new Element("�����",81,1,80,80, 40, 40));	
	m_Elements.Insert(MAKEWORD(2,24),new Element("�����",161,1,80,80, 40, 40));	
	//������
	m_Elements.Insert(MAKEWORD(0,25),new Element("����",245,61,18,22,10,17));
	m_Elements.Insert(MAKEWORD(1,25),new Element("����",273,61,22,22,12,17));	
	m_Elements.Insert(MAKEWORD(2,25),new Element("����",305,61,18,21,10,16));
	m_Elements.Insert(MAKEWORD(3,25),new Element("����",335,61,18,22,10,17));	
	//������
	m_Elements.Insert(MAKEWORD(0,26),new Element("����",244,841,20,22,11,18));
	m_Elements.Insert(MAKEWORD(1,26),new Element("����",274,841,20,21,11,17));	
	m_Elements.Insert(MAKEWORD(2,26),new Element("����",305,841,18,21,10,17));
	m_Elements.Insert(MAKEWORD(3,26),new Element("����",334,841,20,21,11,17));	
	//������
	m_Elements.Insert(MAKEWORD(0,27),new Element("����",245,1591,18,22,  7,17));
	m_Elements.Insert(MAKEWORD(1,27),new Element("����",274,1591,19,21,  9,16));	
	m_Elements.Insert(MAKEWORD(2,27),new Element("����",304,1591,20,21,10,16));
	m_Elements.Insert(MAKEWORD(3,27),new Element("����",335,1591,18,22,  8,17));	
	//������
	m_Elements.Insert(MAKEWORD(0,28),new Element("����",  89,90,30,24,16,19));
	m_Elements.Insert(MAKEWORD(1,28),new Element("����",119,90,30,24,16,19));	
	m_Elements.Insert(MAKEWORD(2,28),new Element("����",149,90,30,24,16,19 ));	
	m_Elements.Insert(MAKEWORD(3,28),new Element("����",179,90,30,24,16,19 ));	
	m_Elements.Insert(MAKEWORD(4,28),new Element("����",209,90,30,24,16,19 ));	
	m_Elements.Insert(MAKEWORD(5,28),new Element("����",239,90,30,24,16,19 ));	
	m_Elements.Insert(MAKEWORD(6,28),new Element("����",269,90,30,24,16,19 ));
	m_Elements.Insert(MAKEWORD(7,28),new Element("����",299,90,30,24,16,19 ));	
	m_Elements.Insert(MAKEWORD(8,28),new Element("����",329,90,30,24,16,19 ));
	//������
	m_Elements.Insert(MAKEWORD(0,29),new Element("����",  89,870,30,24,16,19));
	m_Elements.Insert(MAKEWORD(1,29),new Element("����",119,870,30,24,16,19));	
	m_Elements.Insert(MAKEWORD(2,29),new Element("����",149,870,30,24,16,19 ));	
	m_Elements.Insert(MAKEWORD(3,29),new Element("����",179,870,30,24,16,19 ));	
	m_Elements.Insert(MAKEWORD(4,29),new Element("����",209,870,30,24,16,19 ));	
	m_Elements.Insert(MAKEWORD(5,29),new Element("����",239,870,30,24,16,19 ));	
	m_Elements.Insert(MAKEWORD(6,29),new Element("����",269,870,30,24,16,19 ));
	m_Elements.Insert(MAKEWORD(7,29),new Element("����",299,870,30,24,16,19 ));	
	m_Elements.Insert(MAKEWORD(8,29),new Element("����",329,870,30,24,16,19 ));
	//������
	m_Elements.Insert(MAKEWORD(0,30),new Element("����",  89,1620,30,24,13,19));
	m_Elements.Insert(MAKEWORD(1,30),new Element("����",119,1620,30,24,13,19));	
	m_Elements.Insert(MAKEWORD(2,30),new Element("����",149,1620,30,24,13,19 ));	
	m_Elements.Insert(MAKEWORD(3,30),new Element("����",179,1620,30,24,13,19 ));	
	m_Elements.Insert(MAKEWORD(4,30),new Element("����",209,1620,30,24,13,19 ));	
	m_Elements.Insert(MAKEWORD(5,30),new Element("����",239,1620,30,24,13,19 ));	
	m_Elements.Insert(MAKEWORD(6,30),new Element("����",269,1620,30,24,13,19 ));
	m_Elements.Insert(MAKEWORD(7,30),new Element("����",299,1620,30,24,13,19 ));	
	m_Elements.Insert(MAKEWORD(8,30),new Element("����",329,1620,30,24,13,19 ));
	//���·� չ��
	m_Elements.Insert(MAKEWORD(0,31),new Element("����",  90,211,18,21,10,17));
	m_Elements.Insert(MAKEWORD(1,31),new Element("����",115,211,28,21,14,17));	
	//���·� ����
	m_Elements.Insert(MAKEWORD(0,32),new Element("����",144,211,32,21,16,19));
	m_Elements.Insert(MAKEWORD(1,32),new Element("����",178,211,32,21,16,19));	
	m_Elements.Insert(MAKEWORD(2,32),new Element("����",211,211,28,21,14,19 ));	
	//���Ϸ� չ��
	m_Elements.Insert(MAKEWORD(0,33),new Element("����",  95,990,18,24,  9,19));
	m_Elements.Insert(MAKEWORD(1,33),new Element("����",122,990,24,24,12,19));	
	//���Ϸ� ����
	m_Elements.Insert(MAKEWORD(0,34),new Element("����",148,990,32,24,16,19));
	m_Elements.Insert(MAKEWORD(1,34),new Element("����",181,990,30,24,15,19));	
	m_Elements.Insert(MAKEWORD(2,34),new Element("����",212,990,28,24,14,19));	
	//����� չ��
	m_Elements.Insert(MAKEWORD(0,35),new Element("����",  95,1742,18,20,10,15));
	m_Elements.Insert(MAKEWORD(1,35),new Element("����",123,1741,22,22,10,15));	
	//����� ����
	m_Elements.Insert(MAKEWORD(0,36),new Element("����",152,1740,24,20,11,15));
	m_Elements.Insert(MAKEWORD(1,36),new Element("����",183,1741,22,18,10,15));	
	m_Elements.Insert(MAKEWORD(2,36),new Element("����",213,1743,23,16,10,13));	
	//ˮ������
	m_Elements.Insert(MAKEWORD(0,37),new Element("����",  95,244,18,18,10,12));
	m_Elements.Insert(MAKEWORD(1,37),new Element("����",124,244,20,19,11,12));	
	m_Elements.Insert(MAKEWORD(2,37),new Element("����",153,244,22,19,12,11));
	m_Elements.Insert(MAKEWORD(3,37),new Element("����",185,244,18,17,10,12));
	//������Ӿ
	m_Elements.Insert(MAKEWORD(0,38),new Element("����",211,241,26,19,14,12));
	m_Elements.Insert(MAKEWORD(1,38),new Element("����",240,239,28,21,15,14));	
	m_Elements.Insert(MAKEWORD(2,38),new Element("����",272,243,24,17,13,10));
	m_Elements.Insert(MAKEWORD(3,38),new Element("����",302,244,24,17,13,11));
	//ˮ������
	m_Elements.Insert(MAKEWORD(0,39),new Element("����",  95,1021,18,19,10,12));
	m_Elements.Insert(MAKEWORD(1,39),new Element("����",124,1022,20,18,11,11));	
	m_Elements.Insert(MAKEWORD(2,39),new Element("����",153,1021,22,21,12,12));
	m_Elements.Insert(MAKEWORD(3,39),new Element("����",185,1021,18,19,10,12));
	//������Ӿ
	m_Elements.Insert(MAKEWORD(0,40),new Element("����",213,1021,22,21,12,14));
	m_Elements.Insert(MAKEWORD(1,40),new Element("����",242,1022,24,21,13,13));	
	m_Elements.Insert(MAKEWORD(2,40),new Element("����",272,1021,24,22,13,12));
	m_Elements.Insert(MAKEWORD(3,40),new Element("����",300,1021,28,24,15,11));
	//ˮ������
	m_Elements.Insert(MAKEWORD(0,41),new Element("����",  93,1805,21,17,10,11));
	m_Elements.Insert(MAKEWORD(1,41),new Element("����",120,1805,23,17,13,10));	
	m_Elements.Insert(MAKEWORD(2,41),new Element("����",151,1805,23,20,12,11));
	m_Elements.Insert(MAKEWORD(3,41),new Element("����",185,1805,18,17,  9,11));
	//������Ӿ
	m_Elements.Insert(MAKEWORD(0,42),new Element("����",214,1805,28,19,12,11));
	m_Elements.Insert(MAKEWORD(1,42),new Element("����",244,1805,31,18,12,10));	
	m_Elements.Insert(MAKEWORD(2,42),new Element("����",284,1805,34,21,11,12));
	m_Elements.Insert(MAKEWORD(3,42),new Element("����",325,1805,36,22,10,12));
	//�ñ�ʯ
	m_Elements.Insert(MAKEWORD(  0,43),new Element("����ʯ",1,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  1,43),new Element("����ʯ",81,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(  2,43),new Element("����ʯ",161,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  3,43),new Element("����ʯ",241,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  4,43),new Element("����ʯ",321,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  5,43),new Element("����ʯ",401,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  6,43),new Element("����ʯ",481,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  7,43),new Element("����ʯ",561,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  8,43),new Element("����ʯ",641,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  9,43),new Element("����ʯ",721,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(10,43),new Element("����ʯ",801,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(11,43),new Element("����ʯ",881,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(12,43),new Element("����ʯ",961,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(13,43),new Element("����ʯ",1041,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(14,43),new Element("����ʯ",1121,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(15,43),new Element("����ʯ",1201,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(16,43),new Element("����ʯ",1281,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(17,43),new Element("����ʯ",1361,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(18,43),new Element("����ʯ",1441,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(19,43),new Element("����ʯ",1521,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(20,43),new Element("����ʯ",1601,1,80,80,40,40));
	//�� ���� ����
	m_Elements.Insert(MAKEWORD(0,44),new Element("��������",11,7,16,15,8,7));
	m_Elements.Insert(MAKEWORD(1,44),new Element("��������",53,6,16,15,8,7));
	//������ ����
	m_Elements.Insert(MAKEWORD(0,45),new Element("��������",6,7,16,14,8,7));
	m_Elements.Insert(MAKEWORD(1,45),new Element("��������",31,7,16,14,8,7));
	//������ ����
	m_Elements.Insert(MAKEWORD(0,46),new Element("��������",3,3,14,15,7,7));
	m_Elements.Insert(MAKEWORD(1,46),new Element("��������",27,3,16,15,10,7));
	m_Elements.Insert(MAKEWORD(2,46),new Element("��������",49,3,16,14,11,7));
	//������ ����
	m_Elements.Insert(MAKEWORD(0,47),new Element("��������",62,26,16,15,8,7));
	//������ ����
	m_Elements.Insert(MAKEWORD(0,48),new Element("��������",52,6,16,15,8,7));
	//�����󲻶�
	m_Elements.Insert(MAKEWORD(0,49),new Element("��������",27,3,16,15,10,7));
	//���ӵ�����
	m_Elements.Insert(MAKEWORD(0,50),new Element("���ӵ�����",10,5,16,19,8,7));
	m_Elements.Insert(MAKEWORD(1,50),new Element("���ӵ�����",34,5,16,19,8,7));
	//���ӵ�����
	m_Elements.Insert(MAKEWORD(0,51),new Element("���ӵ�����",4,9,16,17,8,7));
	m_Elements.Insert(MAKEWORD(1,51),new Element("���ӵ�����",31,9,16,17,8,7));
	//���ӵ�����
	m_Elements.Insert(MAKEWORD(0,52),new Element("���ӵ�����",8,2,16,15,8,7));
	m_Elements.Insert(MAKEWORD(1,52),new Element("���ӵ�����",33,2,19,15,13,7));
	//���ӵ�
	m_Elements.Insert(MAKEWORD(0,53),new Element("��Ʒ",0,98,8,7, 4,4));
	m_Elements.Insert(MAKEWORD(1,53),new Element("��Ʒ",8,98,8,8,4,4));
	m_Elements.Insert(MAKEWORD(2,53),new Element("��Ʒ",16,98,8,7,4,4));
	//��������
	m_Elements.Insert(MAKEWORD(0,54),new Element("����",0,222,18,24,10,18));
	m_Elements.Insert(MAKEWORD(1,54),new Element("����",5,0,18,24,10,18));
	//��������
	m_Elements.Insert(MAKEWORD(0,55),new Element("����",5,779,18,25,10,19));
	m_Elements.Insert(MAKEWORD(1,55),new Element("����",20,222,18,25,10,19));
	//��������
	m_Elements.Insert(MAKEWORD(0,56),new Element("����",  5,1531,17,22,  8,17));
	m_Elements.Insert(MAKEWORD(1,56),new Element("����",41,  223,17,22,  8,17));
	//�����
	m_Elements.Insert(MAKEWORD(0,57),new Element("��Ʒ",66,109,16,48,0,16));
	//���Ҵ�
	m_Elements.Insert(MAKEWORD(0,58),new Element("��Ʒ",82,109,16,48,0,16));
	//׹��
	m_Elements.Insert(MAKEWORD(0,59),new Element("׹��",1,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(1,59),new Element("׹��",81,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(2,59),new Element("׹��",161,1,80,80,40,40));	
	m_Elements.Insert(MAKEWORD(3,59),new Element("׹��",241,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(4,59),new Element("׹��",321,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(5,59),new Element("׹��",401,1,80,80,40,40));
	//�����
	m_Elements.Insert(MAKEWORD(0,60),new Element("����",0,118,26,21,0,21));
	m_Elements.Insert(MAKEWORD(1,60),new Element("����",0,139,26,21,0,21));	
	m_Elements.Insert(MAKEWORD(2,60),new Element("����",0,160,26,21,0,21));	
	m_Elements.Insert(MAKEWORD(3,60),new Element("����",0,181,26,21,0,21));
	//�ݵض�̬
	m_Elements.Insert(MAKEWORD(0,61),new Element("�ݵض�Ч",  1,1,18,16,9,8));
	m_Elements.Insert(MAKEWORD(1,61),new Element("�ݵض�Ч",19,1,18,16,9,8));	
	m_Elements.Insert(MAKEWORD(2,61),new Element("�ݵض�Ч",37,1,18,16,9,8));	
	m_Elements.Insert(MAKEWORD(3,61),new Element("�ݵض�Ч",55,1,18,16,9,8));
	//����������Ч
	m_Elements.Insert(MAKEWORD(0,62),new Element("������Ч",  1,1,36,36,18,18));
	m_Elements.Insert(MAKEWORD(1,62),new Element("������Ч",37,1,36,36,18,18));	
	m_Elements.Insert(MAKEWORD(2,62),new Element("������Ч",73,1,36,36,18,18));	
	m_Elements.Insert(MAKEWORD(3,62),new Element("������Ч",109,1,36,36,18,18));
	m_Elements.Insert(MAKEWORD(4,62),new Element("������Ч",145,1,36,36,18,18));	
	m_Elements.Insert(MAKEWORD(5,62),new Element("������Ч",181,1,36,36,18,18));	
	m_Elements.Insert(MAKEWORD(6,62),new Element("������Ч",217,1,36,36,18,18));
	//����
	m_Elements.Insert(MAKEWORD(0,63),new Element("����",1,1,16,16,0,0));
	m_Elements.Insert(MAKEWORD(1,63),new Element("����",17,1,16,16,0,0));	
	m_Elements.Insert(MAKEWORD(2,63),new Element("����",33,1,16,16,0,0));	
	m_Elements.Insert(MAKEWORD(3,63),new Element("����",49,1,16,16,0,0));
	//����
	m_Elements.Insert(MAKEWORD(  0,64),new Element("����",1,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  1,64),new Element("����",81,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  2,64),new Element("����",161,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  3,64),new Element("����",241,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  4,64),new Element("����",321,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  5,64),new Element("����",401,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  6,64),new Element("����",481,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  7,64),new Element("����",561,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  8,64),new Element("����",641,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(  9,64),new Element("����",721,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(10,64),new Element("����",801,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(11,64),new Element("����",881,1,80,80,40,40));
	m_Elements.Insert(MAKEWORD(12,64),new Element("����",961,1,80,80,40,40));
	//ˮ��
	m_Elements.Insert(MAKEWORD( 0,65),new Element("ˮ��",1,1,18,10,9,3));
	m_Elements.Insert(MAKEWORD( 1,65),new Element("ˮ��",19,1,18,10,9,3));
	m_Elements.Insert(MAKEWORD( 2,65),new Element("ˮ��",37,1,18,10,9,3));
	m_Elements.Insert(MAKEWORD( 3,65),new Element("ˮ��",55,1,18,10,9,3));
	m_Elements.Insert(MAKEWORD( 4,65),new Element("ˮ��",73,1,18,10,9,3));
	//ˮ��
	m_Elements.Insert(MAKEWORD( 0,66),new Element("ˮ��",1,1,42,25,21,12));
	m_Elements.Insert(MAKEWORD( 1,66),new Element("ˮ��",42,1,42,25,21,12));
	m_Elements.Insert(MAKEWORD( 2,66),new Element("ˮ��",85,1,42,25,21,12));
	m_Elements.Insert(MAKEWORD( 3,66),new Element("ˮ��",127,1,42,25,21,12));
	m_Elements.Insert(MAKEWORD( 4,66),new Element("ˮ��",169,1,42,25,21,12));
	//����
	m_Elements.Insert(MAKEWORD( 0,67),new Element("����0",0,0,1000,148,0,0));
	m_Elements.Insert(MAKEWORD( 1,67),new Element("����1",0,0,1000,148,0,0));
	m_Elements.Insert(MAKEWORD( 2,67),new Element("����2",0,0,1000,148,0,0));
	m_Elements.Insert(MAKEWORD( 3,67),new Element("����3",0,0,1000,148,0,0));
}
void C2::OutputRun()
{
	HIMC hIMC = ::ImmGetContext(CGameEngine::GetGE()->GetWnd()); 
	bool tag=ImmGetOpenStatus(hIMC);
	//SetWindowText(CGameEngine::GetGE()->GetWnd(),tag?"���뷨��":"���뷨�ر�");
	if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_P)==_KS_DC)
	{//�����뷨
		ImmSetOpenStatus(hIMC, TRUE); 
	}
	else if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_O)==_KS_DC)
	{
		ImmSetOpenStatus(hIMC, FALSE); 	
	}

	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	if(m_state==_SCENE_STATE_RUN&&m_len!=0&&m_data!=NULL)
	{
		int num=(m_len-20)/8;
		for(int i=0;i<num;i++)
		{
			short no=*(short*)(m_data+20+i*8);
			short x=*(short*)(m_data+20+i*8+2);
			short y=*(short*)(m_data+20+i*8+4);
			char move=*((char*)&no+1);
			char f=*(char*)&no;
			int mirror=_MIRROR_NONE;
			if(move<0)
			{
				mirror= _MIRROR_LR;
				no=MAKEWORD(f,-move);
			}
			Element * emt=m_Elements.Find(no)->data;
			pGO->DrawMiBmp(emt->id, x-(mirror== _MIRROR_LR?emt->w-emt->mx:emt->mx), y-emt->my, emt->w, emt->h, emt->x, emt->y, emt->w, emt->h,mirror,RGB(255,0,255));
		}
	}
}
void C2::LogicInputRun()
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
					MessageBox(CGameEngine::GetGE()->GetWnd(),"������������µ�½��","��ʾ",0);
					break;
				}
			case _TCNE_DATA:	
				{
					_GAME_PROTOCOL * gp=(_GAME_PROTOCOL *)evt.data;
					switch(gp->id)
					{
					case _GAME_START:
						{
							m_state=_SCENE_STATE_RUN;
							break;
						}
					case _PLAYER_OUTPUT:
						{
							_S_C_GP19 * gp19=(_S_C_GP19 *)evt.data;
							m_len=gp19->_len;
							m_virx=gp19->_virx;
							m_viry=gp19->_viry;
							if(m_data)
								CGameEngine::GetGE()->GetMemPool()->Free(m_data);
							m_data=(char*)CGameEngine::GetGE()->GetMemPool()->Allocate(m_len);
							memcpy(m_data, evt.data, m_len);
							SetWindowTextA(CGameEngine::GetGE()->GetWnd(),"�յ�����");
							break;
						}
					}
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
	if(CGameEngine::GetGE()->GetAct())
	{
		int tag=0;
		int key[8]={_GI_K_W,_GI_K_S,_GI_K_A,_GI_K_D,_GI_K_J,_GI_K_K,_GI_K_U,_GI_K_I};
		for(int i=0;i<8;i++)
		{
			tag=CGameEngine::GetGE()->GetGI()->Get(key[i]);
			if(tag==_KS_DC||tag==_KS_UC)
			{
				_C_S_GP18 gp18;
				gp18.type=_INTYPE_KEY;
				gp18.p1=key[i];
				gp18.p2=tag;
				pClient->SendData((char*)&gp18,sizeof(gp18));
			}		
		}
	}
}

void C2::Enter()
{
	m_state=_SCENE_STATE_WAIT;
	//��֪�������ѽ��볡�������󴫵ݳ�������
	_C_S_GP22 gp22;
	CGameEngine::GetGE()->GetClient()->SendData((const char*)&gp22,sizeof(gp22));
}