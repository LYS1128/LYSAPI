#pragma once
#include "Obj.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "InvenMgr.h"
#include "Dirt.h"
#include "Parsnip.h"
#include "Rock.h"
#include "Wood.h"

class CKirby :public CObj
{
public:
	CKirby();
	~CKirby();

public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual int			Late_Update(void);
	virtual void		Render(HDC hDC);
	virtual void		Release(void);

private:
	CBmpMgr*				m_pBmpMgr;
};