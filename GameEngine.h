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
	int m_RunState;				//运行状态

	//窗口相关数据
	WNDCLASSA m_WndClass;		//窗口
	char m_WndClassName[32];	//窗口名
	HWND m_hWnd;				//窗口句柄
	int m_ClientW, m_ClientH;	//客户区宽高
	BOOL m_Act;					//窗口激活标志
	int m_SleepTime;			//休息时间

	//场景切换相关
	CSceneChange* m_EnterChange;
	CSceneChange* m_QuitChange;
	//场景切换管理
	std::map<std::string, CSceneChange*> m_SceneChange;

	//动作管理
	CMoves m_Moves;

	//工具相关
	CGameOutput* m_GO;		//输出工具
	CGameInput* m_GI;		//输入工具
	CAudioManager m_AM;		//音频工具
	CTcpClient m_Client;	//客户端

	//内存池
	CMemoryPool m_MP;

	//场景相关
	std::map<std::string, CScene*> m_Scene;	//场景
	static CScene* m_CurScene;						//当前运行的场景
	CScene* m_NextScene;					//下一个场景

	//消息处理函数
	static LRESULT CALLBACK _WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	CGameEngine();
	~CGameEngine();

	//游戏引擎
	static CGameEngine* m_pGameEngine;
public:
	//得到游戏引擎
	static CGameEngine* GetGE();
	
	//初始化
	bool Init(int ClientW, int ClientH);

	//运行  游戏循环
	void Run();

	//加载场景
	bool LoadScene(const char* id, CScene* pScene);
	//加载场景切换效果
	bool LoadSceneChange(const char* id, CSceneChange* p);
	//剔除场景
	bool ReleaseScene(const char* id);
	//设置最初场景
	bool SetInitScene(const char* id);
	//设置当前场景
	bool SetCurScene(const char* id);
	//获取场景
	CScene* GetScene(const char* id);

	//设置进入效果
	bool SetEnterChange(const char* id);
	//设置退出效果
	bool SetQuitChange(const char* id);
	
	//获取绘制工具
	CGameOutput* GetGO();
	//获取输入工具
	CGameInput* GetGI();
	//获取音频工具
	CAudioManager* GetAM();
	//获取客户端
	CTcpClient* GetClient();

	//获取内存池
	CMemoryPool * GetMemPool();
	//退出游戏
	void ExitGame();

	//获取客户区宽
	int GetClientW();
	//获取客户区高
	int GetClientH();

	//获取动作管理
	CMoves* GetMoves();

	//获取窗口句柄
	HWND GetWnd();
	//获取窗口激活状态
	bool GetAct();
};

#endif