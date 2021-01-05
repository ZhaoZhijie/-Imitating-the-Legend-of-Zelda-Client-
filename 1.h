#ifndef Scene_1_H_
#define Scene_1_H_

#include "Scene.h"
#include "SceneChange.h"
#include "MakeMove.h"
#include "AutoPlay.h"
#include <list>
#include "Map.h"
//大厅界面
struct RoomData
{
	//int _no;//房间编号
	char _name[20];//名称
	int _num;//人数
	int _tag;//开始标志
	int _type;//地图类型
};
struct PlayerData
{
	char _name[20];//玩家名字
	int _state;//玩家状态
	int _order;
	std::string _uid;
};
class C1 : public CScene
{
private:
	int m_x;
	int m_y;
	bool m_curtag;
	CAutoPlay *m_AutoShow;
	CMap<short,RoomData> m_Room;
	int m_state;//场景当前状态  大厅 新建  房间
	PlayerData m_Owner;
	PlayerData m_Mate;

	//房间信息
	int m_no;
	std::string m_RName;
	int m_type;
	int m_num;
public:
	void Init();
	void OutputRun();		//绘制
	void LogicInputRun();	//输入和逻辑
	void Enter();			//入效果
	void Quit();			//出效果
	bool LoadSceneChange(const char* id, CSceneChange* pSceneChange);
	void OnUIMsg(const char* id, int UIMsg);
	//对窗口消息的处理
	void HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif