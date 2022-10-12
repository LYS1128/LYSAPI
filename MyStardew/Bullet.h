#pragma once
#include "Obj.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

class CBullet : public CObj {
public:
	CBullet();
	~CBullet();
public:
	virtual void Initialize();
	virtual int Update();
	virtual int Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();
public:
	void Set_Pos(float _fX, float _fY);
	void Set_Tri(float _Sin, float _Cos);
	void Set_Speed(float _Speed);
	void Set_Size(float _Size);
private:
	float m_sin;
	float m_cos;
};


