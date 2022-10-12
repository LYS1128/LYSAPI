#include "stdafx.h"
#include "Rain.h"


CRain::CRain()
{
}


CRain::~CRain()
{
}

void CRain::Initialize(void)
{
	m_dwTime = GetTickCount();

	m_tInfo.fX = rand() % 1000 - 100;
	m_tInfo.fY = rand() % 700 -100;
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_fSpeed = 10.f + rand() % 5;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/rain.bmp", L"rain");

	Update_Rect();
}

int CRain::Update(void)
{
	m_tInfo.fX -= m_fSpeed*cos(45);
	m_tInfo.fY += m_fSpeed*sin(45);

	Update_Rect();

	return OBJ_NOEVENT;
}

int CRain::Late_Update(void)
{
	return 0;
}

void CRain::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"rain");

	//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
	GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
		int(m_tRect.left),  // ���� ���� ��ġ x��ǥ
		int(m_tRect.top),					   // ���� ���� ��ġ y��ǥ
		(int)m_tInfo.fCX,			   // ���� ���� �̹����� ���� ������
		(int)m_tInfo.fCY,			   // ���� ���� �̹����� ���� ������
		hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		0,							   // ��Ʈ���� ����� ���� ��ǥ
		0,
		64,							   // ������ ��Ʈ���� ����, ���� ������
		64,
		RGB(255, 0, 255));			// �����ϰ����ϴ� ����
}

void CRain::Release(void)
{
}
