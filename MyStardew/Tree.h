#pragma once
#include "Obj.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

class CTree : public CObj
{
public:
	CTree();
	~CTree();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Set_Num(int _Num) { m_iNum += _Num; }
	const int&			Get_Num() const { return m_iNum; }
	void		Set_Cut(int Cut) { m_Cut = Cut; }
	const int&			Get_Cut() const { return m_Cut; }
	void		Set_Apple(bool Apple) { m_Apple = Apple; }
	const bool&			Get_Apple() const { return m_Apple; }

private:
	int m_iNum;
	int m_Cut;
	bool m_Apple;
};