#pragma once
#include "Scene.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "UIInven.h"

class CEnding :public CScene
{
public:
	CEnding();
	~CEnding();
public:
	virtual void	Initialize(void);
	virtual void	Update(void);
	virtual void	Late_Update(void);
	virtual void	Render(HDC _DC);
	virtual void	Release(void);
};