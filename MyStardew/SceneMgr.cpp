#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr*	CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eScene(SCENEID(SC_MENU)), m_ePreScene(SCENEID(SC_END))
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eScene = eID;

	if (m_ePreScene != m_eScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eScene)
		{

		case SC_MENU:
			m_pScene = new CMyMenu;
			break;
		case SC_HOUSE:
			m_pScene = new CHouse;
			break;
		case SC_FARM:
			m_pScene = new CFarm;
			break;
		case SC_NIGHT:
			m_pScene = new CNight;
			break;
		case SC_STORE:
			m_pScene = new CStore;
			break;
		case SC_CAVE:
			m_pScene = new CCave;
				break;
		case SC_UNDERTALE:
			m_pScene = new CUndertale;
			break;
		case SC_RUNNING:
			m_pScene = new CRunning;
			break;
		case SC_ENDING:
			m_pScene = new CEnding;
			break;
		}
		m_pScene->Initialize();
		m_ePreScene = m_eScene;
	}
}

void CSceneMgr::Update(void)
{
	if (nullptr != m_pScene)
		m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	if (m_pScene)
		m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC _DC)
{
	m_pScene->Render(_DC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);
}
