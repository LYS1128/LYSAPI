#pragma once

#include "Include.h"
#include "Scene.h"
#include "MyMenu.h"
#include "House.h"
#include "Farm.h"
#include "Night.h"
#include "Store.h"
#include "Cave.h"
#include "Undertale.h"
#include "Running.h"
#include "Ending.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	void		Set_Scene(SCENEID eScene) { m_eScene = eScene; }
	SCENEID		Get_Scene() { return m_eScene; }
	CScene*		Get_NowScene() { return m_pScene; }

public:
	void	Scene_Change(SCENEID eID);
	void	Update(void);
	void	Late_Update(void);
	void	Render(HDC _DC);
	void	Release(void);

public:
	static CSceneMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSceneMgr;

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
	SCENEID Get_PreScene() { return m_ePreScene; }

private:
	static		CSceneMgr*				m_pInstance;
	CScene*								m_pScene;
	SCENEID								m_eScene;
	SCENEID								m_ePreScene;

};