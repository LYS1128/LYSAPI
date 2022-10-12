#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{

}


CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_tInfo.fX = 304;
	m_tInfo.fY = 176;
	m_tInfo.fCX = 32;
	m_tInfo.fCY = 48;

	m_fSpeed = 0.5f;
	m_iDir = rand() % 4;
	m_iHp = 10;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Monster.bmp", L"Monster");

	m_pFrameKey = L"Monster";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	Update_Rect();
}

int CMonster::Update(void)
{
	Scene_Change();
	Move_Frame();

	Update_Rect();
	return 0;
}

int CMonster::Late_Update(void)
{
	return 0;
}

void CMonster::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Monster");

	//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
	GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // 복사 받을 위치 x좌표
		int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY()),				   // 복사 받을 위치 y좌표
		32,			   // 복사 받을 이미지의 가로 사이즈
		48,			   // 복사 받을 이미지의 세로 사이즈
		hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		m_tFrame.iFrameStart * int(m_tInfo.fCX),							   // 비트맵을 출력할 시작 좌표
		m_tFrame.iFrameScene * int(m_tInfo.fCY),
		32,							   // 복사할 비트맵의 가로, 세로 사이즈
		48,
		RGB(255, 0, 255));			// 제거하고자하는 색상
}

void CMonster::Release(void)
{
}

//////
void CMonster::Scene_Change()
{
	if (GetTickCount() % 100 == 0)
		m_iDir = rand() % 4;

		if(m_iDir == 0)
		{
			m_tInfo.fY -= m_fSpeed;
			m_tFrame.iFrameScene = 2;
		}

		else if (m_iDir == 1)
		{
			m_tInfo.fY += m_fSpeed;
			m_tFrame.iFrameScene = 0;
		}
		else if (m_iDir == 2)
		{
			m_tInfo.fX += m_fSpeed;
			m_tFrame.iFrameScene = 1;
		}
		else if (m_iDir == 3)
		{
			m_tInfo.fX -= m_fSpeed;
			m_tFrame.iFrameScene = 3;
		}
	

}
