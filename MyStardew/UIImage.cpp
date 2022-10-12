#include "stdafx.h"
#include "UIImage.h"


CUIImage::CUIImage()
{
}

CUIImage::~CUIImage()
{
}

void CUIImage::Initialize(void)
{
	m_tInfo.fCX = 640.f;
	m_tInfo.fCY = 299.f;
}

int CUIImage::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CUIImage::Late_Update(void)
{
	return 0;
}

void CUIImage::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
		m_tRect.left,					// ���� ���� ��ġ x��ǥ
		m_tRect.top,				   // ���� ���� ��ġ y��ǥ
		(int)m_tInfo.fCX,			   // ���� ���� �̹����� ���� ������
		(int)m_tInfo.fCY,			   // ���� ���� �̹����� ���� ������
		hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		0,	  // ��Ʈ���� ����� ���� ��ǥ
		0,
		(int)m_tInfo.fCX,							   // ������ ��Ʈ���� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));			// �����ϰ����ϴ� ����
}

void CUIImage::Release(void)
{
}

//////////////////////////////////////////

