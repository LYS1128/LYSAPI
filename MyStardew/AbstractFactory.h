#pragma once

#include "Obj.h"

// 추상 팩토리 패턴

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	static	CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static	CObj*		Create(float _fX, float _fY)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}

	static	CObj*		Create(float _fX, float _fY, float _fAngle, DIR eDir = DIR_END)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		if (DIR_END != eDir)
			pObj->Set_Dir(eDir);

		return pObj;
	}
};

//template<typename T>
//inline CAbstractFactory<T>::CAbstractFactory()
//{
//}
//
//template<typename T>
//inline CAbstractFactory<T>::~CAbstractFactory()
//{
//}
