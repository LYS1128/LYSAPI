#include "stdafx.h"
#include "Night.h"


CNight::CNight()
{
}


CNight::~CNight()
{
	Release();
}

void CNight::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Night.bmp", L"Night");
	m_iTime = GetTickCount();
	CScrollMgr::Get_Instance()->Set_ScrollX(-1744);
	CScrollMgr::Get_Instance()->Set_ScrollY(-160);

	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Day(1);
}

void CNight::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySoundW(L"04Night.wav", CSoundMgr::BGM, 0.1f);
	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Ending())
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_ENDING);
		return;
	}
	else if (!(dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Ending()) && GetTickCount() - m_iTime > 2000)
	{
		
		CSceneMgr::Get_Instance()->Scene_Change(SC_HOUSE);
	}
}

void CNight::Late_Update(void)
{
}

void CNight::Render(HDC _DC)
{
	HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Night");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
}

void CNight::Release(void)
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
}
