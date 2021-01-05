#ifndef _JIE_GOU_H
#define _JIE_GOU_H
struct preGood
{//x,y是指地图格子坐标
	unsigned char id;//物品id
	int x;
	int y;
	unsigned long code1;
	unsigned long code2;
};
//人物当前所推动的物品
struct pushGood
{
	unsigned char id;//物品id
	float x;
	float y;
	unsigned char turn;
	unsigned long code1;
	unsigned long code2;
};
//掉落的物品 宝石 加速等
struct extGood
{
	unsigned char id;//掉落物品的id
	float x;
	float y;
	float z;
	float vx;
	float vy;
	float vz;
	int cf;//宝石出现后持续了多少帧
};
struct Good
{
	unsigned char id;//物品id
	float x;
	float y;
};
struct gData
{
	unsigned char id;//物品id
	float x;
	float y;
	unsigned long code1;//附加信息1
	unsigned long code2;//附加信息2
	gData * next;
};

struct SinglePic
{
	unsigned short no;//图片编号
	float x;
	float y;
};
#endif