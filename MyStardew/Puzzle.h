#pragma once
#include "Obj.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

class CPuzzle :
	public CObj
{
public:
	CPuzzle();
	virtual ~CPuzzle();

public:
	void		Set_DrawID(int iDrawID) { m_iDrawID = iDrawID; }
	const int&			Get_DrawID() const { return m_iDrawID; }
	void		Set_PreSelect(bool pre) { PreSelect = pre; }
	const bool&			Get_PreSelect() const { return PreSelect; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int				m_iDrawID;
	bool PreSelect;
	HDC	hMemDC;


};