#ifndef _SCENE_H_
#define _SCENE_H_

#include <string>
#include <map>
#include "ui.h"
#include "GameEngine.h"
class CScene
{
protected:
	friend class CGameEngine;
	std::string m_QuitChange;
	std::string m_EnterChange;

	//�ؼ�����
	std::map<std::string, CUI*> m_UI;
	//ӵ�е�ǰ����Ŀؼ�
	CUI* m_KeyUI;
	//�ӿ�ԭʼ��С
	int m_virW;
	int m_virH;
public:
	CScene();
	virtual ~CScene();

	virtual void Init();
	virtual void Enter();	//���볡��
	virtual void OutputRun();		//����
	virtual void LogicInputRun();	//������߼�
	virtual void Quit();	//�����˳�
	virtual void End();		//����
	virtual void HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//��Ϣ����
	//���������еĿؼ������¼����������ͻᱻ����
	virtual void OnUIMsg(const char* id, int UIMsg);
	
	void SetQuitChange(std::string QuitChange);
	void SetEnterChange(std::string EnterChange);

	//�ؼ����
	//����UI
	bool LoadUI(const char* id, CUI* pUI);
	//ж��UI
	bool ReleaseUI(const char* id);
	//��ȡUI
	CUI* GetUI(const char* id);
	//���ý���UI  ���idΪ�� ��û�н���ؼ�
	bool SetKeyUI(const char* id);
};

#endif