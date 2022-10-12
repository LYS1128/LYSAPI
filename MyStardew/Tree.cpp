#include "stdafx.h"
#include "Tree.h"

CTree::CTree()
	:m_Cut(0),m_iNum(6),m_Apple(false)
{
}


CTree::~CTree()
{
}

void CTree::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iItemID = TREE;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/TreeRoot.bmp", L"TreeRoot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Tree.bmp", L"Tree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Apple.bmp", L"Apple");

	Update_Rect();
}

int CTree::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CTree::Late_Update(void)
{
	return 0;
}

void CTree::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"TreeRoot");
	HDC	hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(L"Apple");

	//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
	GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
		int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // ���� ���� ��ġ x��ǥ
		int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY()-16),				   // ���� ���� ��ġ y��ǥ
		32,			   // ���� ���� �̹����� ���� ������
		48,			   // ���� ���� �̹����� ���� ������
		hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		32*m_Cut,							   // ��Ʈ���� ����� ���� ��ǥ
		0,
		32,							   // ������ ��Ʈ���� ����, ���� ������
		48,
		RGB(255, 0, 255));			// �����ϰ����ϴ� ����

	if (m_Apple)
	{
		GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
			int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX() + 28),  // ���� ���� ��ġ x��ǥ
			int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 54),				   // ���� ���� ��ġ y��ǥ
			32,			   // ���� ���� �̹����� ���� ������
			32,			   // ���� ���� �̹����� ���� ������
			hMemDC1,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
			0,							   // ��Ʈ���� ����� ���� ��ǥ
			0,
			32,							   // ������ ��Ʈ���� ����, ���� ������
			32,
			RGB(255, 0, 255));			// �����ϰ����ϴ� ����
	}

	if (!m_Cut)
	{		
		HDC	hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(L"Tree");
		HDC Buff = CBmpMgr::Get_Instance()->Find_Image(L"Farm");

		RECT BuffRECT;
		RECT TreeRect = m_tRect;

		TreeRect.left += LONG(CScrollMgr::Get_Instance()->Get_ScrollX() - 32);
		TreeRect.top += LONG(CScrollMgr::Get_Instance()->Get_ScrollY() - 158);
		TreeRect.right = LONG(TreeRect.left + 96);
		TreeRect.bottom = LONG(TreeRect.top +162);



		if (IntersectRect(&BuffRECT, &(TreeRect), &(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front()->Get_Rect())))
		{
			BitBlt(Buff, 0, 0, 96, 162, hDC, int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX() - 32), int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 158), SRCCOPY);

			GdiTransparentBlt(Buff,			   // ������� dc, ���������� �׸��� �׸� dc
				0,  // ���� ���� ��ġ x��ǥ
				0,				   // ���� ���� ��ġ y��ǥ
				96,			   // ���� ���� �̹����� ���� ������
				162,			   // ���� ���� �̹����� ���� ������
				hMemDC1,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
				0,							   // ��Ʈ���� ����� ���� ��ǥ
				0,
				96,							   // ������ ��Ʈ���� ����, ���� ������
				162,
				RGB(255, 0, 255));			// �����ϰ����ϴ� ����

			BLENDFUNCTION bf;
			bf.AlphaFormat = 0;
			bf.BlendFlags = 0;
			bf.BlendOp = AC_SRC_OVER;
			bf.SourceConstantAlpha = 100;

			AlphaBlend(hDC, int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX() - 32),
				int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 158), 96, 162, Buff, 0, 0, 96, 162, bf);
		}
		else
		{
			GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
				int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX() - 32),  // ���� ���� ��ġ x��ǥ
				int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 158),				   // ���� ���� ��ġ y��ǥ
				96,			   // ���� ���� �̹����� ���� ������
				162,			   // ���� ���� �̹����� ���� ������
				hMemDC1,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
				0,							   // ��Ʈ���� ����� ���� ��ǥ
				0,
				96,							   // ������ ��Ʈ���� ����, ���� ������
				162,
				RGB(255, 0, 255));			// �����ϰ����ϴ� ����
		}
	}


}

void CTree::Release(void)
{

}