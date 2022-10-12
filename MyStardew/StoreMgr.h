#pragma once
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "InvenMgr.h"

class CStoreMgr
{
private:
	CStoreMgr();
	~CStoreMgr();

public:
	void Initialize(void);
	void Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

public:
	static CStoreMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CStoreMgr;

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
	static		CStoreMgr*	m_pInstance;
	RECT Exit;
	RECT Parsnip;
	RECT Present;
	RECT Sell;
};
