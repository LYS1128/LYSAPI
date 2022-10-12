#include "stdafx.h"
#include "Gun.h"


CGun::CGun()
{
}


CGun::~CGun()
{
}

void CGun::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iItemID = GUN;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Gun.bmp", L"Gun");

	Update_Rect();
}

int CGun::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CGun::Late_Update(void)
{
	return 0;
}

void CGun::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Gun");

	//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
	GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
		int(m_tRect.left),  // ���� ���� ��ġ x��ǥ
		int(m_tRect.top),				   // ���� ���� ��ġ y��ǥ
		(int)m_tInfo.fCX,			   // ���� ���� �̹����� ���� ������
		(int)m_tInfo.fCY,			   // ���� ���� �̹����� ���� ������
		hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		0,							   // ��Ʈ���� ����� ���� ��ǥ
		0,
		32,							   // ������ ��Ʈ���� ����, ���� ������
		32,
		RGB(255, 0, 255));			// �����ϰ����ϴ� ����
}

void CGun::Release(void)
{
}
