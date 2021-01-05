#ifndef _UI_H_
#define _UI_H_

//UI(User Interface):�û��ӿڡ���Ҫ��������Ϸ���������û����н����Ľ���Ԫ��

#include <string>

//UI����Ϣ
#define _UIM_C_ENTER 0		//������
#define _UIM_C_QUIT 1		//����˳�
#define _UIM_C_MOVE_IN 2	//����ڿؼ����ƶ�
#define _UIM_C_MOVE_OUT 3	//����ڿؼ����ƶ�
#define _UIM_C_LBD_IN 4		//�ڿؼ��� �������
#define _UIM_C_LBU_IN 5		//�ڿؼ��� ̧�����
#define _UIM_C_LBD_OUT 6	//�ڿؼ��� �������
#define _UIM_C_LBU_OUT 7	//�ڿؼ��� ̧�����
#define _UIM_C_RBD_IN 8		//�ڿؼ��� �����Ҽ�
#define _UIM_C_RBU_IN 9		//�ڿؼ��� ̧���Ҽ�
#define _UIM_C_RBD_OUT 10	//�ڿؼ��� �����Ҽ�
#define _UIM_C_RBU_OUT 11	//�ڿؼ��� ̧���Ҽ�
#define _UIM_K_D 12			//��������
#define _UIM_K_U 13			//����̧��
#define _UIM_K_CHAR 14		//�����ַ�

//ͬһʱ�� һ��������ֻ����һ���ؼ��յ�������Ϣ�����ַ���Ϣ
class CScene;

class CUI
{
protected:
	friend class CScene;

	//UI���η�Χ
	int m_X, m_Y;		//����
	int m_W, m_H;		//���
	bool m_View;		//�Ƿ�ɼ�
	bool m_Act;			//�Ƿ񼤻�	������ɼ�һ��������

	std::string m_Name;
	CScene* m_Scene;	//��UI����������

public:
	CUI(int x, int y, int w, int h, bool View = true, bool Act = true);
	virtual ~CUI();

	//����UI�ľ���
	void SetRect(int x, int y, int w, int h);
	//��ȡUI�ľ���
	void GetRect(int* x, int* y, int* w, int* h);
	//�����Ƿ�ɼ�
	void SetView(bool View);
	//��ȡUI�Ƿ�ɼ�
	bool GetView();
	//�����Ƿ����
	void SetAct(bool Act);
	//��ȡUI�Ƿ����
	bool GetAct();

	//������Ҫʵ�ֵ��麯��

	//��ʼ��
	virtual void Init();
	//������Ⱦ
	virtual void ActRender();
	//�Ǽ�����Ⱦ
	virtual void UnActRender();
	//��ȡ��Ϣ
	//����ǹ������Ϣ: p1Ϊ x���� p2 Ϊ y����(��Կؼ��ľ���)
	//����Ǽ�����Ϣ: p1Ϊ����ļ�ֵ
	//������ַ���Ϣ: p1Ϊ������ַ�, p2��ʾ�Ƿ�Ϊ˫�ֽڣ�1Ϊ�� 0Ϊ��
	virtual void OnMsg(int msg, int p1, int p2);
	virtual void End();
};

#endif