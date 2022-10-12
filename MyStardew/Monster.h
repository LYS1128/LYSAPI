#pragma once
#include "Obj.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "InvenMgr.h"
#include "Dirt.h"
#include "Parsnip.h"
#include "Rock.h"
#include "Wood.h"

class CMonster :public CObj
{
public:
	CMonster();
	~CMonster();

public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual int			Late_Update(void);
	virtual void		Render(HDC hDC);
	virtual void		Release(void);

public:
	void Scene_Change();
	void		Set_Hp(int _Hp) { m_iHp += _Hp; }
	const int&			Get_Hp() const { return m_iHp; }

private:
	CBmpMgr*				m_pBmpMgr;
	float					m_fTime;
	int m_iDir;
	int m_iHp;
};