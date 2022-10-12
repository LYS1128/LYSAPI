#include "stdafx.h"
#include "Keg.h"


CKeg::CKeg()
	:m_Parsnip(false),m_Pickle(false)
{
}


CKeg::~CKeg()
{
}

void CKeg::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iItemID = KEG;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Keg.bmp", L"Keg");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Input.bmp", L"Input");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Done.bmp", L"Done");


	Update_Rect();
}

int CKeg::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CKeg::Late_Update(void)
{
	return 0;
}

void CKeg::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Keg");
	

	GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
		int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // ���� ���� ��ġ x��ǥ
		int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 32),				   // ���� ���� ��ġ y��ǥ
		32,			   // ���� ���� �̹����� ���� ������
		64,			   // ���� ���� �̹����� ���� ������
		hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		0,							   // ��Ʈ���� ����� ���� ��ǥ
		0,
		32,							   // ������ ��Ʈ���� ����, ���� ������
		64,
		RGB(255, 0, 255));			// �����ϰ����ϴ� ����

	if (m_Parsnip)
	{
		HDC	hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(L"Input");
		GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
			int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // ���� ���� ��ġ x��ǥ
			int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 64),				   // ���� ���� ��ġ y��ǥ
			32,			   // ���� ���� �̹����� ���� ������
			38,			   // ���� ���� �̹����� ���� ������
			hMemDC1,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
			0,							   // ��Ʈ���� ����� ���� ��ǥ
			0,
			32,							   // ������ ��Ʈ���� ����, ���� ������
			38,
			RGB(255, 0, 255));			// �����ϰ����ϴ� ����
	}

	if (m_Pickle)
	{
		HDC	hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(L"Done");
		GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
			int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // ���� ���� ��ġ x��ǥ
			int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 64),				   // ���� ���� ��ġ y��ǥ
			32,			   // ���� ���� �̹����� ���� ������
			38,			   // ���� ���� �̹����� ���� ������
			hMemDC1,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
			0,							   // ��Ʈ���� ����� ���� ��ǥ
			0,
			32,							   // ������ ��Ʈ���� ����, ���� ������
			38,
			RGB(255, 0, 255));			// �����ϰ����ϴ� ����
	}
}

void CKeg::Release(void)
{
}
