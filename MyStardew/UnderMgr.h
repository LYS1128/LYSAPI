#pragma once
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "InvenMgr.h"

class CUnderMgr
{
private:
	CUnderMgr();
	~CUnderMgr();

public:
	void Initialize(void);
	void Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

public:
	static CUnderMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CUnderMgr;

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

	void Set_TalkOption(int option) { TalkOption = option; }

private:
	static		CUnderMgr*	m_pInstance;
	HDC	hMemDC;
	int TalkOption;
	RECT Exit;
};

