#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#include "TcpClient.h"
#include <string>
#include <map>
#include "GameInput.h"
#include "GameOutput.h"
#include "SceneChange.h"
#include "MakeMove.h"
#include "AudioManager.h"
#include <windows.h>
#include "MemoryPool.h"

class CScene;

class CGameEngine
{
	int m_RunState;				//����״̬

	//�����������
	WNDCLASSA m_WndClass;		//����
	char m_WndClassName[32];	//������
	HWND m_hWnd;				//���ھ��
	int m_ClientW, m_ClientH;	//�ͻ������
	BOOL m_Act;					//���ڼ����־
	int m_SleepTime;			//��Ϣʱ��

	//�����л����
	CSceneChange* m_EnterChange;
	CSceneChange* m_QuitChange;
	//�����л�����
	std::map<std::string, CSceneChange*> m_SceneChange;

	//��������
	CMoves m_Moves;

	//�������
	CGameOutput* m_GO;		//�������
	CGameInput* m_GI;		//���빤��
	CAudioManager m_AM;		//��Ƶ����
	CTcpClient m_Client;	//�ͻ���

	//�ڴ��
	CMemoryPool m_MP;

	//�������
	std::map<std::string, CScene*> m_Scene;	//����
	static CScene* m_CurScene;						//��ǰ���еĳ���
	CScene* m_NextScene;					//��һ������

	//��Ϣ������
	static LRESULT CALLBACK _WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	CGameEngine();
	~CGameEngine();

	//��Ϸ����
	static CGameEngine* m_pGameEngine;
public:
	//�õ���Ϸ����
	static CGameEngine* GetGE();
	
	//��ʼ��
	bool Init(int ClientW, int ClientH);

	//����  ��Ϸѭ��
	void Run();

	//���س���
	bool LoadScene(const char* id, CScene* pScene);
	//���س����л�Ч��
	bool LoadSceneChange(const char* id, CSceneChange* p);
	//�޳�����
	bool ReleaseScene(const char* id);
	//�����������
	bool SetInitScene(const char* id);
	//���õ�ǰ����
	bool SetCurScene(const char* id);
	//��ȡ����
	CScene* GetScene(const char* id);

	//���ý���Ч��
	bool SetEnterChange(const char* id);
	//�����˳�Ч��
	bool SetQuitChange(const char* id);
	
	//��ȡ���ƹ���
	CGameOutput* GetGO();
	//��ȡ���빤��
	CGameInput* GetGI();
	//��ȡ��Ƶ����
	CAudioManager* GetAM();
	//��ȡ�ͻ���
	CTcpClient* GetClient();

	//��ȡ�ڴ��
	CMemoryPool * GetMemPool();
	//�˳���Ϸ
	void ExitGame();

	//��ȡ�ͻ�����
	int GetClientW();
	//��ȡ�ͻ�����
	int GetClientH();

	//��ȡ��������
	CMoves* GetMoves();

	//��ȡ���ھ��
	HWND GetWnd();
	//��ȡ���ڼ���״̬
	bool GetAct();
};

#endif