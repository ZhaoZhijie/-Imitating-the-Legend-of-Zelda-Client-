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
void  CScene::Enter()//���볡��
{}	
//void  CScene::Run()
//{}
void CScene::OutputRun(){}		//����
void CScene::LogicInputRun(){}	//������߼�
void  CScene::Quit()//�����˳�
{}	
void  CScene::End()//����
{}
void CScene::HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)//��Ϣ����
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
	//��ȡID
	std::string sid = id;
	//����id�Ƿ���� �������������Է���UI
	//�������ʧ��
	if(m_UI.find(sid) != m_UI.end())
		return 0;
	pUI->m_Scene = this;
	pUI->m_Name = id;

	//��UI װ�볡����UI������
	m_UI.insert(std::pair<std::string, CUI*>(sid, pUI));
	return 1;
}
bool CScene::ReleaseUI(const char* id)
{
	//��ȡid
	std::string sid = id;
	//ͨ��id���� ��UI�Ƿ����
	//������� ������ ��������� ����false ɾ��ʧ��
	std::map<std::string, CUI*>::iterator iui = m_UI.find(sid);
	if (iui != m_UI.end())
	{
		//����UI ����Ҫ�ͷŵĲ����ͷŵ�
		iui->second->End();
		delete iui->second;
		m_UI.erase(iui);
		return true;
	}
	return false;
}
//��ȡUI
CUI* CScene::GetUI(const char* id)
{
	//���Ҹ�id��UI
	//����ҵ� �򷵻ظ�UI û�ҵ� �򷵻�0
	std::string sid = id;
	std::map<std::string, CUI*>::iterator iui = m_UI.find(sid);
	return iui == m_UI.end() ? 0 : iui->second;
}
//���ý���UI  ���idΪ�� ��û�н���ؼ�
bool CScene::SetKeyUI(const char* id)
{
	//����Ҫ����ؼ� ����0
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