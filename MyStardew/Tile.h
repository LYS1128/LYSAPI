#pragma once
#include "Obj.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

class CTile :
	public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	void		Set_DrawID(int iDrawID) { m_iDrawID = iDrawID; }
	void		Set_Option(int iOption) { m_iOption = iOption; }
	void		Set_Select(bool Select) { m_Select = Select; }
	const int&			Get_Option() const { return m_iOption; }
	const int&			Get_DrawID() const { return m_iDrawID; }
	const bool&			Get_Select() const { return m_Select; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int				m_iDrawID;
	int				m_iOption;
	bool			m_Select;
	HDC	hMemDC;


};