#pragma once
#include "Obj.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

class CKeg : public CObj
{
public:
	CKeg();
	~CKeg();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Set_Parsnip(bool Parsnip) { m_Parsnip = Parsnip; }
	const bool&			Get_Parsnip() const { return m_Parsnip; }
	void		Set_Pickle(bool Pickle) { m_Pickle = Pickle; }
	const bool&			Get_Pickle() const { return m_Pickle; }

private:
	bool m_Parsnip;
	bool m_Pickle;
};