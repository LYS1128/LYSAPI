#pragma once

#include "Tile.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"

class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void Initialize(void);
	void Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

public:
	vector<CObj*>* Get_TileList() { return &m_vecTile; }
	void Picking_Tile(POINT& pt, const int& iDrawID, const int& iOption);
	void Select_Tile(POINT & pt, const int & _index);
	void Save_Tile(void);

	void Load_Tile(void);

public:
	static CTileMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CTileMgr;

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
	static		CTileMgr*	m_pInstance;
	vector<CObj*>			m_vecTile;
};

