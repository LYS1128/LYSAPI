#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f), m_eDir(DIR(0)), m_bSelect(false)
	, m_pFrameKey(nullptr)
	, m_eState(STATE(STATE_END)), m_ePreState(STATE(STATE_END))
{

	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}


CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY / 2.f));
}

void CObj::Move_Frame(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}

}

void CObj::Set_Pos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}

void CObj::Set_Dir(DIR eDir)
{
	m_eDir = eDir;
}


void CObj::Set_PosX(float _fX)
{
	m_tInfo.fX += _fX;
}

void CObj::Set_PosY(float _fY)
{
	m_tInfo.fY += _fY;
}

void CObj::RePosX(float _X)
{
	m_tInfo.fX = _X;
}

void CObj::RePosY(float _Y)
{
	m_tInfo.fY = _Y;
}



void CObj::Set_FrameKey(TCHAR* pFrameKey)
{
	m_pFrameKey = pFrameKey;
}
