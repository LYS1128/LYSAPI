#pragma once
#include "Obj.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

class CPickle : public CObj
{
public:
	CPickle();
	~CPickle();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Set_Num(int _Num) { m_iNum += _Num; }
	const int&			Get_Num() const { return m_iNum; }


private:
	int m_iNum;
};


