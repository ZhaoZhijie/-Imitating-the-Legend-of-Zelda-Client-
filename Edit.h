#ifndef _EDIT_H
#define _EDIT_H
#include "ui.h"
#include <string>
class CEdit : public CUI
{
protected:
	char m_Text[200];	//�༭�������
	int m_pos;//�����λ��
	std::string m_FontName;
	bool m_tag;//�Ƿ�����
	int m_cf;
	unsigned int m_cor;
public:
	CEdit(char *fn, unsigned int c, int x, int y, int w, int h, bool View = true, bool Act = true);
	//��ȡ�༭���ı�
	const char * GetText();
	//���ñ༭���ı�
	void SetText(const char * txt);
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