#include "stdafx.h"
#include "Bullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}

void CBullet::Initialize() {

	m_tInfo.fX = CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front()->Get_Info().fX;
	m_tInfo.fY = CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front()->Get_Info().fY;

	m_tInfo.fCX = 5.f;
	m_tInfo.fCY = 5.f;
	m_fSpeed = 4.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Bullet.bmp", L"Bullet");

	Update_Rect();

}

int CBullet::Update() {
	m_tInfo.fX += m_fSpeed*m_cos;
	m_tInfo.fY += m_fSpeed*m_sin;
	Update_Rect();
	return 0;
}

int CBullet::Late_Update() {

	return 0;
}

void CBullet::Render(HDC _DC) {
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Bullet");



	//Ellipse(_DC, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
	GdiTransparentBlt(_DC,			   // ������� dc, ���������� �׸��� �׸� dc
		int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // ���� ���� ��ġ x��ǥ
		int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY()),						   // ���� ���� ��ġ y��ǥ
		(int)m_tInfo.fCX,			   // ���� ���� �̹����� ���� ������
		(int)m_tInfo.fCY,			   // ���� ���� �̹����� ���� ������
		hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		0,							   // ��Ʈ���� ����� ���� ��ǥ
		0,
		5,							   // ������ ��Ʈ���� ����, ���� ������
		5,
		RGB(255, 0, 255));			// �����ϰ����ϴ� ����
}

void CBullet::Release()
{
}

/////////////////////////////////////////

void CBullet::Set_Pos(float _fX, float _fY) {
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}

void CBullet::Set_Tri(float _Sin, float _Cos) {
	m_sin = _Sin;
	m_cos = _Cos;
}

void CBullet::Set_Speed(float _Speed)
{
	m_fSpeed = _Speed;
}

void CBullet::Set_Size(float _Size)
{
	m_tInfo.fCX = _Size;
	m_tInfo.fCY = _Size;
}