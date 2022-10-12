#pragma once
#include "Monster.h"

class CObj;


class CCollisionMgr
{
private:
	CCollisionMgr();
	~CCollisionMgr();

private:
	static bool			Check_Rect(CObj* pDest, CObj* pSrc, float* _pX, float* _pY);
	static		CCollisionMgr*	m_pInstance;

public:
	static CCollisionMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CCollisionMgr;

		return m_pInstance;
	}
	static void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void Collision_RectEx(CObj * Src, CObj * Player);
	void Collision_RectEx(list<CObj*>& Src, CObj * Player);

	void Collision_Dead(list<CObj*>& Src, CObj * Player);

	bool Collision_MonDead(list<CObj*>& Src, list<CObj*>& Dest);


};