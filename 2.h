#ifndef _2_H_
#define _2_H_
#include "Scene.h"
#include "Map.h"
#include "First.h"
class C2 : public CScene
{
//图素
struct Element
{
	const char * id;
	int x;
	int y;
	int w;
	int h;
	int mx;
	int my;
public:
	Element(){};
	Element(const char *_id, int _x, int _y, int _w, int _h, int _mx, int _my)
	{
		id=_id;	x=_x;	y=_y;	w=_w;	h=_h; mx=_mx; my=_my;
	}

};
private:
	int m_x;
	int m_y;
	bool m_curtag;
	//场景状态
	int m_state;
	//画面数据信息
	char * m_data;
	int m_len;
	unsigned short m_virx;
	unsigned short m_viry;
	//图素
	CMap<short,Element*> m_Elements;
public:
	void Init();
	void OutputRun();		//绘制
	void LogicInputRun();	//输入和逻辑
	void Enter();		
};


#endif