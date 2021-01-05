#include "GameEngine.h"
#include "1.h"
#include "2.h"
#include "start.h"
#include "Enter1.h"
#include "Quit1.h"

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPervInstance,
					  LPSTR lpCmdLine,
					  int nShowCmd)
{

	CGameEngine::GetGE()->Init(640, 480);

	CGameEngine::GetGE()->LoadScene("��¼����", new CStart);
	CGameEngine::GetGE()->LoadScene("��������", new C1);
	CGameEngine::GetGE()->LoadScene("��Ϸ����", new C2);
	CGameEngine::GetGE()->LoadSceneChange("��1", new CEnter1);
	CGameEngine::GetGE()->LoadSceneChange("��1", new CQuit1);
	

	CGameEngine::GetGE()->SetInitScene("��¼����");
	
	CGameEngine::GetGE()->Run();

	return 1;
}