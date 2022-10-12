#include "stdafx.h"
#include "Dirt.h"


CDirt::CDirt()
{
}


CDirt::~CDirt()
{
	Release();
}

void CDirt::Initialize(void)
{
	m_iDrawID = 0;
	m_iOption = 0;
	m_Water = false;

	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/DirtTile.bmp", L"DirtTile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/WaterTile.bmp", L"WaterTile");

	Update_Rect();
}

int CDirt::Update(void)
{

	Update_Rect();

	return OBJ_NOEVENT;
}

int CDirt::Late_Update(void)
{
	return 0;
}

void CDirt::Render(HDC hDC)
{
	if (m_Water)
	{
		HDC	hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(L"WaterTile");

		GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
			int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  				// ���� ���� ��ġ x��ǥ
			int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY()),				   // ���� ���� ��ġ y��ǥ
			(int)m_tInfo.fCX,			   // ���� ���� �̹����� ���� ������
			(int)m_tInfo.fCY,			   // ���� ���� �̹����� ���� ������
			hMemDC1,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
			TILECX * m_iDrawID,	  // ��Ʈ���� ����� ���� ��ǥ
			0,
			32,							   // ������ ��Ʈ���� ����, ���� ������
			32,
			RGB(255, 0, 255));			// �����ϰ����ϴ� ����
	}
	else
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"DirtTile");

		//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
		GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
			int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // ���� ���� ��ġ x��ǥ
			int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY()),				   // ���� ���� ��ġ y��ǥ
			(int)m_tInfo.fCX,			   // ���� ���� �̹����� ���� ������
			(int)m_tInfo.fCY,			   // ���� ���� �̹����� ���� ������
			hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
			TILECX * m_iDrawID,							   // ��Ʈ���� ����� ���� ��ǥ
			0,
			32,							   // ������ ��Ʈ���� ����, ���� ������
			32,
			RGB(255, 0, 255));			// �����ϰ����ϴ� ����
	}

}

void CDirt::Release(void)
{
}
