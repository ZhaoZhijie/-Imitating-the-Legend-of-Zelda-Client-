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

	//控件管理
	std::map<std::string, CUI*> m_UI;
	//拥有当前焦点的控件
	CUI* m_KeyUI;
	//视口原始大小
	int m_virW;
	int m_virH;
public:
	CScene();
	virtual ~CScene();

	virtual void Init();
	virtual void Enter();	//进入场景
	virtual void OutputRun();		//绘制
	virtual void LogicInputRun();	//输入和逻辑
	virtual void Quit();	//场景退出
	virtual void End();		//结束
	virtual void HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//消息处理
	//当本场景中的控件发生事件，本函数就会被调用
	virtual void OnUIMsg(const char* id, int UIMsg);
	
	void SetQuitChange(std::string QuitChange);
	void SetEnterChange(std::string EnterChange);

	//控件相关
	//加载UI
	bool LoadUI(const char* id, CUI* pUI);
	//卸载UI
	bool ReleaseUI(const char* id);
	//获取UI
	CUI* GetUI(const char* id);
	//设置焦点UI  如果id为空 则没有焦点控件
	bool SetKeyUI(const char* id);
};

#endif