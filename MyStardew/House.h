#pragma once
#include "Scene.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "TileMgr.h"
#include "UIInven.h"

class CHouse :public CScene
{
public:
	CHouse();
	~CHouse();
public:
	virtual void	Initialize(void);
	virtual void	Update(void);
	virtual void	Late_Update(void);
	virtual void	Render(HDC _DC);
	virtual void	Release(void);

public:
	void Save_Tile(void);
	void Load_Tile(void);
};
