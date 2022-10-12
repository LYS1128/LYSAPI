#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr*	CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}


CKeyMgr::~CKeyMgr()
{

}

bool CKeyMgr::Key_Pressing(int iKey)
{
	if (GetAsyncKeyState(iKey) & 0x8000)
		return true;

	return false;
}

bool CKeyMgr::Key_Down(int iKey)
{
	// ������ ������ ����, ���� ������ �ִ� ���

	if (!m_bKeyState[iKey] && (GetAsyncKeyState(iKey) & 0x8000))
	{
		m_bKeyState[iKey] = !m_bKeyState[iKey];
		return true;
	}

	if (m_bKeyState[iKey] && !(GetAsyncKeyState(iKey) & 0x8000))
		m_bKeyState[iKey] = !m_bKeyState[iKey];

	return false;
}

bool CKeyMgr::Key_Up(int iKey)
{
	// ������ ������ �ְ�, ���� ������ �ʾ��� ���
	if (m_bKeyState[iKey] && !(GetAsyncKeyState(iKey) & 0x8000))
	{
		m_bKeyState[iKey] = !m_bKeyState[iKey];
		return true;
	}

	if (!m_bKeyState[iKey] && (GetAsyncKeyState(iKey) & 0x8000))
		m_bKeyState[iKey] = !m_bKeyState[iKey];

	return false;
}

