#include "stdafx.h"
#include "Farm.h"


CFarm::CFarm()
{
}


CFarm::~CFarm()
{
	Release();
}

void CFarm::Initialize(void)
{
	CObj* pObj = nullptr;
	CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front()->Set_Speed(3.f);

	if (CSceneMgr::Get_Instance()->Get_PreScene() == SC_STORE)
	{
		CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front()->Set_Pos(912, 560);
		CScrollMgr::Get_Instance()->Set_ScrollX(-450);
		CScrollMgr::Get_Instance()->Set_ScrollY(-112);
	}
	else if (CSceneMgr::Get_Instance()->Get_PreScene() == SC_CAVE)
	{
		CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front()->Set_Pos(1072, 272);
		CScrollMgr::Get_Instance()->Set_ScrollX(-450);
		CScrollMgr::Get_Instance()->Set_ScrollY(-112);
	}
	else if (CSceneMgr::Get_Instance()->Get_PreScene() == SC_UNDERTALE)
	{
		CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front()->Set_Pos(1264, 80);
		CScrollMgr::Get_Instance()->Set_ScrollX(-450);
		CScrollMgr::Get_Instance()->Set_ScrollY(-112);
	}
	else if(CSceneMgr::Get_Instance()->Get_PreScene() == SC_RUNNING)
	{
		CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front()->Set_Pos(432, 528);
		CScrollMgr::Get_Instance()->Set_ScrollX(-1760);
		CScrollMgr::Get_Instance()->Set_ScrollY(-176);
	}
	else
	{
		CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front()->Set_Pos(2032, 496);
		CScrollMgr::Get_Instance()->Set_ScrollX(-1760);
		CScrollMgr::Get_Instance()->Set_ScrollY(-176);
	}

	//CTileMgr::Get_Instance()->Initialize();
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BlackGround.bmp", L"BlackGround");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Farm.bmp", L"Farm");

	Load_Tile();
	Load_Dirt();
	Load_Water();
	Load_Seed();
	Load_Obj();

	int PreDay = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_PreDay();
	int Day = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Get_Day();

	if (PreDay == 0 && Day == 0)
		rain = false;

	if (CSceneMgr::Get_Instance()->Get_PreScene() == SC_HOUSE && PreDay != Day)
	{	
		rain = false;

		for (auto& iter : *(CObjMgr::Get_Instance()->Get_ObjList(SEED)))
		{
			for (auto& Buff2 : *(CObjMgr::Get_Instance()->Get_ObjList(WATER))) //워터가 있다면 중복인지 아닌지 보고 생성
			{
				if ((iter->Get_Info().fX == Buff2->Get_Info().fX) && (iter->Get_Info().fY == Buff2->Get_Info().fY))
				{
					int Buff = dynamic_cast<CParsnip*>(iter)->Get_DrawID();

					if (Buff < 3)
						dynamic_cast<CParsnip*>(iter)->Set_DrawID(Buff + 1);
				}
			}
		}
		CObjMgr::Get_Instance()->Get_ObjList(WATER)->clear();
		dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front())->Set_PreDay(Day);
		for (auto& iter : *(CObjMgr::Get_Instance()->Get_ObjList(OBJ)))
		{
			if(iter->Get_ItemID() == TREE && dynamic_cast<CTree*>(iter)->Get_Cut() == 0)
				dynamic_cast<CTree*>(iter)->Set_Apple(true);
			if (iter->Get_ItemID() == KEG && dynamic_cast<CKeg*>(iter)->Get_Parsnip())
				dynamic_cast<CKeg*>(iter)->Set_Pickle(true);
		}

		if (rand() % 3 == 0)
			rain = true;
	}

	if (rain)
	{
		for (int i = 0; i < 30; ++i)
		{
			CObj* pRain = CAbstractFactory<CRain>::Create();
			pRain->Initialize();
			rainlist.push_back(pRain);
		}

		if (CObjMgr::Get_Instance()->Get_ObjList(DIRT)->size() != 0) //흙타일이 한개 이상일떄
		{
			for (auto& Buff : *(CObjMgr::Get_Instance()->Get_ObjList(DIRT))) //흙타일 전체를 돌며
			{
				if (CObjMgr::Get_Instance()->Get_ObjList(WATER)->size() == 0) //워터가 한개도 없으면 바로 생성
				{
					CObj* pObj = CAbstractFactory<CDirt>::Create(Buff->Get_Info().fX, Buff->Get_Info().fY);
					pObj->Set_FrameKey(L"WaterTile");
					CObjMgr::Get_Instance()->Add_Object(WATER, pObj);
					CObjMgr::Get_Instance()->Get_ObjList(WATER)->back()->Initialize();
					dynamic_cast<CDirt*>(CObjMgr::Get_Instance()->Get_ObjList(WATER)->back())->Set_Water(true);
				}
				else
				{
					bool Water = true;
					for (auto& Buff2 : *(CObjMgr::Get_Instance()->Get_ObjList(WATER))) //워터가 있다면 중복인지 아닌지 보고 생성
					{
						if ((Buff->Get_Info().fX == Buff2->Get_Info().fX) && (Buff->Get_Info().fY == Buff2->Get_Info().fY))
						{
							Water = false;
							break;
						}
					}

					if (Water)
					{
						CObj* pObj = CAbstractFactory<CDirt>::Create(Buff->Get_Info().fX, Buff->Get_Info().fY);
						pObj->Set_FrameKey(L"WaterTile");
						CObjMgr::Get_Instance()->Add_Object(WATER, pObj);
						CObjMgr::Get_Instance()->Get_ObjList(WATER)->back()->Initialize();
						dynamic_cast<CDirt*>(CObjMgr::Get_Instance()->Get_ObjList(WATER)->back())->Set_Water(true);
					}
				}
			}
		}
	}

}

void CFarm::Update(void)
{
	if (rain)
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"rainfarm.wav", CSoundMgr::BGM, 0.1f);
		CSoundMgr::Get_Instance()->PlaySoundW(L"rain.wav", CSoundMgr::UI, 0.1f);
		
		for (auto& iter: rainlist)
		{
			iter->Update();
		}
	}
	else
		CSoundMgr::Get_Instance()->PlaySoundW(L"02Farm.wav", CSoundMgr::BGM, 0.1f);

	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();	

}

void CFarm::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();	

	for (auto& iter = rainlist.begin(); iter != rainlist.end();)
	{
		(*iter)->Late_Update();

		if (GetTickCount() - dynamic_cast<CRain*>(*iter)->Get_Time() > (rand()%5000))
		{
			Safe_Delete(*iter);
			iter = rainlist.erase(iter);

			CObj* pRain = CAbstractFactory<CRain>::Create();
			pRain->Initialize();
			rainlist.push_back(pRain);
		}
		else
			++iter;
	}
}

void CFarm::Render(HDC _DC)
{
	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"BlackGround");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Farm");
	BitBlt(_DC, iScrollX, iScrollY, 2528, 1472, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(_DC);
	CTileMgr::Get_Instance()->Render(_DC);

	if (rain)
	{
		for (auto& iter : rainlist)
		{
			iter->Render(_DC);
		}

		BLENDFUNCTION bf;
		bf.AlphaFormat = 0;
		bf.BlendFlags = 0;
		bf.BlendOp = AC_SRC_OVER;
		bf.SourceConstantAlpha = 120;

		AlphaBlend(_DC, 0,0, WINCX, WINCY, hBackDC, 0, 0, WINCX, WINCY, bf);
	}
}

void CFarm::Release(void)
{
	Save_Tile();
	Save_Dirt();
	Save_Water();
	Save_Seed();
	Save_Obj();

	CTileMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(DIRT);
	CObjMgr::Get_Instance()->Delete_ID(WATER);
	CObjMgr::Get_Instance()->Delete_ID(SEED);
	CObjMgr::Get_Instance()->Delete_ID(OBJ);
	CObjMgr::Get_Instance()->Delete_ID(BULLET);
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);

	for_each(rainlist.begin(), rainlist.end(), Safe_Delete<CObj*>);
	rainlist.clear();

}

//////////////////////////////////////////////////
void CFarm::Save_Tile(void)
{
	HANDLE	hFile = CreateFile(L"../Data/FarmTile.dat",	// 파일의 경로 및 이름 명시	
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

void CFarm::Load_Tile(void)
{
	for_each(CTileMgr::Get_Instance()->Get_TileList()->begin(), CTileMgr::Get_Instance()->Get_TileList()->end(), Safe_Delete<CObj*>);
	CTileMgr::Get_Instance()->Get_TileList()->clear();
	

	HANDLE	hFile = CreateFile(L"../Data/FarmTile.dat",	// 파일의 경로 및 이름 명시	
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

void CFarm::Save_Dirt(void)
{
	HANDLE	hFile = CreateFile(L"../Data/FarmDirt.dat",	// 파일의 경로 및 이름 명시	
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

	for (auto& iter : *(CObjMgr::Get_Instance()->Get_ObjList(DIRT)))
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	}
	//for (auto& iter : *(CObjMgr::Get_Instance()->Get_ObjList(WATER)))
	//{
	//	WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	//	WriteFile(hFile, &(dynamic_cast<CDirt*>(iter)->Get_Water()), sizeof(bool), &dwByte, nullptr);
	//}

	// 파일 소멸
	CloseHandle(hFile);
}

void CFarm::Load_Dirt(void)
{
	for_each(CObjMgr::Get_Instance()->Get_ObjList(DIRT)->begin(), CObjMgr::Get_Instance()->Get_ObjList(DIRT)->end(), Safe_Delete<CObj*>);
	CObjMgr::Get_Instance()->Get_ObjList(DIRT)->clear();

	HANDLE	hFile = CreateFile(L"../Data/FarmDirt.dat",	// 파일의 경로 및 이름 명시	
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

	while (true)
	{
		ReadFile(hFile, &BuffINFO, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<CDirt>::Create(BuffINFO.fX, BuffINFO.fY);
		pObj->Set_FrameKey(L"DirtTile");
		CObjMgr::Get_Instance()->Add_Object(DIRT, pObj);
		CObjMgr::Get_Instance()->Get_ObjList(DIRT)->back()->Initialize();

	}

	// 파일 소멸
	CloseHandle(hFile);

}

void CFarm::Save_Water(void)
{
	HANDLE	hFile = CreateFile(L"../Data/FarmWater.dat",	// 파일의 경로 및 이름 명시	
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

	for (auto& iter : *(CObjMgr::Get_Instance()->Get_ObjList(WATER)))
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	}
	//for (auto& iter : *(CObjMgr::Get_Instance()->Get_ObjList(WATER)))
	//{
	//	WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	//	WriteFile(hFile, &(dynamic_cast<CDirt*>(iter)->Get_Water()), sizeof(bool), &dwByte, nullptr);
	//}

	// 파일 소멸
	CloseHandle(hFile);
}

void CFarm::Load_Water(void)
{
	for_each(CObjMgr::Get_Instance()->Get_ObjList(WATER)->begin(), CObjMgr::Get_Instance()->Get_ObjList(WATER)->end(), Safe_Delete<CObj*>);
	CObjMgr::Get_Instance()->Get_ObjList(WATER)->clear();

	HANDLE	hFile = CreateFile(L"../Data/FarmWater.dat",	// 파일의 경로 및 이름 명시	
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

	while (true)
	{
		ReadFile(hFile, &BuffINFO, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<CDirt>::Create(BuffINFO.fX, BuffINFO.fY);
		pObj->Set_FrameKey(L"WaterTile");
		CObjMgr::Get_Instance()->Add_Object(WATER, pObj);
		CObjMgr::Get_Instance()->Get_ObjList(WATER)->back()->Initialize();
		dynamic_cast<CDirt*>(CObjMgr::Get_Instance()->Get_ObjList(WATER)->back())->Set_Water(true);
	}

	// 파일 소멸
	CloseHandle(hFile);

}


void CFarm::Save_Seed(void)
{
	HANDLE	hFile = CreateFile(L"../Data/FarmSeed.dat",	// 파일의 경로 및 이름 명시	
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

	for (auto& iter : *(CObjMgr::Get_Instance()->Get_ObjList(SEED)))
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &(dynamic_cast<CParsnip*>(iter)->Get_DrawID()), sizeof(int), &dwByte, nullptr);

	}
	//for (auto& iter : *(CObjMgr::Get_Instance()->Get_ObjList(WATER)))
	//{
	//	WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	//	WriteFile(hFile, &(dynamic_cast<CDirt*>(iter)->Get_Water()), sizeof(bool), &dwByte, nullptr);
	//}

	// 파일 소멸
	CloseHandle(hFile);
}

void CFarm::Load_Seed(void)
{
	for_each(CObjMgr::Get_Instance()->Get_ObjList(SEED)->begin(), CObjMgr::Get_Instance()->Get_ObjList(SEED)->end(), Safe_Delete<CObj*>);
	CObjMgr::Get_Instance()->Get_ObjList(SEED)->clear();

	HANDLE	hFile = CreateFile(L"../Data/FarmSeed.dat",	// 파일의 경로 및 이름 명시	
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
	int BuffID;

	while (true)
	{
		ReadFile(hFile, &BuffINFO, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &BuffID, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<CParsnip>::Create(BuffINFO.fX, BuffINFO.fY);
		pObj->Set_FrameKey(L"CropsGrow");
		CObjMgr::Get_Instance()->Add_Object(SEED, pObj);
		CObjMgr::Get_Instance()->Get_ObjList(SEED)->back()->Initialize();
		dynamic_cast<CParsnip*>(CObjMgr::Get_Instance()->Get_ObjList(SEED)->back())->Set_Seed(true);
		dynamic_cast<CParsnip*>(CObjMgr::Get_Instance()->Get_ObjList(SEED)->back())->Set_DrawID(BuffID);
	}

	// 파일 소멸
	CloseHandle(hFile);

}

void CFarm::Save_Obj(void)
{
	HANDLE	hFile = CreateFile(L"../Data/FarmObj.dat",	// 파일의 경로 및 이름 명시	
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
		if (iter->Get_ItemID() == TREE)
		{
			WriteFile(hFile, &(dynamic_cast<CTree*>(iter)->Get_Num()), sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &(dynamic_cast<CTree*>(iter)->Get_Apple()), sizeof(bool), &dwByte, nullptr);
		}
		if (iter->Get_ItemID() == KEG)
		{
			WriteFile(hFile, &(dynamic_cast<CKeg*>(iter)->Get_Parsnip()), sizeof(bool), &dwByte, nullptr);
			WriteFile(hFile, &(dynamic_cast<CKeg*>(iter)->Get_Pickle()), sizeof(bool), &dwByte, nullptr);
		}
	}
	//for (auto& iter : *(CObjMgr::Get_Instance()->Get_ObjList(WATER)))
	//{
	//	WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	//	WriteFile(hFile, &(dynamic_cast<CDirt*>(iter)->Get_Water()), sizeof(bool), &dwByte, nullptr);
	//}

	// 파일 소멸
	CloseHandle(hFile);
}

void CFarm::Load_Obj(void)
{
	for_each(CObjMgr::Get_Instance()->Get_ObjList(OBJ)->begin(), CObjMgr::Get_Instance()->Get_ObjList(OBJ)->end(), Safe_Delete<CObj*>);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ)->clear();

	HANDLE	hFile = CreateFile(L"../Data/FarmObj.dat",	// 파일의 경로 및 이름 명시	
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
	bool BuffApple;
	bool BuffPickle;

	while (true)
	{
		ReadFile(hFile, &BuffINFO, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &BuffID, sizeof(int), &dwByte, nullptr);
		if (BuffID == TREE)
		{
			ReadFile(hFile, &BuffNum, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &BuffApple, sizeof(bool), &dwByte, nullptr);
		}
		if (BuffID == KEG)
		{
			ReadFile(hFile, &BuffApple, sizeof(bool), &dwByte, nullptr);
			ReadFile(hFile, &BuffPickle, sizeof(bool), &dwByte, nullptr);
		}

		if (0 == dwByte)
			break;
		if (BuffID == ROCK)
		{
			CObj* pObj = CAbstractFactory<CRock>::Create(BuffINFO.fX, BuffINFO.fY);
			pObj->Set_FrameKey(L"Rock");
			CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
			CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
		}
		else if (BuffID == WOOD)
		{
			CObj* pObj = CAbstractFactory<CWood>::Create(BuffINFO.fX, BuffINFO.fY);
			pObj->Set_FrameKey(L"Wood");
			CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
			CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
		}
		else if (BuffID == TREE)
		{
			CObj* pObj = CAbstractFactory<CTree>::Create(BuffINFO.fX, BuffINFO.fY);
			pObj->Set_FrameKey(L"Tree");
			CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
			CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
			dynamic_cast<CTree*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back())->Set_Num(-6 + BuffNum);
			if((-6 + BuffNum) < -2)
				dynamic_cast<CTree*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back())->Set_Cut(1);
			dynamic_cast<CTree*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back())->Set_Apple(BuffApple);
		}
		else if (BuffID == KEG)
		{
			CObj* pObj = CAbstractFactory<CKeg>::Create(BuffINFO.fX, BuffINFO.fY);
			pObj->Set_FrameKey(L"Keg");
			CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
			CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
			dynamic_cast<CKeg*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back())->Set_Parsnip(BuffApple);
			dynamic_cast<CKeg*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back())->Set_Pickle(BuffPickle);
		}
	}

	// 파일 소멸
	CloseHandle(hFile);

}