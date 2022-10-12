#pragma once
#include "Obj.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

class CDirt: public CObj
{
public:
	CDirt();
	~CDirt();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Set_DrawID(int iDrawID) { m_iDrawID = iDrawID; }
	void		Set_Option(int iOption) { m_iOption = iOption; }
	void		Set_Water(bool Select) { m_Water = Select; }
	const int&			Get_Option() const { return m_iOption; }
	const int&			Get_DrawID() const { return m_iDrawID; }
	const bool&			Get_Water() const { return m_Water; }

private:
	int				m_iDrawID;
	int				m_iOption;
	bool			m_Water;
};

