#include "stdafx.h"
#include "Crystal.h"



CCrystal::CCrystal()
{
}


CCrystal::~CCrystal()
{
}

void CCrystal::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iNum = 1;
	m_iItemID = CRYSTAL;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Crystal.bmp", L"Crystal");

	Update_Rect();
}

int CCrystal::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CCrystal::Late_Update(void)
{
	return 0;
}

void CCrystal::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Crystal");


	//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
	GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
		int(m_tRect.left),  // ���� ���� ��ġ x��ǥ
		int(m_tRect.top),					   // ���� ���� ��ġ y��ǥ
		(int)m_tInfo.fCX,			   // ���� ���� �̹����� ���� ������
		(int)m_tInfo.fCY,			   // ���� ���� �̹����� ���� ������
		hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		0,							   // ��Ʈ���� ����� ���� ��ǥ
		0,
		32,							   // ������ ��Ʈ���� ����, ���� ������
		32,
		RGB(255, 0, 255));			// �����ϰ����ϴ� ����

	if (m_iNum > 1)
	{
		TCHAR		szBuff[32] = L"";
		swprintf_s(szBuff, L"%d", m_iNum);

		SetBkMode(hDC, 1);
		SetTextColor(hDC, RGB(0, 0, 0));
		HFONT hFont, oldFont;
		hFont = CreateFont(10, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("Room No.703"));
		oldFont = (HFONT)SelectObject(hDC, hFont);
		TextOut(hDC, int(m_tRect.left + 18), int(m_tRect.top + 20), szBuff, lstrlen(szBuff));
	}
}

void CCrystal::Release(void)
{
}