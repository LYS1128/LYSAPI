#pragma once

#include "Include.h"
#include "ScrollMgr.h"

class CObj abstract
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY);
	void		Set_Dir(DIR eDir);

	void		Set_PosX(float _fX);
	void		Set_PosY(float _fY);
	void RePosX(float _X);
	void RePosY(float _Y);
	void		Set_FrameKey(TCHAR* pFrameKey);

	void			Set_Select(bool _Select) { m_bSelect = _Select; }
	
	void Set_ItemID(int _ItemID) { m_iItemID = _ItemID; }

	void Set_Speed(int speed) { m_fSpeed = speed; }

	const 	int& Get_ItemID() { return m_iItemID; }
	const bool&		Get_Select() { return m_bSelect; }
	const RECT&		Get_Rect(void)  const { return m_tRect; }
	const INFO&		Get_Info(void)	const { return m_tInfo; }
	DIR				Get_Dir() const { return m_eDir; }
	float				Get_Speed() const { return m_fSpeed; }

public:
	virtual void		Initialize(void) = 0;
	virtual int			Update(void) = 0;
	virtual int			Late_Update(void) = 0;
	virtual void		Render(HDC hDC) = 0;
	virtual void		Release(void) = 0;

public:
	void				Update_Rect(void);
	void				Move_Frame(void);

protected:
	RECT		m_tRect;
	INFO		m_tInfo;
	FRAME		m_tFrame;


	float		m_fSpeed;

	DIR			m_eDir;
	bool		m_bSelect;
	TCHAR*		m_pFrameKey;
	STATE		m_eState;
	STATE		m_ePreState;

	int m_iItemID;

};
