#include "stdafx.h"
#include "Running.h"


CRunning::CRunning()
{
}


CRunning::~CRunning()
{
	Release();
}

void CRunning::Initialize(void)
{
	CObj* pObj = nullptr;

	pObj = CAbstractFactory<CHorse>::Create();
	CObjMgr::Get_Instance()->Add_Object(HORSE, pObj);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BlackGround.bmp", L"BlackGround");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Running.bmp", L"Running");

	m_fSpeed = 0.f;

}

void CRunning::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySoundW(L"Horse.wav", CSoundMgr::BGM, 0.1f);
	CObjMgr::Get_Instance()->Get_ObjList(HORSE)->front()->Update();

	if (m_fSpeed > -14196)
	{
		m_fSpeed -= 5.f;

		if (GetTickCount() % 1000 == 0)
		{
			CObj* pKirby = new CKirby;
			pKirby->Initialize();
			m_KirbyList.push_back(pKirby);
		}
		if (GetTickCount() % 3000 == 0)
		{
			CObj* pBox = new CBox;
			pBox->Initialize();
			m_BoxList.push_back(pBox);
		}
	}
	else
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"RunningS.wav", CSoundMgr::MONSTER, 0.1f);
		CSceneMgr::Get_Instance()->Scene_Change(SC_FARM);
		return;
	}


	for (auto& iter : m_KirbyList)
	{
		iter->Update();
	}
	for (auto& iter : m_BoxList)
	{
		iter->Update();
	}
}

void CRunning::Late_Update(void)
{
	CObjMgr::Get_Instance()->Get_ObjList(HORSE)->front()->Late_Update();

	for (auto& iter = m_KirbyList.begin();iter != m_KirbyList.end();)
	{
		(*iter)->Late_Update();

		RECT Buff;

		if (IntersectRect(&Buff, &(CObjMgr::Get_Instance()->Get_ObjList(HORSE)->front()->Get_Rect()), &((*iter)->Get_Rect())))
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"crash.wav", CSoundMgr::MONSTER, 0.1f);
			CSceneMgr::Get_Instance()->Scene_Change(SC_FARM);
			return;
		}

		if ((*iter)->Get_Rect().left < -100) 
		{
			iter = m_KirbyList.erase(iter);
		}
		else
			++iter;
	}
	for (auto& iter = m_BoxList.begin(); iter != m_BoxList.end();)
	{
		(*iter)->Late_Update();

		RECT Buff;

		if (IntersectRect(&Buff, &(CObjMgr::Get_Instance()->Get_ObjList(HORSE)->front()->Get_Rect()), &((*iter)->Get_Rect())))
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"Box.wav", CSoundMgr::EFFECT, 0.1f);
			iter = m_BoxList.erase(iter);

			bool Box = false;
			for (auto& iter1 : *(CInvenMgr::Get_Instance()->Get_vecInven()))
			{
				if (iter1->Get_ItemID() == BOX)
				{
					dynamic_cast<CBox*>(iter1)->Set_Num(1);
					Box = true;
					break;
				}
			}
			if (!Box)
			{
				for (auto iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->begin(); iter1 != CInvenMgr::Get_Instance()->Get_vecInven()->end(); ++iter1)
				{
					if ((*iter1)->Get_ItemID() == ITEM_END)
					{
						Safe_Delete(*iter1);
						iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter1);
						iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter1, CAbstractFactory<CBox>::Create());
						dynamic_cast<CBox*>(*iter1)->Set_Seed(false);
						break;
					}
				}
			}

		}
		else if ((*iter)->Get_Rect().left < -100)
		{
			iter = m_BoxList.erase(iter);
		}
		else
			++iter;
	}
}

void CRunning::Render(HDC _DC)
{
	HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"BlackGround");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Running");
	BitBlt(_DC, m_fSpeed, 0, 15000, 600, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Get_ObjList(HORSE)->front()->Render(_DC);

	for (auto& iter : m_KirbyList)
	{
		iter->Render(_DC);
	}
	for (auto& iter : m_BoxList)
	{
		iter->Render(_DC);
	}
}

void CRunning::Release(void)
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CObjMgr::Get_Instance()->Delete_ID(HORSE);
	CObjMgr::Get_Instance()->Delete_ID(OBJ);
	for_each(m_KirbyList.begin(), m_KirbyList.end(), Safe_Delete<CObj*>);
	m_KirbyList.clear();
	for_each(m_BoxList.begin(), m_BoxList.end(), Safe_Delete<CObj*>);
	m_BoxList.clear();
}

