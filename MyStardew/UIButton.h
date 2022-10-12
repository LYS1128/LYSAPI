#pragma once
#include "Obj.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

class CUIButton :
	public CObj
{
public:
	CUIButton();
	virtual ~CUIButton();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int		m_iDrawID;

};
