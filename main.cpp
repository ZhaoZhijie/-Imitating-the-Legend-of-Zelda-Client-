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

	CGameEngine::GetGE()->LoadScene("µÇÂ¼³¡¾°", new CStart);
	CGameEngine::GetGE()->LoadScene("´óÌü³¡¾°", new C1);
	CGameEngine::GetGE()->LoadScene("ÓÎÏ·³¡¾°", new C2);
	CGameEngine::GetGE()->LoadSceneChange("Èë1", new CEnter1);
	CGameEngine::GetGE()->LoadSceneChange("³ö1", new CQuit1);
	

	CGameEngine::GetGE()->SetInitScene("µÇÂ¼³¡¾°");
	
	CGameEngine::GetGE()->Run();

	return 1;
}