#ifndef _ROOM_H
#define _ROOM_H
#include "ui.h"
#include <string>
#define _MAP_BOOT 1
#define _MAP_BAR 2
#define _MAP_FLY 3
#define _MAP_RAND 4
#define ROOM_STATE_EMPTY  0   //空房间 ，在讲房间数据发到客户端时空房间不用发
#define ROOM_STATE_WAIT  1		//玩家在房间等待，还未进入游戏
#define ROOM_STATE_RUN  2		//已经进入游戏
#define _ROOM_RUN 3
#define _ROOM_CLICK 0		//按钮被按下的消息
class CRoom : public CUI
{
protected:
	int m_sign ;//地图标志
	int m_no;//房间编号
	std::string m_str;//房间名字
	int m_num;//房间人数
	int m_state;//控件状态
	bool m_in;//光标在空间内标志
	int m_tag;//游戏开始 准备 状态标志

public:
	CRoom(int x, int y, int w, int h, bool View = true, bool Act = true);
	//设置显示数据
	void SetData(int sign, int no,const char * str,int num ,int tag);
	//获取房间编号
	int GetNo();
	//获取房间人数
	int GetNum();
	//初始化
	void ActRender();
	//非激活渲染
	void UnActRender();
	//获取消息
	//如果是光标类消息: p1为 x坐标 p2 为 y坐标(相对控件的矩形)
	//如果是键盘消息: p1为传入的键值
	//如果是字符消息: p1为传入的字符, p2表示是否为双字节（1为是 0为否）
	void OnMsg(int msg, int p1, int p2);
};
#endif