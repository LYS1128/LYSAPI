#pragma once
#include "Obj.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

class CRain : public CObj
{
public:
	CRain();
	~CRain();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	DWORD Get_Time() { return m_dwTime; }

private:
	DWORD m_dwTime;
	int m_fSpeed;
};