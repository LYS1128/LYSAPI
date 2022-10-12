
#include "stdafx.h"
#include "Box.h"



CBox::CBox()
	:m_Seed(1)
{
}


CBox::~CBox()
{
}

void CBox::Initialize(void)
{

	m_tInfo.fX = 850;
	m_tInfo.fY = rand() % 288 + 171;
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iNum = 1;
	m_iItemID = BOX;
	m_fSpeed = 5.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Box.bmp", L"Box");

	Update_Rect();
}

int CBox::Update(void)
{
	if (m_Seed)
		m_tInfo.fX -= m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

int CBox::Late_Update(void)
{
	return 0;
}

void CBox::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Box");



	//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
	GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		int(m_tRect.left),  // 복사 받을 위치 x좌표
		int(m_tRect.top),					   // 복사 받을 위치 y좌표
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

void CBox::Release(void)
{
}