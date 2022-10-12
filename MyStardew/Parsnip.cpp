#include "stdafx.h"
#include "Parsnip.h"



CParsnip::CParsnip()
{
}


CParsnip::~CParsnip()
{
}

void CParsnip::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iDrawID = 0;
	m_iNum = 1;
	m_iItemID = PARSNIP;
	m_Seed = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Parsnip.bmp", L"Parsnip");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/CropsGrow.bmp", L"CropsGrow");

	Update_Rect();
}

int CParsnip::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CParsnip::Late_Update(void)
{
	return 0;
}

void CParsnip::Render(HDC hDC)
{
	if (m_Seed)
	{
		HDC	hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(L"CropsGrow");

		//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());

		GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
			int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // ���� ���� ��ġ x��ǥ
			int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY() - 32),				   // ���� ���� ��ġ y��ǥ
			32,			   // ���� ���� �̹����� ���� ������
			64,			   // ���� ���� �̹����� ���� ������
			hMemDC1,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
			32 * m_iDrawID,							   // ��Ʈ���� ����� ���� ��ǥ
			0,
			32,							   // ������ ��Ʈ���� ����, ���� ������
			64,
			RGB(255, 0, 255));			// �����ϰ����ϴ� ����
	}
	else
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Parsnip");

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

}

void CParsnip::Release(void)
{
}
