#pragma once
#include "Define.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

private:
	HDC			m_DC;
	int				m_iFPS;
	TCHAR			m_szFPS[32];
	DWORD			m_dwTime;
};

