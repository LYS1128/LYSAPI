#pragma once
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "InvenMgr.h"

class CSebaMgr
{
private:
	CSebaMgr();
	~CSebaMgr();

public:
	void Initialize(void);
	void Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

public:
	static CSebaMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSebaMgr;

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
	static		CSebaMgr*	m_pInstance;
	HDC	hMemDC;

	RECT Exit;
	RECT Present;
};