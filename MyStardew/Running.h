#pragma once
#include "Scene.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Horse.h"
#include "SceneMgr.h"
#include "Kirby.h"
#include "Box.h"

class CRunning :public CScene
{
public:
	CRunning();
	~CRunning();
public:
	virtual void	Initialize(void);
	virtual void	Update(void);
	virtual void	Late_Update(void);
	virtual void	Render(HDC _DC);
	virtual void	Release(void);

public:
	float m_fSpeed;
	list<CObj*> m_KirbyList;
	list<CObj*> m_BoxList;

};