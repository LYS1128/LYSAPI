#include "stdafx.h"
#include "Cave.h"


CCave::CCave()
{
}


CCave::~CCave()
{
	Release();
}

void CCave::Initialize(void)
{

	CObj* pObj = nullptr;
	CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front()->Set_Speed(2.f);

	CTileMgr::Get_Instance()->Initialize();

	pObj = CAbstractFactory<CMonster>::Create();
	CObjMgr::Get_Instance()->Add_Object(MONSTER, pObj);

	CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front()->Set_Pos(304, 304);
	CScrollMgr::Get_Instance()->Set_ScrollX(450);
	CScrollMgr::Get_Instance()->Set_ScrollY(112);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BlackGround.bmp", L"BlackGround");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Cave.bmp", L"Cave");

	Load_Tile();

	


}

void CCave::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySoundW(L"06Cave.wav", CSoundMgr::BGM, 0.1f);
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

}

void CCave::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();

}

void CCave::Render(HDC _DC)
{
	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"BlackGround");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Cave");
	BitBlt(_DC, 160 + iScrollX, iScrollY, 320, 318, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(_DC);
	CTileMgr::Get_Instance()->Render(_DC);
}

void CCave::Release(void)
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	Save_Tile();
	CTileMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(BULLET);
}

//////////////////////////////////////
void CCave::Save_Tile(void)
{
	HANDLE	hFile = CreateFile(L"../Data/CaveTile.dat",	// ������ ��� �� �̸� ���	
		GENERIC_WRITE,		// ���� ���� ���, WRITE�� ����, READ�� �б�
		NULL,				// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�� ������ �ɼ�, NULL �������� ����
		NULL,				// ���ȼӼ�, NULL�� ��� �⺻������ ����
		CREATE_ALWAYS,		// ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXITING ������ ���� ��쿡�� ���� �ɼ�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ����� ���� �Ӽ��� �ǹ�), �ƹ��� �Ӽ��� ���� ����� �÷���
		NULL);	// ������ ������ �Ӽ��� ������ ���ø� ������ �ִ� �ּҰ�

	if (INVALID_HANDLE_VALUE == hFile) // ���� ����
	{
		// 1���� : �ڵ�, � ���μ����� �޼����� ��� ������ �����ϱ� ���� �ڵ�
		// 2���� : �޼����� ���� ����ϴ� ���ڿ�
		// 3���� : �˾� â�� �̸� ���ڿ�
		// 4���� : OK ��ư
		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : *(CTileMgr::Get_Instance()->Get_TileList()))
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &(dynamic_cast<CTile*>(iter)->Get_DrawID()), sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &(dynamic_cast<CTile*>(iter)->Get_Option()), sizeof(int), &dwByte, nullptr);
	}

	// ���� �Ҹ�
	CloseHandle(hFile);
}

void CCave::Load_Tile(void)
{
	for_each(CTileMgr::Get_Instance()->Get_TileList()->begin(), CTileMgr::Get_Instance()->Get_TileList()->end(), Safe_Delete<CObj*>);
	CTileMgr::Get_Instance()->Get_TileList()->clear();

	HANDLE	hFile = CreateFile(L"../Data/CaveTile.dat",	// ������ ��� �� �̸� ���	
		GENERIC_READ,		// ���� ���� ���, WRITE�� ����, READ�� �б�
		NULL,				// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�� ������ �ɼ�, NULL �������� ����
		NULL,				// ���ȼӼ�, NULL�� ��� �⺻������ ����
		OPEN_EXISTING,		// ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXITING ������ ���� ��쿡�� ���� �ɼ�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ����� ���� �Ӽ��� �ǹ�), �ƹ��� �Ӽ��� ���� ����� �÷���
		NULL);	// ������ ������ �Ӽ��� ������ ���ø� ������ �ִ� �ּҰ�

	if (INVALID_HANDLE_VALUE == hFile) // ���� ����
	{

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

		CTileMgr::Get_Instance()->Get_TileList()->push_back(CAbstractFactory<CTile>::Create(BuffINFO.fX, BuffINFO.fY));

		dynamic_cast<CTile*>((*CTileMgr::Get_Instance()->Get_TileList())[i])->Set_DrawID(BuffID);
		dynamic_cast<CTile*>((*CTileMgr::Get_Instance()->Get_TileList())[i])->Set_Option(BuffOp);

		dynamic_cast<CTile*>((*CTileMgr::Get_Instance()->Get_TileList())[i])->Update_Rect();

		++i;
	}

	// ���� �Ҹ�
	CloseHandle(hFile);

}



