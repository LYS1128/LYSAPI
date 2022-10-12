#include "stdafx.h"
#include "Kirby.h"


CKirby::CKirby()
{

}


CKirby::~CKirby()
{
}

void CKirby::Initialize(void)
{
	m_tInfo.fX = 850;
	m_tInfo.fY = rand() % 288 + 171;
	m_tInfo.fCX = 64;
	m_tInfo.fCY = 64;

	m_fSpeed = 7.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Kirby.bmp", L"Kirby");

	m_pFrameKey = L"Kirby";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 18;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	Update_Rect();
}

int CKirby::Update(void)
{
	m_tInfo.fX -= m_fSpeed;

	Move_Frame();

	Update_Rect();
	return 0;
}

int CKirby::Late_Update(void)
{
	return 0;
}

void CKirby::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Kirby");

	//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom );
	GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
		int(m_tRect.left),  // ���� ���� ��ġ x��ǥ
		int(m_tRect.top),				   // ���� ���� ��ġ y��ǥ
		64,			   // ���� ���� �̹����� ���� ������
		64,			   // ���� ���� �̹����� ���� ������
		hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		m_tFrame.iFrameStart * 32,							   // ��Ʈ���� ����� ���� ��ǥ
		0,
		32,							   // ������ ��Ʈ���� ����, ���� ������
		32,
		RGB(207, 176, 255));			// �����ϰ����ϴ� ����
}

void CKirby::Release(void)
{
}


/////////////////////////////////////////