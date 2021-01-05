#include "AutoPlay.h"
#define _MAX 10
#define _STATE_CHANGE 0
#define _STATE_RUN 1
#define _CT 60//切换所用帧数
CAutoPlay::CAutoPlay(int cd, int x, int y, int w, int h, bool View, bool Act)
	:CUI(x, y, w, h, View, Act)
{
	m_path.clear();
	m_len=0;
	m_pos=0;
	m_cd=cd;
	m_cf=0;
	m_state=_STATE_RUN;
	memset(&m_r,0,sizeof(RECT));
}
//设置Logo
bool CAutoPlay::SetLogo(const char *id, int x, int y, int w, int h)
{
	m_logo=id;
	m_r.left=x;
	m_r.top=y;
	m_r.right=x+w;
	m_r.bottom=y+h;
	return true;
}
//增加图片
bool CAutoPlay::AddPic(const char* id)
{
	if(m_len>=_MAX)
		return false;
	std::string s=id;
	for(int i=0;i<m_path.size();i++)
	{
		if(s.compare(m_path[i])==0)
			return false;
	}
	m_path.push_back(s);
	m_len++;
	return true;
}
void CAutoPlay::Render()
{
	//获取绘制工具
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	m_cf++;
	if(m_state==_STATE_RUN)
	{
		pGO->DrawImg(m_path[m_pos].c_str(),m_X, m_Y, m_W, m_H, 0, 0, m_W, m_H,_MIRROR_NONE,1);
		if(m_cf>=m_cd)
		{
			m_cf=0;
			m_state=_STATE_CHANGE;
			m_pos=++m_pos%m_len;
		}
	}
	else
	{
		pGO->DrawImg(m_path[m_pos].c_str(),m_X, m_Y, m_W, m_H, 0, 0, m_W, m_H,_MIRROR_NONE,1);
		pGO->DrawImg(m_path[(m_pos-1+m_len)%m_len].c_str(),m_X, m_Y, m_W, m_H, 0, 0, m_W, m_H,_MIRROR_NONE,1-m_cf*1.0/_CT);	
		if(m_cf>_CT)
		{
			m_cf=0;
			m_state=_STATE_RUN;
		}
	}
	//如果有logo则绘制logo
	if(m_logo.size()!=0)
		pGO->DrawImg(m_logo.c_str(), m_X+m_r.left , m_Y+m_r.top , m_r.right-m_r.left , m_r.bottom-m_r.top , 0, 0, m_r.right-m_r.left, m_r.bottom-m_r.top);
}
