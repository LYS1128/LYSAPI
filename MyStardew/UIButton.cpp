#include "stdafx.h"
#include "UIButton.h"



CUIButton::CUIButton()
	: m_iDrawID(0)
{
}


CUIButton::~CUIButton()
{
}

void CUIButton::Initialize(void)
{
	m_tInfo.fCX = 148.f;
	m_tInfo.fCY = 116.f;
}

int CUIButton::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CUIButton::Late_Update(void)
{
	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	if (PtInRect(&m_tRect, Pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(L"StartButton", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_HOUSE);

			/*else if(!lstrcmp(L"Button_Edit", m_pFrameKey))
			CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT);*/

			else if (!lstrcmp(L"EndButton", m_pFrameKey))
				DestroyWindow(g_hWnd);

			return 0;
		}

		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;

	return 0;
}

void CUIButton::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
		m_tRect.left,					// ���� ���� ��ġ x��ǥ
		m_tRect.top,				   // ���� ���� ��ġ y��ǥ
		(int)m_tInfo.fCX,			   // ���� ���� �̹����� ���� ������
		(int)m_tInfo.fCY,			   // ���� ���� �̹����� ���� ������
		hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		0,	  // ��Ʈ���� ����� ���� ��ǥ
		(int)m_tInfo.fCY * m_iDrawID,
		(int)m_tInfo.fCX,							   // ������ ��Ʈ���� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));			// �����ϰ����ϴ� ����
}

void CUIButton::Release(void)
{

}
