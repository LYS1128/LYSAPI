#pragma once
#include "Obj.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

class CEmpty : public CObj
{
public:
	CEmpty();
	~CEmpty();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};