#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{

}


CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_tInfo.fX = 304;
	m_tInfo.fY = 176;
	m_tInfo.fCX = 32;
	m_tInfo.fCY = 48;

	m_fSpeed = 0.5f;
	m_iDir = rand() % 4;
	m_iHp = 10;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Monster.bmp", L"Monster");

	m_pFrameKey = L"Monster";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	Update_Rect();
}

int CMonster::Update(void)
{
	Scene_Change();
	Move_Frame();

	Update_Rect();
	return 0;
}

int CMonster::Late_Update(void)
{
	return 0;
}

void CMonster::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Monster");

	//Ellipse(hDC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
	GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
		int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // ���� ���� ��ġ x��ǥ
		int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY()),				   // ���� ���� ��ġ y��ǥ
		32,			   // ���� ���� �̹����� ���� ������
		48,			   // ���� ���� �̹����� ���� ������
		hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		m_tFrame.iFrameStart * int(m_tInfo.fCX),							   // ��Ʈ���� ����� ���� ��ǥ
		m_tFrame.iFrameScene * int(m_tInfo.fCY),
		32,							   // ������ ��Ʈ���� ����, ���� ������
		48,
		RGB(255, 0, 255));			// �����ϰ����ϴ� ����
}

void CMonster::Release(void)
{
}

//////
void CMonster::Scene_Change()
{
	if (GetTickCount() % 100 == 0)
		m_iDir = rand() % 4;

		if(m_iDir == 0)
		{
			m_tInfo.fY -= m_fSpeed;
			m_tFrame.iFrameScene = 2;
		}

		else if (m_iDir == 1)
		{
			m_tInfo.fY += m_fSpeed;
			m_tFrame.iFrameScene = 0;
		}
		else if (m_iDir == 2)
		{
			m_tInfo.fX += m_fSpeed;
			m_tFrame.iFrameScene = 1;
		}
		else if (m_iDir == 3)
		{
			m_tInfo.fX -= m_fSpeed;
			m_tFrame.iFrameScene = 3;
		}
	

}
