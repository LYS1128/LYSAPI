#pragma once
#include "Obj.h"
#include "BmpMgr.h"

class CUIImage	:public CObj
{
public:
	CUIImage();
	~CUIImage();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

