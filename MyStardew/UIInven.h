#pragma once
#include "Obj.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

class CUIInven :
	public CObj
{
public:
	CUIInven();
	virtual ~CUIInven();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Set_DrawID(int iDrawID) { m_iDrawID = iDrawID; }
	const int&			Get_DrawID() const { return m_iDrawID; }

private:
	int		m_iDrawID;

};
