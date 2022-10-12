#include "stdafx.h"
#include "TileMgr.h"

CTileMgr*	CTileMgr::m_pInstance = NULL;

CTileMgr::CTileMgr()
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize(void)
{
	int i = 0;

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float fX = float((TILECX * j) + (TILECX >> 1));
			float fY = float((TILECY * i) + (TILECY >> 1));

			m_vecTile.push_back(CAbstractFactory<CTile>::Create(fX, fY));
			m_vecTile[i]->Update_Rect();
		}
	}

}

void CTileMgr::Update(void)
{
	/*for (auto& iter : m_vecTile)
	{
		iter->Update();
	}*/

	int	iCullX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX() / TILECX);
	int	iCullY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY() / TILECY);

	if ((int)CScrollMgr::Get_Instance()->Get_ScrollX() < (WINCX - TILECX * TILEX))
		iCullX = 52;
	else if ((int)CScrollMgr::Get_Instance()->Get_ScrollX() > 0)
		iCullX = 0;
	if ((int)CScrollMgr::Get_Instance()->Get_ScrollY() < (WINCY - TILECY * TILEY))
		iCullY = 26;
	else if ((int)CScrollMgr::Get_Instance()->Get_ScrollY() > 0)
		iCullY = 0;

	//				3 + 12.
	int	iCullEndX = iCullX + (WINCX / TILECX) + 2; // (+2�� �ϴ� ������ Ÿ�� ������ Ư���� �� 800, 600���� �������� �ʱ� ������ �� ��ĭ �� �����ְ� ����ؼ� �ڿ������� ���̱� ����)
	int	iCullEndY = iCullY + (WINCY / TILECY) + 2;

	if (iCullEndX > 79)
		iCullEndX = 79;
	if (iCullEndY > 46)
		iCullEndY = 46;

	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int		iIndex = i * TILEX + j;

			if (0 > iIndex || m_vecTile.size() < (size_t)iIndex)
				continue;

			m_vecTile[iIndex]->Update();
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
	{
		Save_Tile();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
	{
		Load_Tile();
	}
}

void CTileMgr::Late_Update(void)
{
	int	iCullX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX() / TILECX);
	int	iCullY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY() / TILECY);

	if ((int)CScrollMgr::Get_Instance()->Get_ScrollX() < (WINCX - TILECX * TILEX))
		iCullX = 52;
	else if ((int)CScrollMgr::Get_Instance()->Get_ScrollX() > 0)
		iCullX = 0;
	if ((int)CScrollMgr::Get_Instance()->Get_ScrollY() < (WINCY - TILECY * TILEY))
		iCullY = 26;
	else if ((int)CScrollMgr::Get_Instance()->Get_ScrollY() > 0)
		iCullY = 0;

	//				3 + 12.
	int	iCullEndX = iCullX + (WINCX / TILECX) + 2; // (+2�� �ϴ� ������ Ÿ�� ������ Ư���� �� 800, 600���� �������� �ʱ� ������ �� ��ĭ �� �����ְ� ����ؼ� �ڿ������� ���̱� ����)
	int	iCullEndY = iCullY + (WINCY / TILECY) + 2;

	if (iCullEndX > 79)
		iCullEndX = 79;
	if (iCullEndY > 46)
		iCullEndY = 46;

	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int		iIndex = i * TILEX + j;

			if (0 > iIndex || m_vecTile.size() < (size_t)iIndex)
				continue;

			m_vecTile[iIndex]->Late_Update();
		}
	}

	/*for (auto& iter : m_vecTile)
	{
		iter->Late_Update();
	}*/
}

void CTileMgr::Render(HDC hDC)
{
	//for (auto& iter : m_vecTile)
	//	iter->Render(hDC);

	int	iCullX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX() / TILECX);
	int	iCullY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY() / TILECY);

	if ((int)CScrollMgr::Get_Instance()->Get_ScrollX() < (WINCX - TILECX * TILEX))
		iCullX = 52;
	else if ((int)CScrollMgr::Get_Instance()->Get_ScrollX() > 0)
		iCullX = 0;
	if ((int)CScrollMgr::Get_Instance()->Get_ScrollY() < (WINCY - TILECY * TILEY))
		iCullY = 26;
	else if ((int)CScrollMgr::Get_Instance()->Get_ScrollY() > 0)
		iCullY = 0;

	//				3 + 12.
	int	iCullEndX = iCullX + (WINCX / TILECX) + 2; // (+2�� �ϴ� ������ Ÿ�� ������ Ư���� �� 800, 600���� �������� �ʱ� ������ �� ��ĭ �� �����ְ� ����ؼ� �ڿ������� ���̱� ����)
	int	iCullEndY = iCullY + (WINCY / TILECY) + 2;

	if (iCullEndX > 79)
		iCullEndX = 79;
	if (iCullEndY > 46)
		iCullEndY = 46;

	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int		iIndex = i * TILEX + j;

			if (0 > iIndex || m_vecTile.size() < (size_t)iIndex)
				continue;

			m_vecTile[iIndex]->Render(hDC);
		}
	}
}

void CTileMgr::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
	vector<CObj*>().swap(m_vecTile);
}

///////////////////////////////////////////////////
void CTileMgr::Picking_Tile(POINT& pt, const int& iDrawID, const int& iOption)
{
	int		iX = pt.x / TILECX;
	int		iY = pt.y / TILECY;

	int		iIndex = iY * TILEX + iX;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(iDrawID);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(iOption);

}

void CTileMgr::Select_Tile(POINT& pt, const int& _index)
{
	int Tile[8] = { _index - TILEX - 1,_index - TILEX,_index - TILEX + 1,_index - 1,_index + 1,_index + TILEX - 1,_index + TILEX,_index + TILEX + 1 };

	int	iCullX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX() / TILECX);
	int	iCullY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY() / TILECY);

	if ((int)CScrollMgr::Get_Instance()->Get_ScrollX() < (WINCX - TILECX * TILEX))
		iCullX = 52;
	else if ((int)CScrollMgr::Get_Instance()->Get_ScrollX() > 0)
		iCullX = 0;
	if ((int)CScrollMgr::Get_Instance()->Get_ScrollY() < (WINCY - TILECY * TILEY))
		iCullY = 26;
	else if ((int)CScrollMgr::Get_Instance()->Get_ScrollY() > 0)
		iCullY = 0;

	//				3 + 12.
	int	iCullEndX = iCullX + (WINCX / TILECX) + 2; // (+2�� �ϴ� ������ Ÿ�� ������ Ư���� �� 800, 600���� �������� �ʱ� ������ �� ��ĭ �� �����ְ� ����ؼ� �ڿ������� ���̱� ����)
	int	iCullEndY = iCullY + (WINCY / TILECY) + 2;

	if (iCullEndX > 79)
		iCullEndX = 79;
	if (iCullEndY > 46)
		iCullEndY = 46;

	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int		iIndex = i * TILEX + j;

			for (int k = 0; k < 8; ++k)
			{
				if (0 > Tile[k] || m_vecTile.size() <= (size_t)Tile[k])
					continue;

				if (iIndex == Tile[k] && PtInRect(&(m_vecTile[Tile[k]]->Get_Rect()), pt))
				{
					dynamic_cast<CTile*>(m_vecTile[Tile[k]])->Set_Select(true);
					++iIndex;
				}

			}
			if(iIndex < m_vecTile.size())
				dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Select(false);
		}
	}
}

void CTileMgr::Save_Tile(void)
{
	HANDLE	hFile = CreateFile(L"../Data/FarmTile.dat",	// ������ ��� �� �̸� ���	
		GENERIC_WRITE,		// ���� ���� ���, WRITE�� ����, READ�� �б�
		NULL,				// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�� ������ �ɼ�, NULL �������� ����
		NULL,				// ���ȼӼ�, NULL�� ��� �⺻������ ����
		CREATE_ALWAYS,		// ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXITING ������ ���� ��쿡�� ���� �ɼ�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ����� ���� �Ӽ��� �ǹ�), �ƹ��� �Ӽ��� ���� ����� �÷���
		NULL);	// ������ ������ �Ӽ��� ������ ���ø� ������ �ִ� �ּҰ�

	if (INVALID_HANDLE_VALUE == hFile) // ���� ����
	{
		MessageBox(g_hWnd, _T("SaveFail"), _T("Fail"), MB_OK);
		// 1���� : �ڵ�, � ���μ����� �޼����� ��� ������ �����ϱ� ���� �ڵ�
		// 2���� : �޼����� ���� ����ϴ� ���ڿ�
		// 3���� : �˾� â�� �̸� ���ڿ�
		// 4���� : OK ��ư
		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : m_vecTile)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &(dynamic_cast<CTile*>(iter)->Get_DrawID()), sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &(dynamic_cast<CTile*>(iter)->Get_Option()), sizeof(int), &dwByte, nullptr);
	}

	// ���� �Ҹ�
	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Save �Ϸ�"), _T("Success"), MB_OK);
}

void CTileMgr::Load_Tile(void)
{
	m_vecTile.clear();

	HANDLE	hFile = CreateFile(L"../Data/FarmTile.dat",	// ������ ��� �� �̸� ���	
		GENERIC_READ,		// ���� ���� ���, WRITE�� ����, READ�� �б�
		NULL,				// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�� ������ �ɼ�, NULL �������� ����
		NULL,				// ���ȼӼ�, NULL�� ��� �⺻������ ����
		OPEN_EXISTING,		// ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXITING ������ ���� ��쿡�� ���� �ɼ�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ����� ���� �Ӽ��� �ǹ�), �ƹ��� �Ӽ��� ���� ����� �÷���
		NULL);	// ������ ������ �Ӽ��� ������ ���ø� ������ �ִ� �ּҰ�

	if (INVALID_HANDLE_VALUE == hFile) // ���� ����
	{
		MessageBox(g_hWnd, _T("LoadFail"), _T("Fail"), MB_OK);
		// 1���� : �ڵ�, � ���μ����� �޼����� ��� ������ �����ϱ� ���� �ڵ�
		// 2���� : �޼����� ���� ����ϴ� ���ڿ�
		// 3���� : �˾� â�� �̸� ���ڿ�
		// 4���� : OK ��ư
		return;
	}

	DWORD		dwByte = 0;

	int i = 0;
	INFO	BuffINFO;
	int		BuffID;
	int		BuffOp;

	while (true)
	{
		ReadFile(hFile, &BuffINFO, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &BuffID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &BuffOp, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_vecTile.push_back(CAbstractFactory<CTile>::Create(BuffINFO.fX, BuffINFO.fY));

		dynamic_cast<CTile*>(m_vecTile[i])->Set_DrawID(BuffID);
		dynamic_cast<CTile*>(m_vecTile[i])->Set_Option(BuffOp);


		++i;
	}

	// ���� �Ҹ�
	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Load �Ϸ�"), _T("Success"), MB_OK);
}