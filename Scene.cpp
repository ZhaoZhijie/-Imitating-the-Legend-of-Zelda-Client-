#include "Scene.h"

CScene::CScene()
{
	m_virW=CGameEngine::GetGE()->GetClientW();
	m_virH=CGameEngine::GetGE()->GetClientH();
}
CScene::~CScene()
{}

void CScene::Init()
{}
void  CScene::Enter()//进入场景
{}	
//void  CScene::Run()
//{}
void CScene::OutputRun(){}		//绘制
void CScene::LogicInputRun(){}	//输入和逻辑
void  CScene::Quit()//场景退出
{}	
void  CScene::End()//结束
{}
void CScene::HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)//消息处理
{}
void CScene::SetQuitChange(std::string QuitChange)
{
	m_QuitChange = QuitChange;
}
void CScene::SetEnterChange(std::string EnterChange)
{
	m_EnterChange = EnterChange;
}

void CScene::OnUIMsg(const char* id, int UIMsg)
{}

bool CScene::LoadUI(const char* id, CUI* pUI)
{
	//获取ID
	std::string sid = id;
	//查找id是否存在 如果不存在则可以放入UI
	//否则放入失败
	if(m_UI.find(sid) != m_UI.end())
		return 0;
	pUI->m_Scene = this;
	pUI->m_Name = id;

	//把UI 装入场景的UI管理中
	m_UI.insert(std::pair<std::string, CUI*>(sid, pUI));
	return 1;
}
bool CScene::ReleaseUI(const char* id)
{
	//获取id
	std::string sid = id;
	//通过id查找 该UI是否存在
	//如果存在 则消除 如果不存在 返回false 删除失败
	std::map<std::string, CUI*>::iterator iui = m_UI.find(sid);
	if (iui != m_UI.end())
	{
		//处理UI 把需要释放的部分释放掉
		iui->second->End();
		delete iui->second;
		m_UI.erase(iui);
		return true;
	}
	return false;
}
//获取UI
CUI* CScene::GetUI(const char* id)
{
	//查找该id的UI
	//如果找到 则返回该UI 没找到 则返回0
	std::string sid = id;
	std::map<std::string, CUI*>::iterator iui = m_UI.find(sid);
	return iui == m_UI.end() ? 0 : iui->second;
}
//设置焦点UI  如果id为空 则没有焦点控件
bool CScene::SetKeyUI(const char* id)
{
	//不需要焦点控件 设置0
	if(0 == id)
	{
		m_KeyUI = 0;
		return 1;
	}
	else
	{
		std::string sid = id;
		std::map<std::string, CUI*>::iterator iui = m_UI.find(sid);
		if(iui == m_UI.end())
			return 0;
		m_KeyUI = iui->second;
		return 1;
	}
}