#include "stdafx.h"
#include "MainGame.h"

CMainGame::CMainGame()
	: m_iFPS(0)
	, m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 32);	
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackBuff.bmp", L"Back");
	CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);

	CSoundMgr::Get_Instance()->Initialize();

	srand((unsigned int)time(NULL));
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CMainGame::Render(void)
{
	HDC		hBackBufferDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");
	CSceneMgr::Get_Instance()->Render(hBackBufferDC);
	BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackBufferDC, 0, 0, SRCCOPY);

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}


}

void CMainGame::Release(void)
{
	CSceneMgr::Get_Instance()->Destroy_Instance();
	for (int i = 0; i < END; ++i)
	{
		CObjMgr::Get_Instance()->Delete_ID(PLAYER);
	}
	
	CObjMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CTileMgr::Get_Instance()->Destroy_Instance();
	CCollisionMgr::Get_Instance()->Destroy_Instance();
	CInvenMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}
