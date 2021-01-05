#ifndef Scene_1_H_
#define Scene_1_H_

#include "Scene.h"
#include "SceneChange.h"
#include "MakeMove.h"
#include "AutoPlay.h"
#include <list>
#include "Map.h"
//��������
struct RoomData
{
	//int _no;//������
	char _name[20];//����
	int _num;//����
	int _tag;//��ʼ��־
	int _type;//��ͼ����
};
struct PlayerData
{
	char _name[20];//�������
	int _state;//���״̬
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
	int m_state;//������ǰ״̬  ���� �½�  ����
	PlayerData m_Owner;
	PlayerData m_Mate;

	//������Ϣ
	int m_no;
	std::string m_RName;
	int m_type;
	int m_num;
public:
	void Init();
	void OutputRun();		//����
	void LogicInputRun();	//������߼�
	void Enter();			//��Ч��
	void Quit();			//��Ч��
	bool LoadSceneChange(const char* id, CSceneChange* pSceneChange);
	void OnUIMsg(const char* id, int UIMsg);
	//�Դ�����Ϣ�Ĵ���
	void HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif