#include "stdafx.h"
#include "Tree.h"

CTree::CTree()
	:m_Cut(0),m_iNum(6),m_Apple(false)
{
}


CTree::~CTree()
{
}

void CTree::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iItemID = TREE;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/TreeRoot.bmp", L"TreeRoot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Tree.bmp", L"Tree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Apple.bmp", L"Apple");

	Update_Rect();
}

int CTree::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CTree::Late_Update(void)
{
	return 0;
}

void CTree::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"TreeRoot");
	HDC	hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(L"Apple");

	//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
	GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // 복사 받을 위치 x좌표
		int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY()-16),				   // 복사 받을 위치 y좌표
		32,			   // 복사 받을 이미지의 가로 사이즈
		48,			   // 복사 받을 이미지의 세로 사이즈
		hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		32*m_Cut,							   // 비트맵을 출력할 시작 좌표
		0,
		32,							   // 복사할 비트맵의 가로, 세로 사이즈
		48,
		RGB(255, 0, 255));			// 제거하고자하는 색상

	if (m_Apple)
	{
		GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
			int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX() + 28),  // 복사 받을 위치 x좌표
			int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 54),				   // 복사 받을 위치 y좌표
			32,			   // 복사 받을 이미지의 가로 사이즈
			32,			   // 복사 받을 이미지의 세로 사이즈
			hMemDC1,						   // 현재 비트맵 이미지를 가지고 있는 dc
			0,							   // 비트맵을 출력할 시작 좌표
			0,
			32,							   // 복사할 비트맵의 가로, 세로 사이즈
			32,
			RGB(255, 0, 255));			// 제거하고자하는 색상
	}

	if (!m_Cut)
	{		
		HDC	hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(L"Tree");
		HDC Buff = CBmpMgr::Get_Instance()->Find_Image(L"Farm");

		RECT BuffRECT;
		RECT TreeRect = m_tRect;

		TreeRect.left += LONG(CScrollMgr::Get_Instance()->Get_ScrollX() - 32);
		TreeRect.top += LONG(CScrollMgr::Get_Instance()->Get_ScrollY() - 158);
		TreeRect.right = LONG(TreeRect.left + 96);
		TreeRect.bottom = LONG(TreeRect.top +162);



		if (IntersectRect(&BuffRECT, &(TreeRect), &(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front()->Get_Rect())))
		{
			BitBlt(Buff, 0, 0, 96, 162, hDC, int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX() - 32), int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 158), SRCCOPY);

			GdiTransparentBlt(Buff,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
				0,  // 복사 받을 위치 x좌표
				0,				   // 복사 받을 위치 y좌표
				96,			   // 복사 받을 이미지의 가로 사이즈
				162,			   // 복사 받을 이미지의 세로 사이즈
				hMemDC1,						   // 현재 비트맵 이미지를 가지고 있는 dc
				0,							   // 비트맵을 출력할 시작 좌표
				0,
				96,							   // 복사할 비트맵의 가로, 세로 사이즈
				162,
				RGB(255, 0, 255));			// 제거하고자하는 색상

			BLENDFUNCTION bf;
			bf.AlphaFormat = 0;
			bf.BlendFlags = 0;
			bf.BlendOp = AC_SRC_OVER;
			bf.SourceConstantAlpha = 100;

			AlphaBlend(hDC, int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX() - 32),
				int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 158), 96, 162, Buff, 0, 0, 96, 162, bf);
		}
		else
		{
			GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
				int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX() - 32),  // 복사 받을 위치 x좌표
				int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 158),				   // 복사 받을 위치 y좌표
				96,			   // 복사 받을 이미지의 가로 사이즈
				162,			   // 복사 받을 이미지의 세로 사이즈
				hMemDC1,						   // 현재 비트맵 이미지를 가지고 있는 dc
				0,							   // 비트맵을 출력할 시작 좌표
				0,
				96,							   // 복사할 비트맵의 가로, 세로 사이즈
				162,
				RGB(255, 0, 255));			// 제거하고자하는 색상
		}
	}


}

void CTree::Release(void)
{

}