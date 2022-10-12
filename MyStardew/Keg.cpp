#include "stdafx.h"
#include "Keg.h"


CKeg::CKeg()
	:m_Parsnip(false),m_Pickle(false)
{
}


CKeg::~CKeg()
{
}

void CKeg::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iItemID = KEG;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Keg.bmp", L"Keg");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Input.bmp", L"Input");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Done.bmp", L"Done");


	Update_Rect();
}

int CKeg::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CKeg::Late_Update(void)
{
	return 0;
}

void CKeg::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Keg");
	

	GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // 복사 받을 위치 x좌표
		int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 32),				   // 복사 받을 위치 y좌표
		32,			   // 복사 받을 이미지의 가로 사이즈
		64,			   // 복사 받을 이미지의 세로 사이즈
		hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		0,							   // 비트맵을 출력할 시작 좌표
		0,
		32,							   // 복사할 비트맵의 가로, 세로 사이즈
		64,
		RGB(255, 0, 255));			// 제거하고자하는 색상

	if (m_Parsnip)
	{
		HDC	hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(L"Input");
		GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
			int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // 복사 받을 위치 x좌표
			int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 64),				   // 복사 받을 위치 y좌표
			32,			   // 복사 받을 이미지의 가로 사이즈
			38,			   // 복사 받을 이미지의 세로 사이즈
			hMemDC1,						   // 현재 비트맵 이미지를 가지고 있는 dc
			0,							   // 비트맵을 출력할 시작 좌표
			0,
			32,							   // 복사할 비트맵의 가로, 세로 사이즈
			38,
			RGB(255, 0, 255));			// 제거하고자하는 색상
	}

	if (m_Pickle)
	{
		HDC	hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(L"Done");
		GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
			int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // 복사 받을 위치 x좌표
			int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 64),				   // 복사 받을 위치 y좌표
			32,			   // 복사 받을 이미지의 가로 사이즈
			38,			   // 복사 받을 이미지의 세로 사이즈
			hMemDC1,						   // 현재 비트맵 이미지를 가지고 있는 dc
			0,							   // 비트맵을 출력할 시작 좌표
			0,
			32,							   // 복사할 비트맵의 가로, 세로 사이즈
			38,
			RGB(255, 0, 255));			// 제거하고자하는 색상
	}
}

void CKeg::Release(void)
{
}
