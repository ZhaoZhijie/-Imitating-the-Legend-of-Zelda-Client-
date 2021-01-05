#ifndef _START_H_
#define _START_H_

#include "Scene.h"
#include "SceneChange.h"
#include "ui.h"
#include "AutoPlay.h"
#include "GameEngine.h"
#include "MsgBox.h"
class CStart : public CScene
{
	int m_x;
	int m_y;
	int m_curtag;
	CAutoPlay *m_AutoShow;
	CTcpClient* m_Client;
	int m_state;
public:
	void Init();
	void OutputRun();		//����
	void LogicInputRun();	//������߼�
	bool LoadSceneChange(const char* id, CSceneChange* pSceneChange);
	//���������еĿؼ������¼����������ͻᱻ����
	void OnUIMsg(const char* id, int UIMsg);
	void HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//��Ϣ����
};

#endif