#include "stdafx.h"
#include "UIButton.h"



CUIButton::CUIButton()
	: m_iDrawID(0)
{
}


CUIButton::~CUIButton()
{
}

void CUIButton::Initialize(void)
{
	m_tInfo.fCX = 148.f;
	m_tInfo.fCY = 116.f;
}

int CUIButton::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CUIButton::Late_Update(void)
{
	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	if (PtInRect(&m_tRect, Pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(L"StartButton", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_HOUSE);

			/*else if(!lstrcmp(L"Button_Edit", m_pFrameKey))
			CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT);*/

			else if (!lstrcmp(L"EndButton", m_pFrameKey))
				DestroyWindow(g_hWnd);

			return 0;
		}

		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;

	return 0;
}

void CUIButton::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		m_tRect.left,					// 복사 받을 위치 x좌표
		m_tRect.top,				   // 복사 받을 위치 y좌표
		(int)m_tInfo.fCX,			   // 복사 받을 이미지의 가로 사이즈
		(int)m_tInfo.fCY,			   // 복사 받을 이미지의 세로 사이즈
		hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		0,	  // 비트맵을 출력할 시작 좌표
		(int)m_tInfo.fCY * m_iDrawID,
		(int)m_tInfo.fCX,							   // 복사할 비트맵의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));			// 제거하고자하는 색상
}

void CUIButton::Release(void)
{

}
