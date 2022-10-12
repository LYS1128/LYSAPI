#pragma once
#include "Scene.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "TileMgr.h"
#include "Rain.h"

class CFarm :public CScene
{
public:
	CFarm();
	~CFarm();
public:
	virtual void	Initialize(void);
	virtual void	Update(void);
	virtual void	Late_Update(void);
	virtual void	Render(HDC _DC);
	virtual void	Release(void);


public:
	void Save_Tile(void);
	void Load_Tile(void);
	void Save_Dirt(void);
	void Load_Dirt(void);
	void Save_Water(void);
	void Load_Water();
	void Save_Seed(void);
	void Load_Seed();
	void Save_Obj(void);
	void Load_Obj();

public:
	bool Get_rain() { return rain; }

private:
	bool rain;
	list<CObj*> rainlist;
};
