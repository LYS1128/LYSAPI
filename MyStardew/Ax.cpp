#include "stdafx.h"
#include "Ax.h"



CAx::CAx()
{
}


CAx::~CAx()
{
}

void CAx::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iItemID = AX;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Tools.bmp", L"Tools");

	Update_Rect();
}

int CAx::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CAx::Late_Update(void)
{
	return 0;
}

void CAx::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tools");

	//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
	GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		int(m_tRect.left),  // 복사 받을 위치 x좌표
		int(m_tRect.top),				   // 복사 받을 위치 y좌표
		(int)m_tInfo.fCX,			   // 복사 받을 이미지의 가로 사이즈
		(int)m_tInfo.fCY,			   // 복사 받을 이미지의 세로 사이즈
		hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		192,							   // 비트맵을 출력할 시작 좌표
		64,
		32,							   // 복사할 비트맵의 가로, 세로 사이즈
		32,
		RGB(255, 0, 255));			// 제거하고자하는 색상
}

void CAx::Release(void)
{
}
