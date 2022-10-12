#include "stdafx.h"
#include "UnderMgr.h"

CUnderMgr*	CUnderMgr::m_pInstance = NULL;

CUnderMgr::CUnderMgr()
{
}


CUnderMgr::~CUnderMgr()
{
}

void CUnderMgr::Initialize(void)
{
	Exit.left = 625; Exit.top = 284; Exit.right = 688; Exit.bottom = 347;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/TemmieTalk.bmp", L"TemmieTalk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/TemmieTalk2.bmp", L"TemmieTalk2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/TemmieTalk3.bmp", L"TemmieTalk3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/SansTalk.bmp", L"SansTalk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/PapirusTalk.bmp", L"PapirusTalk");

	
}

void CUnderMgr::Update(void)
{
	if (TalkOption == 11)
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"TemmieTalk");
	else if (TalkOption == 12)
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"TemmieTalk2");
	else if (TalkOption == 13)
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"TemmieTalk3");
	else if (TalkOption == 14)
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SansTalk");
	else if (TalkOption == 15)
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PapirusTalk");

	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	if (PtInRect(&Exit, Pt)) //종료버튼
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_TalkUnder(false);
		}
	}

}

void CUnderMgr::Late_Update(void)
{
	if(TalkOption == 15)
		dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Sans(true);
}

void CUnderMgr::Render(HDC hDC)
{

	GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		100,					// 복사 받을 위치 x좌표
		100,				   // 복사 받을 위치 y좌표
		600,			   // 복사 받을 이미지의 가로 사이즈
		255,			   // 복사 받을 이미지의 세로 사이즈
		hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		0,	  // 비트맵을 출력할 시작 좌표
		0,
		600,							   // 복사할 비트맵의 가로, 세로 사이즈
		255,
		RGB(255, 0, 255));
}

void CUnderMgr::Release(void)
{
	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_TalkUnder(false);
	CUnderMgr::Get_Instance()->Destroy_Instance();
}
