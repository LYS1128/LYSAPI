#include "stdafx.h"
#include "Rain.h"


CRain::CRain()
{
}


CRain::~CRain()
{
}

void CRain::Initialize(void)
{
	m_dwTime = GetTickCount();

	m_tInfo.fX = rand() % 1000 - 100;
	m_tInfo.fY = rand() % 700 -100;
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_fSpeed = 10.f + rand() % 5;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/rain.bmp", L"rain");

	Update_Rect();
}

int CRain::Update(void)
{
	m_tInfo.fX -= m_fSpeed*cos(45);
	m_tInfo.fY += m_fSpeed*sin(45);

	Update_Rect();

	return OBJ_NOEVENT;
}

int CRain::Late_Update(void)
{
	return 0;
}

void CRain::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"rain");

	//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
	GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		int(m_tRect.left),  // 복사 받을 위치 x좌표
		int(m_tRect.top),					   // 복사 받을 위치 y좌표
		(int)m_tInfo.fCX,			   // 복사 받을 이미지의 가로 사이즈
		(int)m_tInfo.fCY,			   // 복사 받을 이미지의 세로 사이즈
		hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		0,							   // 비트맵을 출력할 시작 좌표
		0,
		64,							   // 복사할 비트맵의 가로, 세로 사이즈
		64,
		RGB(255, 0, 255));			// 제거하고자하는 색상
}

void CRain::Release(void)
{
}
