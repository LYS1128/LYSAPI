#include "stdafx.h"
#include "Parsnip.h"



CParsnip::CParsnip()
{
}


CParsnip::~CParsnip()
{
}

void CParsnip::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iDrawID = 0;
	m_iNum = 1;
	m_iItemID = PARSNIP;
	m_Seed = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Parsnip.bmp", L"Parsnip");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/CropsGrow.bmp", L"CropsGrow");

	Update_Rect();
}

int CParsnip::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CParsnip::Late_Update(void)
{
	return 0;
}

void CParsnip::Render(HDC hDC)
{
	if (m_Seed)
	{
		HDC	hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(L"CropsGrow");

		//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());

		GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
			int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // 복사 받을 위치 x좌표
			int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 32),				   // 복사 받을 위치 y좌표
			32,			   // 복사 받을 이미지의 가로 사이즈
			64,			   // 복사 받을 이미지의 세로 사이즈
			hMemDC1,						   // 현재 비트맵 이미지를 가지고 있는 dc
			32 * m_iDrawID,							   // 비트맵을 출력할 시작 좌표
			0,
			32,							   // 복사할 비트맵의 가로, 세로 사이즈
			64,
			RGB(255, 0, 255));			// 제거하고자하는 색상
	}
	else
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Parsnip");

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
		if (m_iNum > 1)
		{
			TCHAR		szBuff[32] = L"";
			swprintf_s(szBuff, L"%d", m_iNum);

			SetBkMode(hDC, 1);
			SetTextColor(hDC, RGB(0, 0, 0));
			HFONT hFont, oldFont;
			hFont = CreateFont(10, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("Room No.703"));
			oldFont = (HFONT)SelectObject(hDC, hFont);
			TextOut(hDC, int(m_tRect.left + 18), int(m_tRect.top + 20), szBuff, lstrlen(szBuff));
		}
	}

}

void CParsnip::Release(void)
{
}
