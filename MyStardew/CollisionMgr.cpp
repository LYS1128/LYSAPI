#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"

CCollisionMgr*	CCollisionMgr::m_pInstance = NULL;

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSrc, float* _pX, float* _pY)
{
	float		fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);

	// float		fCX = pDest->Get_Info().fCX / 2.f + pSrc->Get_Info().fCX / 2.f;
	// 위의 식을 아래 식으로 변경했을 뿐
	float		fCX = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float		fCY = (pDest->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	if (fCX > fWidth && fCY > fHeight)
	{
		*_pX = fCX - fWidth;
		*_pY = fCY - fHeight;

		return true;
	}
	return false;
}

void CCollisionMgr::Collision_RectEx(CObj* Src, CObj* Player)
{
	RECT	rc{};

	float		fWidth, fHeight;

	if (Check_Rect(Player, Src, &fWidth, &fHeight))
	{
		// 상하 충돌
		if (fWidth > fHeight)
		{
			// 하 충돌
			if (Player->Get_Info().fY < Src->Get_Info().fY)
				Src->Set_PosY(fHeight);
			// 상 충돌
			else
				Src->Set_PosY(-fHeight);
		}
		// 좌우 충돌
		else
		{
			// 우 충돌
			if (Player->Get_Info().fX < Src->Get_Info().fX)
				Src->Set_PosX(fWidth);
			// 좌 충돌
			else
				Src->Set_PosX(-fWidth);
		}
	}

}

void CCollisionMgr::Collision_RectEx(list<CObj*>& Src, CObj* Player)
{
	RECT	rc{};

	float		fWidth, fHeight;
	for (auto& SrcIter : Src)
	{
		if (Check_Rect(Player, SrcIter, &fWidth, &fHeight))
		{
			// 상하 충돌
			if (fWidth > fHeight)
			{
				// 하 충돌
				if (Player->Get_Info().fY < SrcIter->Get_Info().fY)
					SrcIter->Set_PosY(fHeight);
				// 상 충돌
				else
					SrcIter->Set_PosY(-fHeight);
			}
			// 좌우 충돌
			else
			{
				// 우 충돌
				if (Player->Get_Info().fX < SrcIter->Get_Info().fX)
					SrcIter->Set_PosX(fWidth);
				// 좌 충돌
				else
					SrcIter->Set_PosX(-fWidth);
			}
		}
	}
}

void CCollisionMgr::Collision_Dead(list<CObj*>& Src, CObj* Player)
{
	RECT	rc{};

	float		fWidth, fHeight;
	for (auto SrcIter = Src.begin(); SrcIter != Src.end();)
	{
		if (Check_Rect(Player, (*SrcIter), &fWidth, &fHeight))
		{
			Safe_Delete(*SrcIter);
			SrcIter = Src.erase(SrcIter);
		}
		else
			++SrcIter;
	}
}

bool CCollisionMgr::Collision_MonDead(list<CObj*>& Src, list<CObj*>& Dest)
{
	RECT	rc{};

	float		fWidth, fHeight;
		for (auto SrcIter = Src.begin(); SrcIter != Src.end();)
		{
			if (Check_Rect(Dest.front(), (*SrcIter), &fWidth, &fHeight))
			{
				Safe_Delete(*SrcIter);
				SrcIter = Src.erase(SrcIter);
				dynamic_cast<CMonster*>(Dest.front())->Set_Hp(-1);
				if (dynamic_cast<CMonster*>(Dest.front())->Get_Hp() < 0)
				{					
					Safe_Delete(Dest.front());
					Dest.pop_front();
					return true;
				}
			}
			else
				++SrcIter;
		}
		return false;
}
