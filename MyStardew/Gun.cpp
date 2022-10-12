#include "stdafx.h"
#include "Gun.h"


CGun::CGun()
{
}


CGun::~CGun()
{
}

void CGun::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iItemID = GUN;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Gun.bmp", L"Gun");

	Update_Rect();
}

int CGun::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CGun::Late_Update(void)
{
	return 0;
}

void CGun::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Gun");

	//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
	GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		int(m_tRect.left),  // 복사 받을 위치 x좌표
		int(m_tRect.top),				   // 복사 받을 위치 y좌표
		(int)m_tInfo.fCX,			   // 복사 받을 이미지의 가로 사이즈
		(int)m_tInfo.fCY,			   // 복사 받을 이미지의 세로 사이즈
		hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		0,							   // 비트맵을 출력할 시작 좌표
		0,
		32,							   // 복사할 비트맵의 가로, 세로 사이즈
		32,
		RGB(255, 0, 255));			// 제거하고자하는 색상
}

void CGun::Release(void)
{
}
