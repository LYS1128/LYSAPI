#include "stdafx.h"
#include "StoreMgr.h"


CStoreMgr*	CStoreMgr::m_pInstance = NULL;


CStoreMgr::CStoreMgr()
{
}


CStoreMgr::~CStoreMgr()
{
	Release();
}

void CStoreMgr::Initialize(void)
{
	Exit.left = 393; Exit.top = 235; Exit.right = 456; Exit.bottom = 298;
	Parsnip.left = 269; Parsnip.top = 83; Parsnip.right = 716; Parsnip.bottom = 142;
	Present.left = 269; Present.top = 147; Present.right = 716; Present.bottom = 210;
	Sell.left = 321; Sell.top = 236; Sell.right = 385; Sell.bottom = 298;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/StoreWin.bmp", L"StoreWin");

}

void CStoreMgr::Update(void)
{
	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);


	if (PtInRect(&Exit, Pt)) //종료버튼
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_StoreOpen(false);
		}
	}
	else if (PtInRect(&Parsnip, Pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Money() >= 1)
			{
				CSoundMgr::Get_Instance()->PlaySoundW(L"purchase.wav", CSoundMgr::EFFECT, 0.3f);

				dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(-1);

				bool Parsnip = false;
				for (auto& iter1 : *(CInvenMgr::Get_Instance()->Get_vecInven()))
				{
					if (iter1->Get_ItemID() == PARSNIPSEED)
					{
						dynamic_cast<CParsnipSeed*>(iter1)->Set_Num(1);
						Parsnip = true;
						break;
					}
				}
				if (!Parsnip)
				{
					for (auto iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->begin(); iter1 != CInvenMgr::Get_Instance()->Get_vecInven()->end(); ++iter1)
					{
						if ((*iter1)->Get_ItemID() == ITEM_END)
						{
							Safe_Delete(*iter1);
							iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter1);
							iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter1, CAbstractFactory<CParsnipSeed>::Create());
							break;
						}
					}
				}
			}
		}
	}
	else if (PtInRect(&Present, Pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Money() >= 10)
			{
				CSoundMgr::Get_Instance()->PlaySoundW(L"purchase.wav", CSoundMgr::EFFECT, 0.3f);

				dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(-10);

				bool Present = false;
				for (auto& iter1 : *(CInvenMgr::Get_Instance()->Get_vecInven()))
				{
					if (iter1->Get_ItemID() == PRESENT)
					{
						dynamic_cast<CPresent*>(iter1)->Set_Num(1);
						Present = true;
						break;
					}
				}

				if (!Present)
				{
					for (auto iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->begin(); iter1 != CInvenMgr::Get_Instance()->Get_vecInven()->end(); ++iter1)
					{
						if ((*iter1)->Get_ItemID() == ITEM_END)
						{
							Safe_Delete(*iter1);
							iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter1);
							iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter1, CAbstractFactory<CPresent>::Create());
							break;
						}
					}
				}
			}
		}
	}

	else if (PtInRect(&Sell, Pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Hand() == PARSNIP)
			{
				CSoundMgr::Get_Instance()->PlaySoundW(L"Sell.wav", CSoundMgr::EFFECT, 0.3f);

				for (auto& iter = (CInvenMgr::Get_Instance()->Get_vecInven())->begin(); iter != (CInvenMgr::Get_Instance()->Get_vecInven())->end(); ++iter) //워터가 있다면 중복인지 아닌지 보고 생성
				{
					if ((*iter)->Get_ItemID() == PARSNIP)
					{
						if (dynamic_cast<CParsnip*>(*iter)->Get_Num() == 1)
						{
							Safe_Delete(*iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter, CAbstractFactory<CEmpty>::Create());
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(5);
							break;
						}
						else
						{
							dynamic_cast<CParsnip*>(*iter)->Set_Num(-1);
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(5);
							break;

						}

					}
					
				}
			}
			else if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Hand() == APPLE)
			{

				CSoundMgr::Get_Instance()->PlaySoundW(L"Sell.wav", CSoundMgr::EFFECT, 0.3f);
				for (auto& iter = (CInvenMgr::Get_Instance()->Get_vecInven())->begin(); iter != (CInvenMgr::Get_Instance()->Get_vecInven())->end(); ++iter) //워터가 있다면 중복인지 아닌지 보고 생성
				{
					if ((*iter)->Get_ItemID() == APPLE)
					{
						if (dynamic_cast<CApple*>(*iter)->Get_Num() == 1)
						{
							Safe_Delete(*iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter, CAbstractFactory<CEmpty>::Create());
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(3);
							break;
						}
						else
						{
							dynamic_cast<CApple*>(*iter)->Set_Num(-1);
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(3);
							break;

						}

					}
				}
			}
			else if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Hand() == CRYSTAL)
			{
				CSoundMgr::Get_Instance()->PlaySoundW(L"Sell.wav", CSoundMgr::EFFECT, 0.3f);
				for (auto& iter = (CInvenMgr::Get_Instance()->Get_vecInven())->begin(); iter != (CInvenMgr::Get_Instance()->Get_vecInven())->end(); ++iter) //워터가 있다면 중복인지 아닌지 보고 생성
				{
					if ((*iter)->Get_ItemID() == CRYSTAL)
					{
						if (dynamic_cast<CCrystal*>(*iter)->Get_Num() == 1)
						{
							Safe_Delete(*iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter, CAbstractFactory<CEmpty>::Create());
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(2);
							break;
						}
						else
						{
							dynamic_cast<CCrystal*>(*iter)->Set_Num(-1);
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(2);
							break;

						}

					}
				}
			}

			else if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Hand() == PICKLE)
			{
				CSoundMgr::Get_Instance()->PlaySoundW(L"Sell.wav", CSoundMgr::EFFECT, 0.3f);
				for (auto& iter = (CInvenMgr::Get_Instance()->Get_vecInven())->begin(); iter != (CInvenMgr::Get_Instance()->Get_vecInven())->end(); ++iter) //워터가 있다면 중복인지 아닌지 보고 생성
				{
					if ((*iter)->Get_ItemID() == PICKLE)
					{
						if (dynamic_cast<CPickle*>(*iter)->Get_Num() == 1)
						{
							Safe_Delete(*iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter, CAbstractFactory<CEmpty>::Create());
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(8);
							break;
						}
						else
						{
							dynamic_cast<CPickle*>(*iter)->Set_Num(-1);
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(8);
							break;

						}

					}
				}
			}

			else if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Hand() == STATUE)
			{
				CSoundMgr::Get_Instance()->PlaySoundW(L"Sell.wav", CSoundMgr::EFFECT, 0.3f);
				for (auto& iter = (CInvenMgr::Get_Instance()->Get_vecInven())->begin(); iter != (CInvenMgr::Get_Instance()->Get_vecInven())->end(); ++iter) //워터가 있다면 중복인지 아닌지 보고 생성
				{
					if ((*iter)->Get_ItemID() == STATUE)
					{
						if (dynamic_cast<CStatue*>(*iter)->Get_Num() == 1)
						{
							Safe_Delete(*iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter, CAbstractFactory<CEmpty>::Create());
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(5);
							break;
						}
						else
						{
							dynamic_cast<CStatue*>(*iter)->Set_Num(-1);
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(5);
							break;

						}

					}
				}
			}

			else if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Hand() == BOX)
			{
				CSoundMgr::Get_Instance()->PlaySoundW(L"Sell.wav", CSoundMgr::EFFECT, 0.3f);
				for (auto& iter = (CInvenMgr::Get_Instance()->Get_vecInven())->begin(); iter != (CInvenMgr::Get_Instance()->Get_vecInven())->end(); ++iter) //워터가 있다면 중복인지 아닌지 보고 생성
				{
					if ((*iter)->Get_ItemID() == BOX)
					{
						if (dynamic_cast<CBox*>(*iter)->Get_Num() == 1)
						{
							Safe_Delete(*iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter, CAbstractFactory<CEmpty>::Create());
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(2);
							break;
						}
						else
						{
							dynamic_cast<CBox*>(*iter)->Set_Num(-1);
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(2);
							break;

						}

					}
				}
			}

			else if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Hand() == SALAD)
			{
				CSoundMgr::Get_Instance()->PlaySoundW(L"Sell.wav", CSoundMgr::EFFECT, 0.3f);
				for (auto& iter = (CInvenMgr::Get_Instance()->Get_vecInven())->begin(); iter != (CInvenMgr::Get_Instance()->Get_vecInven())->end(); ++iter) //워터가 있다면 중복인지 아닌지 보고 생성
				{
					if ((*iter)->Get_ItemID() == SALAD)
					{
						if (dynamic_cast<CSalad*>(*iter)->Get_Num() == 1)
						{
							Safe_Delete(*iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter);
							iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter, CAbstractFactory<CEmpty>::Create());
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(8);
							break;
						}
						else
						{
							dynamic_cast<CSalad*>(*iter)->Set_Num(-1);
							dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_Money(8);
							break;

						}

					}
				}
			}
		}
	}
}

void CStoreMgr::Late_Update(void)
{
	

}

void CStoreMgr::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"StoreWin");

	GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		51,					// 복사 받을 위치 x좌표
		51,				   // 복사 받을 위치 y좌표
		698,			   // 복사 받을 이미지의 가로 사이즈
		256,			   // 복사 받을 이미지의 세로 사이즈
		hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		0,	  // 비트맵을 출력할 시작 좌표
		0,
		698,							   // 복사할 비트맵의 가로, 세로 사이즈
		256,
		RGB(255, 0, 255));

	TCHAR		szBuff[32] = L"";
	swprintf_s(szBuff, L"%d", dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Money());

	SetBkMode(hDC, 1);
	SetTextColor(hDC, RGB(0, 0, 0));
	HFONT hFont, oldFont;
	hFont = CreateFont(20, 35, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("Room No.703"));
	oldFont = (HFONT)SelectObject(hDC, hFont);
	TextOut(hDC, 501, 257, szBuff, lstrlen(szBuff));
}

void CStoreMgr::Release(void)
{
	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_StoreOpen(false);
	CStoreMgr::Get_Instance()->Destroy_Instance();
}

/////