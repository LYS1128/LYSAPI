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
#include "Bullet.h"
#include "Tree.h"
#include "Apple.h"
#include "Keg.h"
#include "Pickle.h"
#include "Statue.h"
#include "Salad.h"
#include "Ban.h"
#include "Puzzle.h"

class CPlayer :public CObj
{
public:
	CPlayer();
	~CPlayer();

public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual int			Late_Update(void);
	virtual void		Render(HDC hDC);
	virtual void		Release(void);

public:
	void Key_Input();
	void OffSet(void);
	void Scene_Change(void);
	void Make_Dirt();

	int Get_Day() { return m_iDay; }
	void Set_Day(int Day) { m_iDay += Day; }
	int Get_PreDay() { return m_iPreDay; }
	void Set_PreDay(int Day) { m_iPreDay = Day; }
	int Get_Money() { return m_iMoney; }
	void Set_Money(int Money) { m_iMoney += Money; }
	bool Get_StoreOpen() { return StoreOpen; }
	void Set_StoreOpen(bool Open) { StoreOpen = Open; }
	bool Get_TalkSeba() { return TalkSeba; }
	void Set_TalkSeba(bool Open) { TalkSeba = Open; }
	bool Get_TalkUnder() { return TalkUnder; }
	void Set_TalkUnder(bool Under) { TalkUnder = Under; }
	int Get_Hand() { return m_iHand; }
	void Set_Ending(bool End) { Ending = End; }
	bool Get_Ending() { return Ending; }

	int Get_Present() { return m_iPresent; }
	void Set_Present(int Present) { m_iPresent += Present; }
	bool Get_Sans() { return Sans; }
	void Set_Sans(bool San) { Sans = San; }
	


private:
	CBmpMgr*				m_pBmpMgr;
	bool					m_bJump;
	float					m_fTime;
	float					m_fOriginY;
	DWORD m_dwTime;

	float m_sin;
	float m_cos;

	int m_iHand;
	int m_iDay;
	int m_iPreDay;

	int m_iMoney;
	int m_iPresent;
	bool StoreOpen;
	bool TalkSeba;
	bool Ending;
	bool Sans;
	bool TalkUnder;
};