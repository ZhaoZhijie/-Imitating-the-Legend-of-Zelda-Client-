#ifndef _JIE_GOU_H
#define _JIE_GOU_H
struct preGood
{//x,y��ָ��ͼ��������
	unsigned char id;//��Ʒid
	int x;
	int y;
	unsigned long code1;
	unsigned long code2;
};
//���ﵱǰ���ƶ�����Ʒ
struct pushGood
{
	unsigned char id;//��Ʒid
	float x;
	float y;
	unsigned char turn;
	unsigned long code1;
	unsigned long code2;
};
//�������Ʒ ��ʯ ���ٵ�
struct extGood
{
	unsigned char id;//������Ʒ��id
	float x;
	float y;
	float z;
	float vx;
	float vy;
	float vz;
	int cf;//��ʯ���ֺ�����˶���֡
};
struct Good
{
	unsigned char id;//��Ʒid
	float x;
	float y;
};
struct gData
{
	unsigned char id;//��Ʒid
	float x;
	float y;
	unsigned long code1;//������Ϣ1
	unsigned long code2;//������Ϣ2
	gData * next;
};

struct SinglePic
{
	unsigned short no;//ͼƬ���
	float x;
	float y;
};
#endif