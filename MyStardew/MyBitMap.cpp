#include "stdafx.h"
#include "MyBitMap.h"


CMyBitMap::CMyBitMap()
{
}


CMyBitMap::~CMyBitMap()
{
	Release();
}

void CMyBitMap::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	m_hBitMap = (HBITMAP)LoadImage(NULL,			// ���α׷� �ν��Ͻ� �ڵ��� ����
		pFilePath,		// ������ ���
		IMAGE_BITMAP,	// � Ÿ��, ��Ʈ��, Ŀ������, ����������
		0,				// ����, ���� ������
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	// LR_LOADFROMFILE : ���Ͽ��� �̹����� �ҷ����ڴٴ� ��
	// LR_CREATEDIBSECTION : �о�� ������ DIB���·� ��ȯ�ϰڴٴ� ��

	/*- LoadImage�� ��Ʈ���� ���� ������ ������ �ִ� ������ �׸��� ���´� �ƴϴ�.
	- ��Ʈ���� �׸��� ���ؼ� m_hMemDC������ �غ������� '���� ���õ� GDI������Ʈ'�� �⺻���� ��Ȳ�̴�.
	- �غ��� DC�� GDI������Ʈ�� �ҷ��� ��Ʈ���� �����ϱ� ���� SelectObject ����Ѵ�.

	- SelectObject�� GDI ������Ʈ�� �����ϱ� �� ������Ʈ�� ��ȯ*/

	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);

}

void CMyBitMap::Release(void)
{
	// LoadImage �о���� ������ �����ϴ� �Լ�

	// ���� dc�� ���õ� GDI ������Ʈ�� ������ ���� ����.
	// �����ϱ� ���� ������ ����ϴ� GDI������Ʈ�� ��ü�� �ϰ� �� ���� ������ �����ϴ� �ڵ��̴�.

	SelectObject(m_hMemDC, m_hOldBmp);

	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}
