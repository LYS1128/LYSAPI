#pragma once
#include "Obj.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

class CBan :
	public CObj
{
public:
	CBan();
	virtual ~CBan();

public:
	void		Set_PreSelect(bool pre) { PreSelect = pre; }
	const bool&			Get_PreSelect() const { return PreSelect; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool PreSelect;
	HDC	hMemDC;


};