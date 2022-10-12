#include "stdafx.h"
#include "Ax.h"



CAx::CAx()
{
}


CAx::~CAx()
{
}

void CAx::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iItemID = AX;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Tools.bmp", L"Tools");

	Update_Rect();
}

int CAx::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CAx::Late_Update(void)
{
	return 0;
}

void CAx::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tools");

	//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
	GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
		int(m_tRect.left),  // ���� ���� ��ġ x��ǥ
		int(m_tRect.top),				   // ���� ���� ��ġ y��ǥ
		(int)m_tInfo.fCX,			   // ���� ���� �̹����� ���� ������
		(int)m_tInfo.fCY,			   // ���� ���� �̹����� ���� ������
		hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		192,							   // ��Ʈ���� ����� ���� ��ǥ
		64,
		32,							   // ������ ��Ʈ���� ����, ���� ������
		32,
		RGB(255, 0, 255));			// �����ϰ����ϴ� ����
}

void CAx::Release(void)
{
}
