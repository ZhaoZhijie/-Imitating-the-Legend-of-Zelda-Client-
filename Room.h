#ifndef _ROOM_H
#define _ROOM_H
#include "ui.h"
#include <string>
#define _MAP_BOOT 1
#define _MAP_BAR 2
#define _MAP_FLY 3
#define _MAP_RAND 4
#define ROOM_STATE_EMPTY  0   //�շ��� ���ڽ��������ݷ����ͻ���ʱ�շ��䲻�÷�
#define ROOM_STATE_WAIT  1		//����ڷ���ȴ�����δ������Ϸ
#define ROOM_STATE_RUN  2		//�Ѿ�������Ϸ
#define _ROOM_RUN 3
#define _ROOM_CLICK 0		//��ť�����µ���Ϣ
class CRoom : public CUI
{
protected:
	int m_sign ;//��ͼ��־
	int m_no;//������
	std::string m_str;//��������
	int m_num;//��������
	int m_state;//�ؼ�״̬
	bool m_in;//����ڿռ��ڱ�־
	int m_tag;//��Ϸ��ʼ ׼�� ״̬��־

public:
	CRoom(int x, int y, int w, int h, bool View = true, bool Act = true);
	//������ʾ����
	void SetData(int sign, int no,const char * str,int num ,int tag);
	//��ȡ������
	int GetNo();
	//��ȡ��������
	int GetNum();
	//��ʼ��
	void ActRender();
	//�Ǽ�����Ⱦ
	void UnActRender();
	//��ȡ��Ϣ
	//����ǹ������Ϣ: p1Ϊ x���� p2 Ϊ y����(��Կؼ��ľ���)
	//����Ǽ�����Ϣ: p1Ϊ����ļ�ֵ
	//������ַ���Ϣ: p1Ϊ������ַ�, p2��ʾ�Ƿ�Ϊ˫�ֽڣ�1Ϊ�� 0Ϊ��
	void OnMsg(int msg, int p1, int p2);
};
#endif