#include "stdafx.h"
#include "Ban.h"



CBan::CBan()
{
}


CBan::~CBan()
{
	Release();
}

void CBan::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iItemID = BAN;
	PreSelect = true;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Ban.bmp", L"Ban");

	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ban");

	Update_Rect();
}

int CBan::Update(void)
{


	Update_Rect();

	return OBJ_NOEVENT;
}

int CBan::Late_Update(void)
{

	return 0;
}

void CBan::Render(HDC hDC)
{
	if (PreSelect)
	{
		//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
		GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
			int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // ���� ���� ��ġ x��ǥ
			int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY()),				   // ���� ���� ��ġ y��ǥ
			(int)m_tInfo.fCX,			   // ���� ���� �̹����� ���� ������
			(int)m_tInfo.fCY,			   // ���� ���� �̹����� ���� ������
			hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
			0,							   // ��Ʈ���� ����� ���� ��ǥ
			0,
			32,							   // ������ ��Ʈ���� ����, ���� ������
			32,
			RGB(255, 0, 255));			// �����ϰ����ϴ� ����
	}
}

void CBan::Release(void)
{
}

////////////////////////////////
