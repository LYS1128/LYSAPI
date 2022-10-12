#include "stdafx.h"
#include "Kirby.h"


CKirby::CKirby()
{

}


CKirby::~CKirby()
{
}

void CKirby::Initialize(void)
{
	m_tInfo.fX = 850;
	m_tInfo.fY = rand() % 288 + 171;
	m_tInfo.fCX = 64;
	m_tInfo.fCY = 64;

	m_fSpeed = 7.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Kirby.bmp", L"Kirby");

	m_pFrameKey = L"Kirby";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 18;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	Update_Rect();
}

int CKirby::Update(void)
{
	m_tInfo.fX -= m_fSpeed;

	Move_Frame();

	Update_Rect();
	return 0;
}

int CKirby::Late_Update(void)
{
	return 0;
}

void CKirby::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Kirby");

	//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom );
	GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		int(m_tRect.left),  // 복사 받을 위치 x좌표
		int(m_tRect.top),				   // 복사 받을 위치 y좌표
		64,			   // 복사 받을 이미지의 가로 사이즈
		64,			   // 복사 받을 이미지의 세로 사이즈
		hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		m_tFrame.iFrameStart * 32,							   // 비트맵을 출력할 시작 좌표
		0,
		32,							   // 복사할 비트맵의 가로, 세로 사이즈
		32,
		RGB(207, 176, 255));			// 제거하고자하는 색상
}

void CKirby::Release(void)
{
}


/////////////////////////////////////////