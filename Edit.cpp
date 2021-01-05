#include "Edit.h"
#include "GameEngine.h"
CEdit::CEdit(char *fn, unsigned int c, int x, int y, int w, int h, bool View, bool Act)
	:CUI(x, y, w, h, View, false)
{
	memset(m_Text,0,200);
	m_pos=0;
	m_FontName=fn;
	m_tag=true;//是否闪动  当m_sub为0时才可闪动
	m_cf=0;
	m_cor=c;
}
//获取编辑框文本
const char * CEdit::GetText()
{
	return m_Text;
}
//设置编辑框文本
void CEdit::SetText(const char * txt)
{
	strcpy_s(m_Text,200,txt);
}
void CEdit::ActRender()
{
	m_cf++;
	if(m_tag)
	{
		if(m_cf==40)
		{
			m_tag=false;
			m_cf=0;
		}
	}
	else
	{
		if(m_cf==40)
		{
			m_tag=true;
			m_cf=0;
		}
	}
	//获取绘制工具
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	//绘制实心矩形
	//pGO->DrawSRectangle(m_X, m_Y, m_X + m_W, m_Y + m_H, RGB(0,0,0), RGB(255,255,255));
	SIZE sz;
	char buf[200];
	memcpy(buf,m_Text,m_pos+1);
	buf[m_pos]=0;
	pGO->GetTextLen(m_FontName.c_str(), buf, &sz);	
	//绘制文字
	pGO->DrawStringS(m_FontName.c_str(), m_X ,m_Y+(m_H-sz.cy)/2, m_Text, m_cor);
	//绘制插入符
	if(m_Act&&m_tag)
		pGO->DrawLine(sz.cx+m_X, m_Y+1, sz.cx+m_X, m_Y+m_H-1, RGB(255,255,255),2);	
}

void CEdit::UnActRender()
{
	//获取绘制工具
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();
	//绘制实心矩形
	pGO->DrawSRectangle(m_X, m_Y, m_X + m_W, m_Y + m_H, RGB(255,0,0), RGB(255,255,255));
	//绘制文字
	pGO->DrawStringS(m_FontName.c_str(), m_X ,m_Y+2, m_Text, RGB(0,255,0));	
}

void CEdit::OnMsg(int msg, int p1, int p2)
{
	switch(msg)
	{
	case _UIM_C_LBD_OUT:
		{
			//m_sub=0;
			//m_tag=true;
			//m_cf=0;
			break;
		}
	case _UIM_K_CHAR:
		{
			m_tag=true;
			m_cf=0;
			int n=strlen(m_Text);
			if(n>198)
				break;
			if(p1==8)
			{//退格键
				char buf[200];
				memcpy(buf,m_Text,200);
				if(m_pos>0)
				{
					int tmp=m_pos;
					if(m_Text[m_pos-1]<0)
						m_pos-=2;
					else
						m_pos-=1;
					memcpy(m_Text+m_pos, buf+tmp, n-tmp+1);
				}
			}
			else if(p1==37)
			{//左键
				if(m_pos>0)
				{
					if(m_Text[m_pos-1]>0)
						m_pos--;	
					else
						m_pos-=2;
				}
			}
			else if(p1==39)
			{//右键
				if(m_pos<n)
				{
					if(m_Text[m_pos]>0)
						m_pos++;	
					else
						m_pos+=2;
				}
			}
			else if(p1==13)
			{//Enter键
				;
			}
			else
			{
				if(m_pos<n)
				{
					for(int i=n;i>=m_pos;i--)
					{
						m_Text[i+1]=m_Text[i];
					}
				}
				else
					m_Text[m_pos+1]='\0';
				m_Text[m_pos]=p1;
				m_pos++;
			}	
		}
	}
}