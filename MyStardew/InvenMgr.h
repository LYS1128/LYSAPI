#pragma once
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "Pick.h"
#include "Watering.h"
#include "ParsnipSeed.h"
#include "Parsnip.h"
#include "Pickax.h"
#include "Ax.h"
#include "Present.h"
#include "Gun.h"
#include "Empty.h"
#include "Crystal.h"
#include "AbstractFactory.h"

class CInvenMgr
{
private:
	CInvenMgr();
	~CInvenMgr();

public:
	void Initialize(void);
	void Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

public:
	std::vector<CObj*>* Get_vecInven();
	void		Set_Big(bool Big) { m_InvenBig = Big; }
	const bool&			Get_Big() const { return m_InvenBig; }

public:
	static CInvenMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CInvenMgr;

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
	static		CInvenMgr*	m_pInstance;
	vector<CObj*>			m_vecInven;
	bool m_InvenBig;
	CObj* BuffItem;
	int BuffIndex;

	bool Wood;
	bool Rock;
	bool Apple;
	bool Parsnip;

	int m_Statue;
	int m_Salad;

	RECT StatueRECT;
	RECT SaladRECT;
};

