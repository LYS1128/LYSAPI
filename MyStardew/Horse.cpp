#include "stdafx.h"
#include "Horse.h"


CHorse::CHorse()
{

}


CHorse::~CHorse()
{
}

void CHorse::Initialize(void)
{
	m_tInfo.fX = 300;
	m_tInfo.fY = 300;
	m_tInfo.fCX = 32;
	m_tInfo.fCY = 32;

	m_fSpeed = 2.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Horse.bmp", L"Horse");

	m_pFrameKey = L"Horse";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	Update_Rect();
}

int CHorse::Update(void)
{
	Key_Input();

	Move_Frame();

	Update_Rect();
	return 0;
}

int CHorse::Late_Update(void)
{
	return 0;
}

void CHorse::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Horse");

	//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
	GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
		int(m_tRect.left -16),  // ���� ���� ��ġ x��ǥ
		int(m_tRect.top -40),				   // ���� ���� ��ġ y��ǥ
		64,			   // ���� ���� �̹����� ���� ������
		80,			   // ���� ���� �̹����� ���� ������
		hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		m_tFrame.iFrameStart * 64,							   // ��Ʈ���� ����� ���� ��ǥ
		0,
		64,							   // ������ ��Ʈ���� ����, ���� ������
		80,
		RGB(255, 0, 255));			// �����ϰ����ϴ� ����
}

void CHorse::Release(void)
{
}


/////////////////////////////////////////
void CHorse::Key_Input() {
	if (CKeyMgr::Get_Instance()->Key_Pressing('W') && (m_tRect.top > 155)) {
		if (CKeyMgr::Get_Instance()->Key_Pressing('A') && (m_tRect.left > 0)) {
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('D') && (m_tRect.right < WINCX)) {
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);

		}
		else {
			m_tInfo.fY -= m_fSpeed;
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('S') && (m_tRect.bottom < 475)) {
		if (CKeyMgr::Get_Instance()->Key_Pressing('A') && (m_tRect.left > 0)) {
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('D') && (m_tRect.right < WINCX)) {
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
		}
		else {
			m_tInfo.fY += m_fSpeed;
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('A') && (m_tRect.left > 0)) {
		m_tInfo.fX -= m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('D') && (m_tRect.right < WINCX)) {
		m_tInfo.fX += m_fSpeed;
	}
}