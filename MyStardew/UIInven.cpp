#include "stdafx.h"
#include "UIInven.h"


CUIInven::CUIInven()
	: m_iDrawID(0)
{
}


CUIInven::~CUIInven()
{
}

void CUIInven::Initialize(void)
{
	m_tInfo.fCX = 384.f;
	m_tInfo.fCY = 64.f;

	Update_Rect();
}

int CUIInven::Update(void)
{
	Update_Rect();
	return 0;
}

int CUIInven::Late_Update(void)
{
	return 0;
}

void CUIInven::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		m_tRect.left,					// 복사 받을 위치 x좌표
		m_tRect.top,				   // 복사 받을 위치 y좌표
		(int)m_tInfo.fCX,			   // 복사 받을 이미지의 가로 사이즈
		(int)m_tInfo.fCY+(64*m_iDrawID),			   // 복사 받을 이미지의 세로 사이즈
		hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		0,	  // 비트맵을 출력할 시작 좌표
		(64 * m_iDrawID),
		(int)m_tInfo.fCX,							   // 복사할 비트맵의 가로, 세로 사이즈
		(int)m_tInfo.fCY + (64 * m_iDrawID),
		RGB(255, 0, 255));			// 제거하고자하는 색상
}

void CUIInven::Release(void)
{
}
