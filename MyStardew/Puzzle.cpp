#include "stdafx.h"
#include "Puzzle.h"



CPuzzle::CPuzzle()
{
}


CPuzzle::~CPuzzle()
{
	Release();
}

void CPuzzle::Initialize(void)
{
	m_iDrawID = 0;
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iItemID = PUZZLE;
	PreSelect = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/PuzzleTile.bmp", L"PuzzleTile");

	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PuzzleTile");

	Update_Rect();
}

int CPuzzle::Update(void)
{


	Update_Rect();

	return OBJ_NOEVENT;
}

int CPuzzle::Late_Update(void)
{

	return 0;
}

void CPuzzle::Render(HDC hDC)
{

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
		RGB(255, 255, 255));			// �����ϰ����ϴ� ����
}

void CPuzzle::Release(void)
{
}

////////////////////////////////
