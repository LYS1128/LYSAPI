#include "stdafx.h"
#include "InvenMgr.h"


CInvenMgr*	CInvenMgr::m_pInstance = NULL;


CInvenMgr::CInvenMgr()
{
}


CInvenMgr::~CInvenMgr()
{
	Release();
}

void CInvenMgr::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/SelectTile.bmp", L"SelectTile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Making.bmp", L"Making");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Statue.bmp", L"Statue");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Obj/Salad.bmp", L"Salad");

	m_vecInven.push_back(CAbstractFactory<CPick>::Create());
	m_vecInven.push_back(CAbstractFactory<CPickax>::Create());
	m_vecInven.push_back(CAbstractFactory<CAx>::Create());
	m_vecInven.push_back(CAbstractFactory<CWatering>::Create());
	m_vecInven.push_back(CAbstractFactory<CGun>::Create());
	
	m_vecInven.push_back(CAbstractFactory<CParsnipSeed>::Create());
	dynamic_cast<CParsnipSeed*>(m_vecInven.back())->Set_Num(9);

	for (int i = 6; i < 33;++i)
		m_vecInven.push_back(CAbstractFactory<CEmpty>::Create());

	for (int i = 0; i < m_vecInven.size(); ++i)
	{
		m_vecInven[i]->Set_Pos(240.f+(32.f*i), 568.f);
		m_vecInven[i]->Update_Rect();
	}

	m_InvenBig = false;
	BuffItem = nullptr;
	m_Salad = 1;
	m_Statue = 1;
	Wood= false;
	Rock = false;
	Apple =false;
	Parsnip=false;

	StatueRECT = {240,208,272,240};
	SaladRECT = {400,208,432,240};
}

void CInvenMgr::Update(void)
{
	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	if (m_InvenBig == false)
	{
		for (unsigned int i = 0; i < m_vecInven.size() && i < 11 ; ++i)
		{
			m_vecInven[i]->Set_Pos(240.f + (32.f*i), 568.f);
			m_vecInven[i]->Update_Rect();
		}

		for (unsigned int i = 11;  i < m_vecInven.size(); ++i)
		{
			m_vecInven[i]->Set_Pos(850.f, 650.f);
		}
	}
	else
	{
		for (unsigned int i = 0; i < m_vecInven.size(); ++i)
		{
			m_vecInven[i]->Set_Pos(240.f + (32.f*(i%11)), 100.f + (32.f *(i/11)));
			m_vecInven[i]->Update_Rect();
		}
	}

	for (auto& iter : m_vecInven)
	{
		iter->Update();
	}

	if (PtInRect(&StatueRECT, Pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (m_Statue == 0)
			{

				CSoundMgr::Get_Instance()->PlaySoundW(L"Pickle.wav", CSoundMgr::EFFECT, 0.1f);
				bool Statue = false;

				for (auto& iter1 = (CInvenMgr::Get_Instance()->Get_vecInven())->begin(); iter1 != (CInvenMgr::Get_Instance()->Get_vecInven())->end(); ++iter1) //워터가 있다면 중복인지 아닌지 보고 생성
				{

					if ((*iter1)->Get_ItemID() == WOOD)
					{
						if (dynamic_cast<CWood*>(*iter1)->Get_Num() == 1)
						{
							Safe_Delete(*iter1);
							iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->erase(iter1);
							iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->insert(iter1, CAbstractFactory<CEmpty>::Create());
						}
						else
						{
							dynamic_cast<CWood*>(*iter1)->Set_Num(-1);
						}
					}
					if ((*iter1)->Get_ItemID() == ROCK)
					{
						if (dynamic_cast<CRock*>(*iter1)->Get_Num() == 1)
						{
							Safe_Delete(*iter1);
							iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->erase(iter1);
							iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->insert(iter1, CAbstractFactory<CEmpty>::Create());
						}
						else
						{
							dynamic_cast<CRock*>(*iter1)->Set_Num(-1);
						}
					}
				}

				for (auto& iter1 : *(CInvenMgr::Get_Instance()->Get_vecInven()))
				{

					if (iter1->Get_ItemID() == STATUE)
					{
						dynamic_cast<CStatue*>(iter1)->Set_Num(1);
						Statue = true;
						break;
					}
				}
				if (!Statue)
				{
					for (auto iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->begin(); iter1 != CInvenMgr::Get_Instance()->Get_vecInven()->end(); ++iter1)
					{
						if ((*iter1)->Get_ItemID() == ITEM_END)
						{
							Safe_Delete(*iter1);
							iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter1);
							iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter1, CAbstractFactory<CStatue>::Create());
							dynamic_cast<CStatue*>(*iter1)->Set_Seed(0);
							break;
						}
					}
				}
			}
		}
	}

	if (PtInRect(&SaladRECT, Pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (m_Salad == 0)
			{

				CSoundMgr::Get_Instance()->PlaySoundW(L"Pickle.wav", CSoundMgr::EFFECT, 0.1f);
				bool Salad = false;

				for (auto& iter1 = (CInvenMgr::Get_Instance()->Get_vecInven())->begin(); iter1 != (CInvenMgr::Get_Instance()->Get_vecInven())->end(); ++iter1) //워터가 있다면 중복인지 아닌지 보고 생성
				{

					if ((*iter1)->Get_ItemID() == PARSNIP)
					{
						if (dynamic_cast<CParsnip*>(*iter1)->Get_Num() == 1)
						{
							Safe_Delete(*iter1);
							iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->erase(iter1);
							iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->insert(iter1, CAbstractFactory<CEmpty>::Create());
						}
						else
						{
							dynamic_cast<CParsnip*>(*iter1)->Set_Num(-1);
						}
					}
					if ((*iter1)->Get_ItemID() == APPLE)
					{
						if (dynamic_cast<CApple*>(*iter1)->Get_Num() == 1)
						{
							Safe_Delete(*iter1);
							iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->erase(iter1);
							iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->insert(iter1, CAbstractFactory<CEmpty>::Create());
						}
						else
						{
							dynamic_cast<CApple*>(*iter1)->Set_Num(-1);
						}
					}
				}

				for (auto& iter1 : *(CInvenMgr::Get_Instance()->Get_vecInven()))
				{

					if (iter1->Get_ItemID() == SALAD)
					{
						dynamic_cast<CSalad*>(iter1)->Set_Num(1);
						Salad = true;
						break;
					}
				}
				if (!Salad)
				{
					for (auto iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->begin(); iter1 != CInvenMgr::Get_Instance()->Get_vecInven()->end(); ++iter1)
					{
						if ((*iter1)->Get_ItemID() == ITEM_END)
						{
							Safe_Delete(*iter1);
							iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter1);
							iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter1, CAbstractFactory<CSalad>::Create());
							dynamic_cast<CSalad*>(*iter1)->Set_Seed(0);
							break;
						}
					}
				}
			}
		}
	}
}

void CInvenMgr::Late_Update(void)
{
	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	for (auto& iter : m_vecInven)
	{
		iter->Late_Update();

		if (m_InvenBig == false)
			BuffItem = nullptr;
		if (PtInRect(&(iter->Get_Rect()), Pt))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
			{
				for (auto& Buff : m_vecInven)
					Buff->Set_Select(false);

				if (iter != nullptr)
					iter->Set_Select(true);
				return;
			}
			if (m_InvenBig == true)
			{
				if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
				{
					if (BuffItem == nullptr)
					{
						if (iter->Get_ItemID() != ITEM_END)
						{
							BuffItem = iter;
							BuffIndex = int((Pt.x - 224.f) / 32) + 11 * int((Pt.y - 84.f) / 32);
						}
					}
					else
					{
						m_vecInven[BuffIndex] = iter;
						m_vecInven[(int((iter->Get_Info().fX - 224.f) / 32) + 11 * int((iter->Get_Info().fY - 84.f) / 32))] = BuffItem;
						BuffItem = nullptr;
					}
				}
			}

		}
		if (iter->Get_ItemID() == WOOD)
			Wood = true;
		if (iter->Get_ItemID() == ROCK)
			Rock = true;
		if (iter->Get_ItemID() == APPLE)
			Apple = true;
		if (iter->Get_ItemID() == PARSNIP)
			Parsnip = true;

	}
	if (Wood && Rock)
		m_Statue = 0;
	else
		m_Statue = 1;

	if (Apple && Parsnip)
		m_Salad = 0;
	else
		m_Salad = 1;

	Wood = false;
	Rock = false;
	Apple = false;
	Parsnip = false;

}

void CInvenMgr::Render(HDC hDC)
{

		for (auto& iter : m_vecInven)
		{
			iter->Render(hDC);

			if (iter->Get_Select())
			{
				HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SelectTile");

				GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
					int(iter->Get_Rect().left),  				// 복사 받을 위치 x좌표
					int(iter->Get_Rect().top),				   // 복사 받을 위치 y좌표
					(int)(iter->Get_Info().fCX),			   // 복사 받을 이미지의 가로 사이즈
					(int)(iter->Get_Info().fCY),			   // 복사 받을 이미지의 세로 사이즈
					hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
					0,	  // 비트맵을 출력할 시작 좌표
					0,
					32,							   // 복사할 비트맵의 가로, 세로 사이즈
					32,
					RGB(255, 0, 255));			// 제거하고자하는 색상
			}
		}

		if (m_InvenBig)
		{
			HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Making");

			GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
				208,					// 복사 받을 위치 x좌표
				176,				   // 복사 받을 위치 y좌표
				384,			   // 복사 받을 이미지의 가로 사이즈
				96,			   // 복사 받을 이미지의 세로 사이즈
				hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
				0,	  // 비트맵을 출력할 시작 좌표
				0,
				384,							   // 복사할 비트맵의 가로, 세로 사이즈
				96,
				RGB(255, 0, 255));			// 제거하고자하는 색상		// 제거하고자하는 색상

			HDC	hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(L"Salad");

			GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
				400,					// 복사 받을 위치 x좌표
				208,				   // 복사 받을 위치 y좌표
				32,			   // 복사 받을 이미지의 가로 사이즈
				32,			   // 복사 받을 이미지의 세로 사이즈
				hMemDC1,						   // 현재 비트맵 이미지를 가지고 있는 dc
				32 * m_Salad,	  // 비트맵을 출력할 시작 좌표
				0,
				32,							   // 복사할 비트맵의 가로, 세로 사이즈
				32,
				RGB(255, 0, 255));			// 제거하고자하는 색상		// 제거하고자하는 색상
			HDC	hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"Statue");

			GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
				240,					// 복사 받을 위치 x좌표
				208,				   // 복사 받을 위치 y좌표
				32,			   // 복사 받을 이미지의 가로 사이즈
				32,			   // 복사 받을 이미지의 세로 사이즈
				hMemDC2,						   // 현재 비트맵 이미지를 가지고 있는 dc
				32 * m_Statue,	  // 비트맵을 출력할 시작 좌표
				0,
				32,							   // 복사할 비트맵의 가로, 세로 사이즈
				32,
				RGB(255, 0, 255));			// 제거하고자하는 색상		// 제거하고자하는 색상
		}


}

void CInvenMgr::Release(void)
{
	for_each(m_vecInven.begin(), m_vecInven.end(), Safe_Delete<CObj*>);
	m_vecInven.clear();
}

/////
std::vector<CObj*>* CInvenMgr::Get_vecInven()
{
	return &m_vecInven;
}