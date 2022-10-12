#include "stdafx.h"
#include "MyMenu.h"



CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	m_pBmgMgr->Insert_Bmp(L"../Image/Menu/MenuSky.bmp", L"MenuSky");
	m_pBmgMgr->Insert_Bmp(L"../Image/Menu/TitleImg.bmp", L"TitleImg");


	m_pBmgMgr->Insert_Bmp(L"../Image/Menu/StartButton.bmp", L"StartButton");
	m_pBmgMgr->Insert_Bmp(L"../Image/Menu/EndButton.bmp", L"EndButton");

	CObj* pObj = CAbstractFactory<CUIImage>::Create(400.f, 200.f);
	pObj->Set_FrameKey(L"TitleImg");
	CObjMgr::Get_Instance()->Add_Object(UIIMG, pObj);

	pObj = CAbstractFactory<CUIButton>::Create(300.f, 450.f);
	pObj->Set_FrameKey(L"StartButton");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CUIButton>::Create(500.f, 450.f);
	pObj->Set_FrameKey(L"EndButton");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);
}

void CMyMenu::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySoundW(L"00MainMenu.wav", CSoundMgr::BGM, 0.1f);
	CObjMgr::Get_Instance()->Update();
}

void CMyMenu::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC _DC)
{
	HDC		hMemDC = m_pBmgMgr->Find_Image(L"MenuSky");

	BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	CObjMgr::Get_Instance()->Render(_DC);
}

void CMyMenu::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(BUTTON);
	CObjMgr::Get_Instance()->Delete_ID(UIIMG);
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
}
