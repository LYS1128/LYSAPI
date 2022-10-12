#include "stdafx.h"
#include "Ending.h"


CEnding::CEnding()
{
}


CEnding::~CEnding()
{
	Release();
}

void CEnding::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ending.bmp", L"Ending");
}

void CEnding::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySoundW(L"05Ending.wav", CSoundMgr::BGM, 0.1f);
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		DestroyWindow(g_hWnd);
	}
}

void CEnding::Late_Update(void)
{
}

void CEnding::Render(HDC _DC)
{
	HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Ending");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
}

void CEnding::Release(void)
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CObjMgr::Get_Instance()->Delete_ID(PLAYER);
}