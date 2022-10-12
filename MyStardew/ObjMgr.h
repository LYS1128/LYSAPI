#pragma once

#include "Include.h"
#include "TileMgr.h"
#include "Player.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "InvenMgr.h"
#include "StoreMgr.h"
#include "SebaMgr.h"
#include "UnderMgr.h"

// 메디에이터(중재자) + 싱글톤

class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
//	CObj*			Get_Player() { return m_ObjList[PLAYER].front(); }
	CObj*			Get_Target(OBJID eID, CObj* pObj);
	list<CObj*>*	Get_ObjList(OBJID eID);

public:
	void			Add_Object(OBJID eID, CObj* pObj);

	int				Update(void);
	int				Late_Update(void);
	void			Render(HDC hDC);
	void			Release(void);
	void			Delete_ID(OBJID eID);

	void Set_DirtID(OBJID _eID);

public:
	static CObjMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjMgr;

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

private:
	list<CObj*>				m_ObjList[END];
	list<CObj*>				m_RenderList[END];
	static		CObjMgr*	m_pInstance;

	bool Puzzleinit = false;
	

};

