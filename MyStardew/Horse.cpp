#include "stdafx.h"
#include "Horse.h"


CHorse::CHorse()
{

}


CHorse::~CHorse()
{
}

void CHorse::Initialize(void)
{
	m_tInfo.fX = 300;
	m_tInfo.fY = 300;
	m_tInfo.fCX = 32;
	m_tInfo.fCY = 32;

	m_fSpeed = 2.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Horse.bmp", L"Horse");

	m_pFrameKey = L"Horse";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	Update_Rect();
}

int CHorse::Update(void)
{
	Key_Input();

	Move_Frame();

	Update_Rect();
	return 0;
}

int CHorse::Late_Update(void)
{
	return 0;
}

void CHorse::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Horse");

	//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
	GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		int(m_tRect.left -16),  // 복사 받을 위치 x좌표
		int(m_tRect.top -40),				   // 복사 받을 위치 y좌표
		64,			   // 복사 받을 이미지의 가로 사이즈
		80,			   // 복사 받을 이미지의 세로 사이즈
		hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		m_tFrame.iFrameStart * 64,							   // 비트맵을 출력할 시작 좌표
		0,
		64,							   // 복사할 비트맵의 가로, 세로 사이즈
		80,
		RGB(255, 0, 255));			// 제거하고자하는 색상
}

void CHorse::Release(void)
{
}


/////////////////////////////////////////
void CHorse::Key_Input() {
	if (CKeyMgr::Get_Instance()->Key_Pressing('W') && (m_tRect.top > 155)) {
		if (CKeyMgr::Get_Instance()->Key_Pressing('A') && (m_tRect.left > 0)) {
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('D') && (m_tRect.right < WINCX)) {
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);

		}
		else {
			m_tInfo.fY -= m_fSpeed;
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('S') && (m_tRect.bottom < 475)) {
		if (CKeyMgr::Get_Instance()->Key_Pressing('A') && (m_tRect.left > 0)) {
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('D') && (m_tRect.right < WINCX)) {
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
		}
		else {
			m_tInfo.fY += m_fSpeed;
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('A') && (m_tRect.left > 0)) {
		m_tInfo.fX -= m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('D') && (m_tRect.right < WINCX)) {
		m_tInfo.fX += m_fSpeed;
	}
}