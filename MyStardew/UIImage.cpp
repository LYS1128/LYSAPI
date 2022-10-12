#include "stdafx.h"
#include "UIImage.h"


CUIImage::CUIImage()
{
}

CUIImage::~CUIImage()
{
}

void CUIImage::Initialize(void)
{
	m_tInfo.fCX = 640.f;
	m_tInfo.fCY = 299.f;
}

int CUIImage::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CUIImage::Late_Update(void)
{
	return 0;
}

void CUIImage::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		m_tRect.left,					// 복사 받을 위치 x좌표
		m_tRect.top,				   // 복사 받을 위치 y좌표
		(int)m_tInfo.fCX,			   // 복사 받을 이미지의 가로 사이즈
		(int)m_tInfo.fCY,			   // 복사 받을 이미지의 세로 사이즈
		hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		0,	  // 비트맵을 출력할 시작 좌표
		0,
		(int)m_tInfo.fCX,							   // 복사할 비트맵의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));			// 제거하고자하는 색상
}

void CUIImage::Release(void)
{
}

//////////////////////////////////////////

