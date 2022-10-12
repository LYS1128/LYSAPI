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
	GdiTransparentBlt(_DC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		int(m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX()),  // 복사 받을 위치 x좌표
		int(m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY()),						   // 복사 받을 위치 y좌표
		(int)m_tInfo.fCX,			   // 복사 받을 이미지의 가로 사이즈
		(int)m_tInfo.fCY,			   // 복사 받을 이미지의 세로 사이즈
		hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		0,							   // 비트맵을 출력할 시작 좌표
		0,
		5,							   // 복사할 비트맵의 가로, 세로 사이즈
		5,
		RGB(255, 0, 255));			// 제거하고자하는 색상
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