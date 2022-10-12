#pragma once
#include "Obj.h"
#include "BmpMgr.h"

class CPick : public CObj
{
public:
	CPick();
	virtual	~CPick();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};

