#pragma once
#include "Obj.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

class CParsnip : public CObj
{
public:
	CParsnip();
	~CParsnip();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Set_Num(int _Num) { m_iNum += _Num; }
	const int&			Get_Num() const { return m_iNum; }

	void		Set_DrawID(int iDrawID) { m_iDrawID = iDrawID; }
	const int&			Get_DrawID() const { return m_iDrawID; }

	void		Set_Seed(bool Seed) { m_Seed = Seed; }
	const bool&			Get_Seed() const { return m_Seed; }

private:
	int m_iNum;
	bool m_Seed;
	int				m_iDrawID;
};