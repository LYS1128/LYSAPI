#include "stdafx.h"
#include "Tile.h"



CTile::CTile()
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_iDrawID = 0;
	m_iOption = 0;
	m_Select = false;

	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/Collision.bmp", L"Collision");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/SelectTile.bmp", L"SelectTile");

	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Collision");

	Update_Rect();
}

int CTile::Update(void)
{


	Update_Rect();

	return OBJ_NOEVENT;
}

int CTile::Late_Update(void)
{

	return 0;
}

void CTile::Render(HDC hDC)
{

		//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
		//GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
		//int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // ���� ���� ��ġ x��ǥ
		//int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY()),				   // ���� ���� ��ġ y��ǥ
		//(int)m_tInfo.fCX,			   // ���� ���� �̹����� ���� ������
		//(int)m_tInfo.fCY,			   // ���� ���� �̹����� ���� ������
		//hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		//TILECX * m_iDrawID,							   // ��Ʈ���� ����� ���� ��ǥ
		//0,
		//32,							   // ������ ��Ʈ���� ����, ���� ������
		//32,
		//RGB(255, 0, 255));			// �����ϰ����ϴ� ����

		if (m_Select)
		{
			HDC	hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(L"SelectTile");

			GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
				int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  				// ���� ���� ��ġ x��ǥ
				int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY()),				   // ���� ���� ��ġ y��ǥ
				(int)m_tInfo.fCX,			   // ���� ���� �̹����� ���� ������
				(int)m_tInfo.fCY,			   // ���� ���� �̹����� ���� ������
				hMemDC1,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
				0,	  // ��Ʈ���� ����� ���� ��ǥ
				0,
				32,							   // ������ ��Ʈ���� ����, ���� ������
				32,
				RGB(255, 0, 255));			// �����ϰ����ϴ� ����
		}
}

void CTile::Release(void)
{
}

////////////////////////////////

