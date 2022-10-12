#include "stdafx.h"
#include "Undertale.h"


CUndertale::CUndertale()
{
}


CUndertale::~CUndertale()
{
	Release();
}

void CUndertale::Initialize(void)
{
	CObj* pObj = nullptr;
	CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front()->Set_Speed(2.5f);

	CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front()->Set_Pos(176, 304);
	CScrollMgr::Get_Instance()->Set_ScrollX(450);
	CScrollMgr::Get_Instance()->Set_ScrollY(112);

	CTileMgr::Get_Instance()->Initialize();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BlackGround.bmp", L"BlackGround");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Undertale.bmp", L"Undertale");

	Load_Tile();
	Load_Obj();
}

void CUndertale::Update(void)
{
	if(dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Sans())
		CSoundMgr::Get_Instance()->PlaySoundW(L"Megalovania.wav", CSoundMgr::BGM, 0.1f);
	else
		CSoundMgr::Get_Instance()->PlaySoundW(L"Memory.wav", CSoundMgr::BGM, 0.1f);
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_TalkUnder())
		CUnderMgr::Get_Instance()->Update();
}

void CUndertale::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();

	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_TalkUnder())
		CUnderMgr::Get_Instance()->Late_Update();
}

void CUndertale::Render(HDC _DC)
{
	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"BlackGround");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Undertale");
	BitBlt(_DC, iScrollX, iScrollY, 2018, 357, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(_DC);
	CTileMgr::Get_Instance()->Render(_DC);
	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_TalkUnder())
		CUnderMgr::Get_Instance()->Render(_DC);
}

void CUndertale::Release(void)
{
	Save_Tile();
	Save_Obj();

	CTileMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);

	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_TalkUnder())
	{
		dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_TalkUnder(false);
		CUnderMgr::Get_Instance()->Destroy_Instance();
	}
}

//////////////////////////////////////////////////
void CUndertale::Save_Tile(void)
{
	HANDLE	hFile = CreateFile(L"../Data/UnderTile.dat",	// 파일의 경로 및 이름 명시	
		GENERIC_WRITE,		// 파일 접근 모드, WRITE는 쓰기, READ는 읽기
		NULL,				// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가할 것인지 옵션, NULL 공유하지 않음
		NULL,				// 보안속성, NULL일 경우 기본값으로 설정
		CREATE_ALWAYS,		// 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXITING 파일이 있을 경우에만 여는 옵션
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김과 같은 속성을 의미), 아무런 속성이 없는 경우의 플래그
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일이 있는 주소값

	if (INVALID_HANDLE_VALUE == hFile) // 개방 실패
	{
		// 1인자 : 핸들, 어떤 프로세스에 메세지를 띄울 것인지 구분하기 위한 핸들
		// 2인자 : 메세지에 실제 출력하는 문자열
		// 3인자 : 팝업 창의 이름 문자열
		// 4인자 : OK 버튼
		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : *(CTileMgr::Get_Instance()->Get_TileList()))
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &(dynamic_cast<CTile*>(iter)->Get_DrawID()), sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &(dynamic_cast<CTile*>(iter)->Get_Option()), sizeof(int), &dwByte, nullptr);
	}

	// 파일 소멸
	CloseHandle(hFile);
}

void CUndertale::Load_Tile(void)
{
	for_each(CTileMgr::Get_Instance()->Get_TileList()->begin(), CTileMgr::Get_Instance()->Get_TileList()->end(), Safe_Delete<CObj*>);
	CTileMgr::Get_Instance()->Get_TileList()->clear();

	HANDLE	hFile = CreateFile(L"../Data/UnderTile.dat",	// 파일의 경로 및 이름 명시	
		GENERIC_READ,		// 파일 접근 모드, WRITE는 쓰기, READ는 읽기
		NULL,				// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가할 것인지 옵션, NULL 공유하지 않음
		NULL,				// 보안속성, NULL일 경우 기본값으로 설정
		OPEN_EXISTING,		// 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXITING 파일이 있을 경우에만 여는 옵션
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김과 같은 속성을 의미), 아무런 속성이 없는 경우의 플래그
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일이 있는 주소값

	if (INVALID_HANDLE_VALUE == hFile) // 개방 실패
	{

		// 1인자 : 핸들, 어떤 프로세스에 메세지를 띄울 것인지 구분하기 위한 핸들
		// 2인자 : 메세지에 실제 출력하는 문자열
		// 3인자 : 팝업 창의 이름 문자열
		// 4인자 : OK 버튼
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
		++i;
	}

	// 파일 소멸
	CloseHandle(hFile);

}

void CUndertale::Save_Obj(void)
{
	HANDLE	hFile = CreateFile(L"../Data/UnderObj.dat",	// 파일의 경로 및 이름 명시	
		GENERIC_WRITE,		// 파일 접근 모드, WRITE는 쓰기, READ는 읽기
		NULL,				// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가할 것인지 옵션, NULL 공유하지 않음
		NULL,				// 보안속성, NULL일 경우 기본값으로 설정
		CREATE_ALWAYS,		// 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXITING 파일이 있을 경우에만 여는 옵션
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김과 같은 속성을 의미), 아무런 속성이 없는 경우의 플래그
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일이 있는 주소값

	if (INVALID_HANDLE_VALUE == hFile) // 개방 실패
	{
		// 1인자 : 핸들, 어떤 프로세스에 메세지를 띄울 것인지 구분하기 위한 핸들
		// 2인자 : 메세지에 실제 출력하는 문자열
		// 3인자 : 팝업 창의 이름 문자열
		// 4인자 : OK 버튼
		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : *(CObjMgr::Get_Instance()->Get_ObjList(OBJ)))
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &(iter->Get_ItemID()), sizeof(ITEMID), &dwByte, nullptr);
		
	}
	//for (auto& iter : *(CObjMgr::Get_Instance()->Get_ObjList(WATER)))
	//{
	//	WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	//	WriteFile(hFile, &(dynamic_cast<CDirt*>(iter)->Get_Water()), sizeof(bool), &dwByte, nullptr);
	//}

	// 파일 소멸
	CloseHandle(hFile);
}

void CUndertale::Load_Obj(void)
{
	for_each(CObjMgr::Get_Instance()->Get_ObjList(OBJ)->begin(), CObjMgr::Get_Instance()->Get_ObjList(OBJ)->end(), Safe_Delete<CObj*>);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ)->clear();

	HANDLE	hFile = CreateFile(L"../Data/UnderObj.dat",	// 파일의 경로 및 이름 명시	
		GENERIC_READ,		// 파일 접근 모드, WRITE는 쓰기, READ는 읽기
		NULL,				// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가할 것인지 옵션, NULL 공유하지 않음
		NULL,				// 보안속성, NULL일 경우 기본값으로 설정
		OPEN_EXISTING,		// 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXITING 파일이 있을 경우에만 여는 옵션
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김과 같은 속성을 의미), 아무런 속성이 없는 경우의 플래그
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일이 있는 주소값

	if (INVALID_HANDLE_VALUE == hFile) // 개방 실패
	{

		// 1인자 : 핸들, 어떤 프로세스에 메세지를 띄울 것인지 구분하기 위한 핸들
		// 2인자 : 메세지에 실제 출력하는 문자열
		// 3인자 : 팝업 창의 이름 문자열
		// 4인자 : OK 버튼
		return;
	}

	DWORD		dwByte = 0;

	INFO	BuffINFO;
	ITEMID BuffID;
	int BuffNum;

	while (true)
	{
		ReadFile(hFile, &BuffINFO, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &BuffID, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;
		if (BuffID == PUZZLE)
		{
			CObj* pObj = CAbstractFactory<CPuzzle>::Create(BuffINFO.fX, BuffINFO.fY);
			pObj->Set_FrameKey(L"PuzzleTile");
			CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
			CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
		}
		else if (BuffID == BAN)
		{
			CObj* pObj = CAbstractFactory<CBan>::Create(BuffINFO.fX, BuffINFO.fY);
			pObj->Set_FrameKey(L"Ban");
			CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
			CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
		}

	}

	// 파일 소멸
	CloseHandle(hFile);

}