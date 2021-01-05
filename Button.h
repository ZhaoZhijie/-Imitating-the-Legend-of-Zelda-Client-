#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "ui.h"

#define _BUTTON_CLICK 0		//��ť�����µ���Ϣ
//�ؼ���ǰ״̬
#define _BUTTON_STATE_CURSOR_OUT 0		//����ڿؼ��ⲿ
#define _BUTTON_STATE_CURSOR_IN_UP 1	//����ڿؼ��ڲ���û�а���
#define _BUTTON_STATE_CURSOR_IN_DOWN 2	//����ڿؼ��ڲ�������
#define _BUTTON_STATE_UNACT 3			//�ؼ�������

class CButton : public CUI
{
protected:
	int m_ButtonState;	//������ǰ��״̬
	bool m_In;			//����ڰ�ť�ڵı��
	std::string m_Text;	//��ť������

public:
	CButton(const char* t, int x, int y, int w, int h, bool View = true, bool Act = true);
	void ActRender();
	//�Ǽ�����Ⱦ
	void UnActRender();
	//��ȡ��Ϣ
	//����ǹ������Ϣ: p1Ϊ x���� p2 Ϊ y����(��Կؼ��ľ���)
	//����Ǽ�����Ϣ: p1Ϊ����ļ�ֵ
	//������ַ���Ϣ: p1Ϊ������ַ�, p2��ʾ�Ƿ�Ϊ˫�ֽڣ�1Ϊ�� 0Ϊ��
	void OnMsg(int msg, int p1, int p2);

	//���ð�ť����
	void SetText(const char* t);
	const char* GetText();
};

#endif