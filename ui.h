#ifndef _UI_H_
#define _UI_H_

//UI(User Interface):用户接口。主要是用于游戏界面中与用户进行交互的界面元素

#include <string>

//UI的消息
#define _UIM_C_ENTER 0		//光标进入
#define _UIM_C_QUIT 1		//光标退出
#define _UIM_C_MOVE_IN 2	//光标在控件上移动
#define _UIM_C_MOVE_OUT 3	//光标在控件外移动
#define _UIM_C_LBD_IN 4		//在控件里 按下左键
#define _UIM_C_LBU_IN 5		//在控件里 抬起左键
#define _UIM_C_LBD_OUT 6	//在控件外 按下左键
#define _UIM_C_LBU_OUT 7	//在控件外 抬起左键
#define _UIM_C_RBD_IN 8		//在控件里 按下右键
#define _UIM_C_RBU_IN 9		//在控件里 抬起右键
#define _UIM_C_RBD_OUT 10	//在控件外 按下右键
#define _UIM_C_RBU_OUT 11	//在控件外 抬起右键
#define _UIM_K_D 12			//按键按下
#define _UIM_K_U 13			//按键抬起
#define _UIM_K_CHAR 14		//输入字符

//同一时间 一个场景中只能有一个控件收到键盘消息或者字符消息
class CScene;

class CUI
{
protected:
	friend class CScene;

	//UI矩形范围
	int m_X, m_Y;		//坐标
	int m_W, m_H;		//宽高
	bool m_View;		//是否可见
	bool m_Act;			//是否激活	如果不可见一定不激活

	std::string m_Name;
	CScene* m_Scene;	//该UI的所属场景

public:
	CUI(int x, int y, int w, int h, bool View = true, bool Act = true);
	virtual ~CUI();

	//设置UI的矩形
	void SetRect(int x, int y, int w, int h);
	//获取UI的矩形
	void GetRect(int* x, int* y, int* w, int* h);
	//设置是否可见
	void SetView(bool View);
	//获取UI是否可见
	bool GetView();
	//设置是否可用
	void SetAct(bool Act);
	//获取UI是否可用
	bool GetAct();

	//子类需要实现的虚函数

	//初始化
	virtual void Init();
	//激活渲染
	virtual void ActRender();
	//非激活渲染
	virtual void UnActRender();
	//获取消息
	//如果是光标类消息: p1为 x坐标 p2 为 y坐标(相对控件的矩形)
	//如果是键盘消息: p1为传入的键值
	//如果是字符消息: p1为传入的字符, p2表示是否为双字节（1为是 0为否）
	virtual void OnMsg(int msg, int p1, int p2);
	virtual void End();
};

#endif