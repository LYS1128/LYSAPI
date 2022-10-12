#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"

CObjMgr*	CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj*		pTarget = nullptr;

	float		fDistance = 0.f;

	for (auto& iter : m_ObjList[eID])
	{

		float	fWidth = abs(pObj->Get_Info().fX - iter->Get_Info().fX);
		float	fHeight = abs(pObj->Get_Info().fY - iter->Get_Info().fY);

		float   fDistance2 = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if (fDistance > fDistance2 || !pTarget)
		{
			pTarget = iter;
			fDistance = fDistance2;
		}
	}

	return pTarget;
}

std::list<CObj*>* CObjMgr::Get_ObjList(OBJID eID)
{
	return &m_ObjList[eID];
}

void CObjMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if (END <= eID || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update(void)
{
	if (m_ObjList[MONSTER].size() != 0)
	{
		if (CCollisionMgr::Get_Instance()->Collision_MonDead(m_ObjList[BULLET], m_ObjList[MONSTER]))
		{
			
			CSoundMgr::Get_Instance()->PlaySoundW(L"Goast.wav", CSoundMgr::MONSTER, 0.1f);
			bool Pars = false;

			

			for (auto& iter1 : *(CInvenMgr::Get_Instance()->Get_vecInven()))
			{
				
				if (iter1->Get_ItemID() == CRYSTAL)
				{
					dynamic_cast<CCrystal*>(iter1)->Set_Num(1);
					Pars = true;
					break;
				}
			}
			if (!Pars)
			{
				
				for (auto iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->begin(); iter1 != CInvenMgr::Get_Instance()->Get_vecInven()->end(); ++iter1)
				{
					if ((*iter1)->Get_ItemID() == ITEM_END)
					{
						Safe_Delete(*iter1);
						iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter1);
						iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter1, CAbstractFactory<CCrystal>::Create());
						break;
					}
				}
			}
		}
	}

	if (CSceneMgr::Get_Instance()->Get_Scene() == SC_UNDERTALE)
	{
		bool Solve = true;

		for (auto& iter1 : m_ObjList[OBJ])
		{
			POINT	Pt{ m_ObjList[PLAYER].front()->Get_Info().fX,m_ObjList[PLAYER].front()->Get_Info().fY };

			if (iter1->Get_ItemID() == PUZZLE)
			{
				if (PtInRect(&(iter1->Get_Rect()), Pt) && !(dynamic_cast<CPuzzle*>(iter1)->Get_PreSelect()))
				{
					CSoundMgr::Get_Instance()->PlaySoundW(L"Puzzle.wav", CSoundMgr::EFFECT, 0.3f);

					dynamic_cast<CPuzzle*>(iter1)->Set_PreSelect(true);

					if (dynamic_cast<CPuzzle*>(iter1)->Get_DrawID() == 0)
						dynamic_cast<CPuzzle*>(iter1)->Set_DrawID(1);
					else if (dynamic_cast<CPuzzle*>(iter1)->Get_DrawID() == 1)
						dynamic_cast<CPuzzle*>(iter1)->Set_DrawID(2);
					else
						dynamic_cast<CPuzzle*>(iter1)->Set_DrawID(2);

				}
				else if (!(PtInRect(&(iter1->Get_Rect()), Pt)) && dynamic_cast<CPuzzle*>(iter1)->Get_PreSelect())
					dynamic_cast<CPuzzle*>(iter1)->Set_PreSelect(false);

				if (dynamic_cast<CPuzzle*>(iter1)->Get_DrawID() != 1)
					Solve = false;
			}
		}

		if (Solve && !Puzzleinit)
		{
			for (auto& iter : *(CTileMgr::Get_Instance()->Get_TileList()))
			{
				for (auto& iter1 : m_ObjList[OBJ])
				{
					if (iter1->Get_ItemID() == BAN && (iter->Get_Info().fX == iter1->Get_Info().fX) && (iter->Get_Info().fY == iter1->Get_Info().fY))
					{
						dynamic_cast<CBan*>(iter1)->Set_PreSelect(false);
						dynamic_cast<CTile*>(iter)->Set_DrawID(0);
						dynamic_cast<CTile*>(iter)->Set_Option(0);
					}
				}
			}
			Puzzleinit = true;
		}
		else if (!Solve && Puzzleinit)
		{
			for (auto& iter : *(CTileMgr::Get_Instance()->Get_TileList()))
			{
				for (auto& iter1 : m_ObjList[OBJ])
				{
					if (iter1->Get_ItemID() == BAN && (iter->Get_Info().fX == iter1->Get_Info().fX) && (iter->Get_Info().fY == iter1->Get_Info().fY))
					{
						dynamic_cast<CBan*>(iter1)->Set_PreSelect(true);
						dynamic_cast<CTile*>(iter)->Set_DrawID(1);
						dynamic_cast<CTile*>(iter)->Set_Option(1);
					}
				}
			}
			Puzzleinit = false;
		}
	}

	for (auto& iter : *(CTileMgr::Get_Instance()->Get_TileList()))
	{
		iter->Update();

		if (dynamic_cast<CTile*>(iter)->Get_Option() == 1)
		{
			CCollisionMgr::Get_Instance()->Collision_RectEx(m_ObjList[PLAYER].front(), iter);
			if (m_ObjList[MONSTER].size() != 0)
				CCollisionMgr::Get_Instance()->Collision_RectEx(m_ObjList[MONSTER], iter);
			CCollisionMgr::Get_Instance()->Collision_Dead(m_ObjList[BULLET], iter);
		}

		if (dynamic_cast<CTile*>(iter)->Get_Option() == 16 && dynamic_cast<CTile*>(iter)->Get_Select() && CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_RUNNING);
			break;
		}

		if (dynamic_cast<CTile*>(iter)->Get_Option() == 2 && dynamic_cast<CTile*>(iter)->Get_Select() && CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_FARM);
			break;
		}

		if (dynamic_cast<CTile*>(iter)->Get_Option() == 3 && dynamic_cast<CTile*>(iter)->Get_Select() && CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"Door.wav", CSoundMgr::EFFECT, 0.1f);
			CSceneMgr::Get_Instance()->Scene_Change(SC_HOUSE);
			break;
		}

		if (dynamic_cast<CTile*>(iter)->Get_Option() == 4 && dynamic_cast<CTile*>(iter)->Get_Select() && CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_NIGHT);
			break;
		}

		if (dynamic_cast<CTile*>(iter)->Get_Option() == 5 && dynamic_cast<CTile*>(iter)->Get_Select() && CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"Door.wav", CSoundMgr::EFFECT, 0.1f);
			CSceneMgr::Get_Instance()->Scene_Change(SC_STORE);
			break;
		}
		if (dynamic_cast<CTile*>(iter)->Get_Option() == 6 && dynamic_cast<CTile*>(iter)->Get_Select() && CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_StoreOpen(true);
			CStoreMgr::Get_Instance()->Initialize();
			break;
		}

		if (dynamic_cast<CTile*>(iter)->Get_Option() == 7 && dynamic_cast<CTile*>(iter)->Get_Select() && CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_TalkSeba(true);
			CSebaMgr::Get_Instance()->Initialize();
			break;
		}
		if (dynamic_cast<CTile*>(iter)->Get_Option() == 8 && dynamic_cast<CTile*>(iter)->Get_Select() && CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_CAVE);
			break;
		}

		if (dynamic_cast<CTile*>(iter)->Get_Option() == 9 && dynamic_cast<CTile*>(iter)->Get_Select() && CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_UNDERTALE);
			break;
		}

		if (dynamic_cast<CTile*>(iter)->Get_Option() == 10 && dynamic_cast<CTile*>(iter)->Get_Select() && CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{

			for (auto& iter1 : m_ObjList[OBJ])
			{
				if (iter1->Get_ItemID() == PUZZLE)
					dynamic_cast<CPuzzle*>(iter1)->Set_DrawID(0);
			}
			
		}
		if ((dynamic_cast<CTile*>(iter)->Get_Option() >= 11 && dynamic_cast<CTile*>(iter)->Get_Option() <= 15) && dynamic_cast<CTile*>(iter)->Get_Select() && CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_TalkUnder(true);
			CUnderMgr::Get_Instance()->Initialize();
			CUnderMgr::Get_Instance()->Set_TalkOption(dynamic_cast<CTile*>(iter)->Get_Option());
			break;
		}
		

		if (dynamic_cast<CTile*>(iter)->Get_Option() == 0 && dynamic_cast<CTile*>(iter)->Get_Select() && CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			for (auto& Buff = (CObjMgr::Get_Instance()->Get_ObjList(SEED))->begin(); Buff != (CObjMgr::Get_Instance()->Get_ObjList(SEED))->end();) //워터가 있다면 중복인지 아닌지 보고 생성
			{
				if ((iter->Get_Info().fX == (*Buff)->Get_Info().fX) && (iter->Get_Info().fY == (*Buff)->Get_Info().fY) && dynamic_cast<CParsnip*>(*Buff)->Get_DrawID() == 3)
				{
					Safe_Delete(*Buff);
					Buff = CObjMgr::Get_Instance()->Get_ObjList(SEED)->erase(Buff);

					CSoundMgr::Get_Instance()->PlaySoundW(L"Pickle.wav", CSoundMgr::EFFECT, 0.1f);

					bool Pars = false;

					for (auto& iter1 : *(CInvenMgr::Get_Instance()->Get_vecInven()))
					{
						if (iter1->Get_ItemID() == PARSNIP)
						{
							dynamic_cast<CParsnip*>(iter1)->Set_Num(1);
							Pars = true;
							break;
						}
					}
					if (!Pars)
					{
						for (auto iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->begin(); iter1 != CInvenMgr::Get_Instance()->Get_vecInven()->end(); ++iter1)
						{
							if ((*iter1)->Get_ItemID() == ITEM_END)
							{
								Safe_Delete(*iter1);
								iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter1);
								iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter1, CAbstractFactory<CParsnip>::Create());
								break;
							}
						}
					}
				}
				else
					++Buff;
			}
		}

		if (dynamic_cast<CTile*>(iter)->Get_Option() == 1 && dynamic_cast<CTile*>(iter)->Get_Select() && CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			for (auto& Buff = (CObjMgr::Get_Instance()->Get_ObjList(OBJ))->begin(); Buff != (CObjMgr::Get_Instance()->Get_ObjList(OBJ))->end(); ++Buff) //워터가 있다면 중복인지 아닌지 보고 생성
			{
				if (((*Buff)->Get_ItemID() == KEG) && (iter->Get_Info().fX == (*Buff)->Get_Info().fX) && (iter->Get_Info().fY == (*Buff)->Get_Info().fY) && dynamic_cast<CKeg*>(*Buff)->Get_Pickle())
				{
					CSoundMgr::Get_Instance()->PlaySoundW(L"Pickle.wav", CSoundMgr::EFFECT, 0.1f);
					bool Pickle = false;
					dynamic_cast<CKeg*>(*Buff)->Set_Pickle(false);
					dynamic_cast<CKeg*>(*Buff)->Set_Parsnip(false);

					for (auto& iter1 : *(CInvenMgr::Get_Instance()->Get_vecInven()))
					{
						if (iter1->Get_ItemID() == PICKLE)
						{
							dynamic_cast<CPickle*>(iter1)->Set_Num(1);
							Pickle = true;
							break;
						}
					}
					if (!Pickle)
					{
						for (auto iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->begin(); iter1 != CInvenMgr::Get_Instance()->Get_vecInven()->end(); ++iter1)
						{
							if ((*iter1)->Get_ItemID() == ITEM_END)
							{
								Safe_Delete(*iter1);
								iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter1);
								iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter1, CAbstractFactory<CPickle>::Create());
								break;
							}
						}
					}
				}
			}

		}
	}

	int iEvent = 0;

	for (int i = 0; i < END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iEvent = iter->Update();
	}

	Set_DirtID(DIRT);
	Set_DirtID(WATER);

	return 0;
}

int CObjMgr::Late_Update(void)
{
	for (int i = 0; i < END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;
		}
	}

	return 0;
}

void CObjMgr::Render(HDC hDC)
{
	//for (int i = 0; i < END; ++i)
	//{
	//	
	//}

	for (int i = 0; i < END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;

			m_RenderList[i].push_back(iter);

		}

		m_RenderList[i].sort(CompareY<CObj*>);

		for (auto& iter : m_RenderList[i])
			iter->Render(hDC);

		m_RenderList[i].clear();		// 정렬은 실시간으로 계속 바뀜
	}
}

void CObjMgr::Release(void)
{
	for (int i = 0; i < END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}

///////////////////////////////////////////////
void CObjMgr::Set_DirtID(OBJID _eID)
{

	for (auto& iter : m_ObjList[_eID])
	{
		int Check = 0; //업 1 다운 2 왼 4 오른 8

		for (auto& Buff : m_ObjList[_eID])
		{
			if (((iter->Get_Info().fY - 32) == Buff->Get_Info().fY) && (iter->Get_Info().fX == Buff->Get_Info().fX)) //위에 있다....
				Check |= 1;
			if (((iter->Get_Info().fY + 32) == Buff->Get_Info().fY) && (iter->Get_Info().fX == Buff->Get_Info().fX)) //아래에 있다....
				Check |= 2;
			if (((iter->Get_Info().fX - 32) == Buff->Get_Info().fX) && (iter->Get_Info().fY == Buff->Get_Info().fY)) //왼쪽에 있다....
				Check |= 4;
			if (((iter->Get_Info().fX + 32) == Buff->Get_Info().fX) && (iter->Get_Info().fY == Buff->Get_Info().fY)) //오른쪽에 있다....
				Check |= 8;
		}

		if (Check == 0)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(SOLO);
		else if (Check == 1)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(UP);
		else if (Check == 2)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(DOWN);
		else if (Check == 3)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(UPDOWN);
		else if (Check == 4)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(LEFT);
		else if (Check == 5)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(UPLEFT);
		else if (Check == 6)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(DOWNLEFT);
		else if (Check == 7)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(UDL);
		else if (Check == 8)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(RIGHT);
		else if (Check == 9)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(UPRIGHT);
		else if (Check == 10)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(DOWNRIGHT);
		else if (Check == 11)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(UDR);
		else if (Check == 12)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(LEFTRIGHT);
		else if (Check == 13)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(ULR);
		else if (Check == 14)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(DLR);
		else if (Check == 15)
			dynamic_cast<CDirt*>(iter)->Set_DrawID(UDLR);
	}
}
