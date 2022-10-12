#include "stdafx.h"
#include "UIInven.h"


CUIInven::CUIInven()
	: m_iDrawID(0)
{
}


CUIInven::~CUIInven()
{
}

void CUIInven::Initialize(void)
{
	m_tInfo.fCX = 384.f;
	m_tInfo.fCY = 64.f;

	Update_Rect();
}

int CUIInven::Update(void)
{
	Update_Rect();
	return 0;
}

int CUIInven::Late_Update(void)
{
	return 0;
}

void CUIInven::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
		m_tRect.left,					// ���� ���� ��ġ x��ǥ
		m_tRect.top,				   // ���� ���� ��ġ y��ǥ
		(int)m_tInfo.fCX,			   // ���� ���� �̹����� ���� ������
		(int)m_tInfo.fCY+(64*m_iDrawID),			   // ���� ���� �̹����� ���� ������
		hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		0,	  // ��Ʈ���� ����� ���� ��ǥ
		(64 * m_iDrawID),
		(int)m_tInfo.fCX,							   // ������ ��Ʈ���� ����, ���� ������
		(int)m_tInfo.fCY + (64 * m_iDrawID),
		RGB(255, 0, 255));			// �����ϰ����ϴ� ����
}

void CUIInven::Release(void)
{
}
