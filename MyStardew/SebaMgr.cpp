#include "stdafx.h"
#include "SebaMgr.h"



CSebaMgr*	CSebaMgr::m_pInstance = NULL;



CSebaMgr::CSebaMgr()
{
}


CSebaMgr::~CSebaMgr()
{
	Release();
}

void CSebaMgr::Initialize(void)
{
	Present.left = 553; Present.top = 284; Present.right = 616; Present.bottom = 347;
	Exit.left = 625; Exit.top = 284; Exit.right = 688; Exit.bottom = 347;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/IdleTalk.bmp", L"IdleTalk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/ThankTalk.bmp", L"ThankTalk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/AlmostTalk.bmp", L"AlmostTalk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/EndTalk.bmp", L"EndTalk");

	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"IdleTalk");
	
}

void CSebaMgr::Update(void)
{
	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	if (PtInRect(&Exit, Pt)) //종료버튼
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_TalkSeba(false);
		}
	}
	else if (PtInRect(&Present, Pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Hand() == PRESENT)
			{
				for (auto& iter = (CInvenMgr::Get_Instance()->Get_vecInven())->begin(); iter != (CInvenMgr::Get_Instance()->Get_vecInven())->end();++iter) //워터가 있다면 중복인지 아닌지 보고 생성
				{
					if ((*iter)->Get_ItemID() == PRESENT)
					{
						
						if (dynamic_cast<CPresent*>(*iter)->Get_Num() == 1)
						{
							Safe_Delete(*iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter, CAbstractFactory<CEmpty>::Create());
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Present(1);
							if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Present() < 7)
							{
								CSoundMgr::Get_Instance()->PlaySoundW(L"present.wav", CSoundMgr::EFFECT, 0.1f);
								hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ThankTalk");
							}
							else if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Present() < 10)
							{
								CSoundMgr::Get_Instance()->PlaySoundW(L"present.wav", CSoundMgr::EFFECT, 0.1f);
								hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"AlmostTalk");
							}
							else
							{
								CSoundMgr::Get_Instance()->PlaySoundW(L"newRecord.wav", CSoundMgr::EFFECT, 0.1f);
								hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"EndTalk");
								dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Ending(true);
							}
							break;
						}
						else
						{
							dynamic_cast<CPresent*>(*iter)->Set_Num(-1);
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Present(1);
							if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Present() < 7)
							{
								CSoundMgr::Get_Instance()->PlaySoundW(L"present.wav", CSoundMgr::EFFECT, 0.1f);
								hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ThankTalk");
							}
							else if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Present() < 10)
							{
								CSoundMgr::Get_Instance()->PlaySoundW(L"present.wav", CSoundMgr::EFFECT, 0.1f);
								hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"AlmostTalk");
							}
							else
							{
								CSoundMgr::Get_Instance()->PlaySoundW(L"newRecord.wav", CSoundMgr::EFFECT, 0.1f);
								hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"EndTalk");
								dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Ending(true);
							}
							break;

						}

					}
				}
			}
		}
	}


}

void CSebaMgr::Late_Update(void)
{
}

void CSebaMgr::Render(HDC hDC)
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

void CSebaMgr::Release(void)
{
	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_TalkSeba(false);
	CSebaMgr::Get_Instance()->Destroy_Instance();
}
