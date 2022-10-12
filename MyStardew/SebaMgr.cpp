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

	if (PtInRect(&Exit, Pt)) //�����ư
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
				for (auto& iter = (CInvenMgr::Get_Instance()->Get_vecInven())->begin(); iter != (CInvenMgr::Get_Instance()->Get_vecInven())->end();++iter) //���Ͱ� �ִٸ� �ߺ����� �ƴ��� ���� ����
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
	GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
		100,					// ���� ���� ��ġ x��ǥ
		100,				   // ���� ���� ��ġ y��ǥ
		600,			   // ���� ���� �̹����� ���� ������
		255,			   // ���� ���� �̹����� ���� ������
		hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		0,	  // ��Ʈ���� ����� ���� ��ǥ
		0,
		600,							   // ������ ��Ʈ���� ����, ���� ������
		255,
		RGB(255, 0, 255));
}

void CSebaMgr::Release(void)
{
	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_TalkSeba(false);
	CSebaMgr::Get_Instance()->Destroy_Instance();
}
