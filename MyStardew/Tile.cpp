#include "stdafx.h"
#include "Tile.h"



CTile::CTile()
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_iDrawID = 0;
	m_iOption = 0;
	m_Select = false;

	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/Collision.bmp", L"Collision");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/SelectTile.bmp", L"SelectTile");

	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Collision");

	Update_Rect();
}

int CTile::Update(void)
{


	Update_Rect();

	return OBJ_NOEVENT;
}

int CTile::Late_Update(void)
{

	return 0;
}

void CTile::Render(HDC hDC)
{

		//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
		//GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		//int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // 복사 받을 위치 x좌표
		//int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY()),				   // 복사 받을 위치 y좌표
		//(int)m_tInfo.fCX,			   // 복사 받을 이미지의 가로 사이즈
		//(int)m_tInfo.fCY,			   // 복사 받을 이미지의 세로 사이즈
		//hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		//TILECX * m_iDrawID,							   // 비트맵을 출력할 시작 좌표
		//0,
		//32,							   // 복사할 비트맵의 가로, 세로 사이즈
		//32,
		//RGB(255, 0, 255));			// 제거하고자하는 색상

		if (m_Select)
		{
			HDC	hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(L"SelectTile");

			GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
				int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  				// 복사 받을 위치 x좌표
				int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY()),				   // 복사 받을 위치 y좌표
				(int)m_tInfo.fCX,			   // 복사 받을 이미지의 가로 사이즈
				(int)m_tInfo.fCY,			   // 복사 받을 이미지의 세로 사이즈
				hMemDC1,						   // 현재 비트맵 이미지를 가지고 있는 dc
				0,	  // 비트맵을 출력할 시작 좌표
				0,
				32,							   // 복사할 비트맵의 가로, 세로 사이즈
				32,
				RGB(255, 0, 255));			// 제거하고자하는 색상
		}
}

void CTile::Release(void)
{
}

////////////////////////////////

