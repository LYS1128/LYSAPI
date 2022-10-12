#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
	:m_pBmpMgr(CBmpMgr::Get_Instance())
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400;
	m_tInfo.fY = 300;
	m_tInfo.fCX = 32;
	m_tInfo.fCY = 32;

	m_fSpeed = 2.f;

	m_iDay = 0;
	m_iPreDay = 0;
	m_bJump = false;
	m_iHand = ITEM_END;

	m_iMoney = 100;
	StoreOpen = false;
	TalkSeba = false;
	TalkUnder = false;
	m_iPresent = 0;
	Ending = false;
	m_dwTime = GetTickCount();
	Sans = false;

	m_pBmpMgr->Insert_Bmp(L"../Image/Player/PlayerDown.bmp", L"PlayerDown");
	m_pBmpMgr->Insert_Bmp(L"../Image/Player/PlayerLeft.bmp", L"PlayerLeft");
	m_pBmpMgr->Insert_Bmp(L"../Image/Player/PlayerUp.bmp", L"PlayerUp");
	m_pBmpMgr->Insert_Bmp(L"../Image/Player/PlayerRight.bmp", L"PlayerRight");
	m_pBmpMgr->Insert_Bmp(L"../Image/Player/SansDown.bmp", L"SansDown");
	m_pBmpMgr->Insert_Bmp(L"../Image/Player/SansLeft.bmp", L"SansLeft");
	m_pBmpMgr->Insert_Bmp(L"../Image/Player/SansUp.bmp", L"SansUp");
	m_pBmpMgr->Insert_Bmp(L"../Image/Player/SansRight.bmp", L"SansRight");

	m_eState = IDLE;
	m_ePreState = IDLE;

	m_pFrameKey = L"PlayerDown";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_pBmpMgr->Insert_Bmp(L"../Image/Player/Inven.bmp", L"Inven");

	CObj* pObj = CAbstractFactory<CUIInven>::Create(400.f, 568.f);
	pObj->Set_FrameKey(L"Inven");
	pObj->Update_Rect();
	CObjMgr::Get_Instance()->Add_Object(INVEN, pObj);
	CInvenMgr::Get_Instance()->Initialize();

	Update_Rect();

}

int CPlayer::Update(void)
{
	if (CSceneMgr::Get_Instance()->Get_Scene() != SC_RUNNING)
	{

		Key_Input();

		Scene_Change();
		Move_Frame();

		Update_Rect();
		OffSet();



		CInvenMgr::Get_Instance()->Update();
	}

	return OBJ_NOEVENT;
}

int CPlayer::Late_Update(void)
{
	if (CSceneMgr::Get_Instance()->Get_Scene() != SC_RUNNING)
	{
		int		iX = (int)(m_tInfo.fX / TILECX);
		int		iY = (int)(m_tInfo.fY / TILECY);

		int		iIndex = iY * TILEX + iX;

		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Select_Tile(pt, iIndex);

		CInvenMgr::Get_Instance()->Late_Update();

		for (auto& iter : *(CInvenMgr::Get_Instance()->Get_vecInven()))
		{
			if (iter->Get_Select())
				m_iHand = iter->Get_ItemID();
		}
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
			Make_Dirt();
	}
	return 0;
}

void CPlayer::Render(HDC hDC)
{
	if (CSceneMgr::Get_Instance()->Get_Scene() != SC_RUNNING)
	{
		//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		HDC	hMemDC = m_pBmpMgr->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
			int(m_tRect.left),  // ���� ���� ��ġ x��ǥ
			int(m_tRect.top - 32),				   // ���� ���� ��ġ y��ǥ
			32,			   // ���� ���� �̹����� ���� ������
			64,			   // ���� ���� �̹����� ���� ������
			hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
			m_tFrame.iFrameStart * int(m_tInfo.fCX),							   // ��Ʈ���� ����� ���� ��ǥ
			m_tFrame.iFrameScene * int(m_tInfo.fCY),
			32,							   // ������ ��Ʈ���� ����, ���� ������
			64,
			RGB(255, 0, 255));			// �����ϰ����ϴ� ����

		HDC	hMemDC1 = m_pBmpMgr->Find_Image(L"Tools");

		if (m_iHand == PICK)
			GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
				int(m_tRect.left + 2),  // ���� ���� ��ġ x��ǥ
				int(m_tRect.top - 52),				   // ���� ���� ��ġ y��ǥ
				28,			   // ���� ���� �̹����� ���� ������
				28,			   // ���� ���� �̹����� ���� ������
				hMemDC1,						   // ���� ��Ʈ�� �̹����� ������ �ִ� d
				192,							   // ��Ʈ���� ����� ���� ��ǥ
				112,
				32,							   // ������ ��Ʈ���� ����, ���� ������
				32,
				RGB(255, 0, 255));			// �����ϰ����ϴ� ����
		else if (m_iHand == WATERING)
			GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
				int(m_tRect.left + 2),  // ���� ���� ��ġ x��ǥ
				int(m_tRect.top - 52),				   // ���� ���� ��ġ y��ǥ
				28,			   // ��			   // ���� ���� �̹����� ���� ������
				28,			   // ��			   // ���� ���� �̹����� ���� ������
				hMemDC1,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
				128,							   // ��Ʈ���� ����� ���� ��ǥ
				160,
				32,							   // ������ ��Ʈ���� ����, ���� ������
				32,
				RGB(255, 0, 255));			// �����ϰ����ϴ� ����
		else if (m_iHand == PICKAX)
			GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
				int(m_tRect.left + 2),  // ���� ���� ��ġ x��ǥ
				int(m_tRect.top - 52),				   // ���� ���� ��ġ y��ǥ
				28,			   // ��			   // ���� ���� �̹����� ���� ������
				28,			   // ��			   // ���� ���� �̹����� ���� ������
				hMemDC1,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
				192,							   // ��Ʈ���� ����� ���� ��ǥ
				16,
				32,							   // ������ ��Ʈ���� ����, ���� ������
				32,
				RGB(255, 0, 255));			// �����ϰ����ϴ� ����
		else if (m_iHand == AX)
			GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
				int(m_tRect.left + 2),  // ���� ���� ��ġ x��ǥ
				int(m_tRect.top - 52),				   // ���� ���� ��ġ y��ǥ
				28,			   // ��			   // ���� ���� �̹����� ���� ������
				28,			   // ��			   // ���� ���� �̹����� ���� ������
				hMemDC1,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
				192,							   // ��Ʈ���� ����� ���� ��ǥ
				64,
				32,							   // ������ ��Ʈ���� ����, ���� ������
				32,
				RGB(255, 0, 255));			// �����ϰ����ϴ� ����


		CInvenMgr::Get_Instance()->Render(hDC);
	}
}

void CPlayer::Release(void)
{
}



//////////////////////////////////////////////////////////////////////////////

void CPlayer::Key_Input() {
	if (CKeyMgr::Get_Instance()->Key_Pressing('W')) {
		if (CKeyMgr::Get_Instance()->Key_Pressing('A')) {
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			if(Sans)
				m_pFrameKey = L"SansLeft";
			else
				m_pFrameKey = L"PlayerLeft";
			m_eState = WALK;
			m_eDir = DIR_UPL;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('D')) {
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			if (Sans)
				m_pFrameKey = L"SansRight";
			else
				m_pFrameKey = L"PlayerRight";
			m_eState = WALK;
			m_eDir = DIR_UPR;
		}
		else {
			m_tInfo.fY -= m_fSpeed;
			if (Sans)
				m_pFrameKey = L"SansUp";
			else
				m_pFrameKey = L"PlayerUp";
			m_eState = WALK;
			m_eDir = DIR_UP;
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('S')) {
		if (CKeyMgr::Get_Instance()->Key_Pressing('A')) {
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			if (Sans)
				m_pFrameKey = L"SansLeft";
			else
				m_pFrameKey = L"PlayerLeft";
			m_eState = WALK;
			m_eDir = DIR_DOWNL;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('D')) {
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			if (Sans)
				m_pFrameKey = L"SansRight";
			else
				m_pFrameKey = L"PlayerRight";
			m_eState = WALK;
			m_eDir = DIR_DOWNR;
		}
		else {
			m_tInfo.fY += m_fSpeed;
			if (Sans)
				m_pFrameKey = L"SansDown";
			else
				m_pFrameKey = L"PlayerDown";
			m_eState = WALK;
			m_eDir = DIR_DOWN;
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('A')) {
		m_tInfo.fX -= m_fSpeed;
		if (Sans)
			m_pFrameKey = L"SansLeft";
		else
			m_pFrameKey = L"PlayerLeft";
		m_eState = WALK;
		m_eDir = DIR_LEFT;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('D')) {
		m_tInfo.fX += m_fSpeed;
		if (Sans)
			m_pFrameKey = L"SansRight";
		else
			m_pFrameKey = L"PlayerRight";
		m_eState = WALK;
		m_eDir = DIR_RIGHT;
	}

	else if (CKeyMgr::Get_Instance()->Key_Down('I')) {
		CUIInven* inven = dynamic_cast<CUIInven*>(CObjMgr::Get_Instance()->Get_ObjList(INVEN)->front());
		if (inven->Get_DrawID() == 1)
		{
			inven->Set_Pos(400.f, 568.f);
			inven->Set_DrawID(0);
			CInvenMgr::Get_Instance()->Set_Big(false);
		}
		else
		{
			inven->Set_Pos(400.f, 100.f);
			inven->Set_DrawID(1);
			CInvenMgr::Get_Instance()->Set_Big(true);
		}
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing('X')) //�浹Ÿ��
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 1);
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing('1')) //������ŻŸ��
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 2, 16);
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing('2')) //����ŻŸ��
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 2, 3);
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing('3')) //���ڱ� Ÿ��
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 2, 5);
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing('4')) //���ڱ� Ÿ��
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 2, 8);
	}

	/////////////////////////////////
	else if (CKeyMgr::Get_Instance()->Key_Pressing('5')) //���� Ÿ��
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 2, 9);
	}

	//else if (CKeyMgr::Get_Instance()->Key_Pressing('5')) //���� Ÿ��
	//{
	//	POINT	pt;
	//	GetCursorPos(&pt);
	//	ScreenToClient(g_hWnd, &pt);

	//	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//	CTileMgr::Get_Instance()->Picking_Tile(pt, 2, 12);
	//}

	//else if (CKeyMgr::Get_Instance()->Key_Pressing('6')) //���� Ÿ��
	//{
	//	POINT	pt;
	//	GetCursorPos(&pt);
	//	ScreenToClient(g_hWnd, &pt);

	//	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//	CTileMgr::Get_Instance()->Picking_Tile(pt, 2, 13);
	//}

	//else if (CKeyMgr::Get_Instance()->Key_Pressing('7')) //���� Ÿ��
	//{
	//	POINT	pt;
	//	GetCursorPos(&pt);
	//	ScreenToClient(g_hWnd, &pt);

	//	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//	CTileMgr::Get_Instance()->Picking_Tile(pt, 2, 14);
	//}

	//else if (CKeyMgr::Get_Instance()->Key_Pressing('8')) //���� Ÿ��
	//{
	//	POINT	pt;
	//	GetCursorPos(&pt);
	//	ScreenToClient(g_hWnd, &pt);

	//	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//	CTileMgr::Get_Instance()->Picking_Tile(pt, 2, 15);
	//}

	//else if (CKeyMgr::Get_Instance()->Key_Pressing('4')) //���� Ÿ��
	//{
	//	POINT	pt;
	//	GetCursorPos(&pt);
	//	ScreenToClient(g_hWnd, &pt);

	//	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//	CTileMgr::Get_Instance()->Picking_Tile(pt, 2, 5);
	//}

	//else if (CKeyMgr::Get_Instance()->Key_Pressing('5')) //���� Ÿ��
	//{
	//	POINT	pt;
	//	GetCursorPos(&pt);
	//	ScreenToClient(g_hWnd, &pt);

	//	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//	CTileMgr::Get_Instance()->Picking_Tile(pt, 2, 6);
	//}

	//else if (CKeyMgr::Get_Instance()->Key_Pressing('6')) //���� Ÿ��
	//{
	//	POINT	pt;
	//	GetCursorPos(&pt);
	//	ScreenToClient(g_hWnd, &pt);

	//	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//	CTileMgr::Get_Instance()->Picking_Tile(pt, 2, 7);
	//}

	//else if (CKeyMgr::Get_Instance()->Key_Pressing('7')) //���� Ÿ��
	//{
	//	POINT	pt;
	//	GetCursorPos(&pt);
	//	ScreenToClient(g_hWnd, &pt);

	//	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//	CTileMgr::Get_Instance()->Picking_Tile(pt, 2, 8);
	//}

	//else if (CKeyMgr::Get_Instance()->Key_Pressing('8')) //���� Ÿ��
	//{
	//	POINT	pt;
	//	GetCursorPos(&pt);
	//	ScreenToClient(g_hWnd, &pt);

	//	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//	CTileMgr::Get_Instance()->Picking_Tile(pt, 2, 9);
	//}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('9')) //���� �ʱ�ȭ ��ư
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 2, 10);
	}


	else if (CKeyMgr::Get_Instance()->Key_Pressing('0')) //Ÿ�Ͼ��ֱ�
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 0, 0);
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing('R')) //��
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		int		iX = pt.x / TILECX;
		int		iY = pt.y / TILECY;

		int		iIndex = iY * TILEX + iX;

		if (0 > iIndex || CTileMgr::Get_Instance()->Get_TileList()->size() <= (size_t)iIndex)
			return;

			if(dynamic_cast<CTile*>((*CTileMgr::Get_Instance()->Get_TileList())[iIndex])->Get_Select())
				{
					if (CObjMgr::Get_Instance()->Get_ObjList(OBJ)->size() == 0)
					{
						CObj* pObj = CAbstractFactory<CRock>::Create((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX, (*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY);
						pObj->Set_FrameKey(L"Rock");
						CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
						CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
						CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 1);
					}
					else
					{
						for (auto& Buff : *(CObjMgr::Get_Instance()->Get_ObjList(OBJ)))
						{
							if (((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX == Buff->Get_Info().fX) && ((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY == Buff->Get_Info().fY))
								return;
						}
						CObj* pObj = CAbstractFactory<CRock>::Create((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX, (*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY);
						pObj->Set_FrameKey(L"Rock");
						CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
						CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
						CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 1);
					}
			}


	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing('T')) //����
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		int		iX = pt.x / TILECX;
		int		iY = pt.y / TILECY;

		int		iIndex = iY * TILEX + iX;

		if (0 > iIndex || CTileMgr::Get_Instance()->Get_TileList()->size() <= (size_t)iIndex)
			return;

		if (dynamic_cast<CTile*>((*CTileMgr::Get_Instance()->Get_TileList())[iIndex])->Get_Select())
		{
			if (CObjMgr::Get_Instance()->Get_ObjList(OBJ)->size() == 0)
			{
				CObj* pObj = CAbstractFactory<CWood>::Create((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX, (*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY);
				pObj->Set_FrameKey(L"Wood");
				CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
				CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
				CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 1);
			}
			else
			{
				for (auto& Buff : *(CObjMgr::Get_Instance()->Get_ObjList(OBJ)))
				{
					if (((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX == Buff->Get_Info().fX) && ((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY == Buff->Get_Info().fY))
						return;
				}
				CObj* pObj = CAbstractFactory<CWood>::Create((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX, (*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY);
				pObj->Set_FrameKey(L"Wood");
				CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
				CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
				CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 1);

			}
		}


	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing('Y')) //����
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		int		iX = pt.x / TILECX;
		int		iY = pt.y / TILECY;

		int		iIndex = iY * TILEX + iX;

		if (0 > iIndex || CTileMgr::Get_Instance()->Get_TileList()->size() <= (size_t)iIndex)
			return;

		if (dynamic_cast<CTile*>((*CTileMgr::Get_Instance()->Get_TileList())[iIndex])->Get_Select())
		{
			if (CObjMgr::Get_Instance()->Get_ObjList(OBJ)->size() == 0)
			{
				CObj* pObj = CAbstractFactory<CTree>::Create((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX, (*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY);
				pObj->Set_FrameKey(L"Tree");
				CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
				CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
				CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 1);
			}
			else
			{
				for (auto& Buff : *(CObjMgr::Get_Instance()->Get_ObjList(OBJ)))
				{
					if (((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX == Buff->Get_Info().fX) && ((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY == Buff->Get_Info().fY))
						return;
				}
				CObj* pObj = CAbstractFactory<CTree>::Create((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX, (*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY);
				pObj->Set_FrameKey(L"Tree");
				CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
				CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
				CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 1);

			}
		}


	}

	//else if (CKeyMgr::Get_Instance()->Key_Pressing('U')) //�� ����°�
	//{
	//	POINT	pt;
	//	GetCursorPos(&pt);
	//	ScreenToClient(g_hWnd, &pt);

	//	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//	int		iX = pt.x / TILECX;
	//	int		iY = pt.y / TILECY;

	//	int		iIndex = iY * TILEX + iX;

	//	if (0 > iIndex || CTileMgr::Get_Instance()->Get_TileList()->size() <= (size_t)iIndex)
	//		return;

	//	if (dynamic_cast<CTile*>((*CTileMgr::Get_Instance()->Get_TileList())[iIndex])->Get_Select())
	//	{
	//		if (CObjMgr::Get_Instance()->Get_ObjList(OBJ)->size() == 0)
	//		{
	//			CObj* pObj = CAbstractFactory<CBan>::Create((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX, (*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY);
	//			pObj->Set_FrameKey(L"Ban");
	//			CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
	//			CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
	//			CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 1);
	//		}
	//		else
	//		{
	//			for (auto& Buff : *(CObjMgr::Get_Instance()->Get_ObjList(OBJ)))
	//			{
	//				if (((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX == Buff->Get_Info().fX) && ((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY == Buff->Get_Info().fY))
	//					return;
	//			}
	//			CObj* pObj = CAbstractFactory<CBan>::Create((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX, (*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY);
	//			pObj->Set_FrameKey(L"Ban");
	//			CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
	//			CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
	//			CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 1);

	//		}
	//	}


	//}

	//else if (CKeyMgr::Get_Instance()->Key_Pressing('U')) //����Ÿ�� ����°�... 
	//{
	//	POINT	pt;
	//	GetCursorPos(&pt);
	//	ScreenToClient(g_hWnd, &pt);

	//	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//	int		iX = pt.x / TILECX;
	//	int		iY = pt.y / TILECY;

	//	int		iIndex = iY * TILEX + iX;

	//	if (0 > iIndex || CTileMgr::Get_Instance()->Get_TileList()->size() <= (size_t)iIndex)
	//		return;

	//	if (dynamic_cast<CTile*>((*CTileMgr::Get_Instance()->Get_TileList())[iIndex])->Get_Select())
	//	{
	//		if (CObjMgr::Get_Instance()->Get_ObjList(OBJ)->size() == 0)
	//		{
	//			CObj* pObj = CAbstractFactory<CPuzzle>::Create((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX, (*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY);
	//			pObj->Set_FrameKey(L"PuzzleTile");
	//			CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
	//			CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
	//		}
	//		else
	//		{
	//			for (auto& Buff : *(CObjMgr::Get_Instance()->Get_ObjList(OBJ)))
	//			{
	//				if (((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX == Buff->Get_Info().fX) && ((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY == Buff->Get_Info().fY))
	//					return;
	//			}
	//			CObj* pObj = CAbstractFactory<CPuzzle>::Create((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX, (*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY);
	//			pObj->Set_FrameKey(L"PuzzleTile");
	//			CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
	//			CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();

	//		}
	//	}


	//}

	else if (CKeyMgr::Get_Instance()->Key_Pressing('U')) //��Ŭ�븸��°�... ����� ö���Ҽ������ϱ� ������������
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		int		iX = pt.x / TILECX;
		int		iY = pt.y / TILECY;

		int		iIndex = iY * TILEX + iX;

		if (0 > iIndex || CTileMgr::Get_Instance()->Get_TileList()->size() <= (size_t)iIndex)
			return;

		if (dynamic_cast<CTile*>((*CTileMgr::Get_Instance()->Get_TileList())[iIndex])->Get_Select())
		{
			if (CObjMgr::Get_Instance()->Get_ObjList(OBJ)->size() == 0)
			{
				CObj* pObj = CAbstractFactory<CKeg>::Create((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX, (*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY);
				pObj->Set_FrameKey(L"Keg");
				CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
				CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
				CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 1);
			}
			else
			{
				for (auto& Buff : *(CObjMgr::Get_Instance()->Get_ObjList(OBJ)))
				{
					if (((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX == Buff->Get_Info().fX) && ((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY == Buff->Get_Info().fY))
						return;
				}
				CObj* pObj = CAbstractFactory<CKeg>::Create((*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fX, (*CTileMgr::Get_Instance()->Get_TileList())[iIndex]->Get_Info().fY);
				pObj->Set_FrameKey(L"Keg");
				CObjMgr::Get_Instance()->Add_Object(OBJ, pObj);
				CObjMgr::Get_Instance()->Get_ObjList(OBJ)->back()->Initialize();
				CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 1);

			}
		}


	}

	else
	{
		m_eState = IDLE;
	}
}

void CPlayer::OffSet(void)
{
	int		iOffsetX = WINCX >> 1;
	int		iOffsetY = WINCY >> 1;
	float		fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	if (iOffsetX > m_tInfo.fX + fScrollX)
		CScrollMgr::Get_Instance()->Set_Scroll(iOffsetX - m_tInfo.fX , iOffsetY - m_tInfo.fY);

	if (iOffsetX < m_tInfo.fX + fScrollX)
		CScrollMgr::Get_Instance()->Set_Scroll(iOffsetX - m_tInfo.fX, iOffsetY - m_tInfo.fY);

	if (iOffsetY > m_tInfo.fY + fScrollY)
		CScrollMgr::Get_Instance()->Set_Scroll(iOffsetX - m_tInfo.fX, iOffsetY - m_tInfo.fY);

	if (iOffsetY < m_tInfo.fY + fScrollY)
		CScrollMgr::Get_Instance()->Set_Scroll(iOffsetX - m_tInfo.fX, iOffsetY - m_tInfo.fY);


	m_tRect.left += (LONG)CScrollMgr::Get_Instance()->Get_ScrollX();
	m_tRect.top += (LONG)CScrollMgr::Get_Instance()->Get_ScrollY();
	m_tRect.right += (LONG)CScrollMgr::Get_Instance()->Get_ScrollX();
	m_tRect.bottom += (LONG)CScrollMgr::Get_Instance()->Get_ScrollY();

}

void CPlayer::Scene_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case WALK:
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eState;
	}
}

void CPlayer::Make_Dirt()
{
	for (auto& iter : *(CTileMgr::Get_Instance()->Get_TileList()))
	{
		if (m_iHand == PICK)
		{
			if (dynamic_cast<CTile*>(iter)->Get_Select())
			{
				CSoundMgr::Get_Instance()->PlaySoundW(L"Pick.wav", CSoundMgr::EFFECT, 0.1f);
				if (CObjMgr::Get_Instance()->Get_ObjList(DIRT)->size() == 0)
				{
					CObj* pObj = CAbstractFactory<CDirt>::Create(iter->Get_Info().fX, iter->Get_Info().fY);
					pObj->Set_FrameKey(L"DirtTile");
					CObjMgr::Get_Instance()->Add_Object(DIRT, pObj);
					CObjMgr::Get_Instance()->Get_ObjList(DIRT)->back()->Initialize();
				}
				else
				{
					for (auto& Buff : *(CObjMgr::Get_Instance()->Get_ObjList(DIRT)))
					{
						if ((iter->Get_Info().fX == Buff->Get_Info().fX) && (iter->Get_Info().fY == Buff->Get_Info().fY))
							return;
					}
					CObj* pObj = CAbstractFactory<CDirt>::Create(iter->Get_Info().fX, iter->Get_Info().fY);
					pObj->Set_FrameKey(L"DirtTile");
					CObjMgr::Get_Instance()->Add_Object(DIRT, pObj);
					CObjMgr::Get_Instance()->Get_ObjList(DIRT)->back()->Initialize();

				}

				if ((CSceneMgr::Get_Instance()->Get_Scene() == SC_FARM) && dynamic_cast<CFarm*>(CSceneMgr::Get_Instance()->Get_NowScene())->Get_rain())
				{
					CObj* pObj = CAbstractFactory<CDirt>::Create(iter->Get_Info().fX, iter->Get_Info().fY);
					pObj->Set_FrameKey(L"WaterTile");
					CObjMgr::Get_Instance()->Add_Object(WATER, pObj);
					CObjMgr::Get_Instance()->Get_ObjList(WATER)->back()->Initialize();
					dynamic_cast<CDirt*>(CObjMgr::Get_Instance()->Get_ObjList(WATER)->back())->Set_Water(true);

				}
			}
		}
			
		else if (m_iHand == WATERING) //�����϶�
		{
			if (dynamic_cast<CTile*>(iter)->Get_Select()) //���õ� Ÿ�� Ŭ���ϸ�
			{
				if (CObjMgr::Get_Instance()->Get_ObjList(DIRT)->size() != 0) //��Ÿ���� �Ѱ� �̻��ϋ�
				{
					for (auto& Buff : *(CObjMgr::Get_Instance()->Get_ObjList(DIRT))) //��Ÿ�� ��ü�� ����
					{
						if ((iter->Get_Info().fX == Buff->Get_Info().fX) && (iter->Get_Info().fY == Buff->Get_Info().fY)) //��Ÿ���� ���� Ÿ�ϰ� ��ġ�ϸ�
						{
							CSoundMgr::Get_Instance()->PlaySoundW(L"water.wav", CSoundMgr::EFFECT, 0.3f);

							if (CObjMgr::Get_Instance()->Get_ObjList(WATER)->size() == 0) //���Ͱ� �Ѱ��� ������ �ٷ� ����
							{
								CObj* pObj = CAbstractFactory<CDirt>::Create(iter->Get_Info().fX, iter->Get_Info().fY);
								pObj->Set_FrameKey(L"WaterTile");
								CObjMgr::Get_Instance()->Add_Object(WATER, pObj);
								CObjMgr::Get_Instance()->Get_ObjList(WATER)->back()->Initialize();
								dynamic_cast<CDirt*>(CObjMgr::Get_Instance()->Get_ObjList(WATER)->back())->Set_Water(true);
							}
							else
							{
								for (auto& Buff2 : *(CObjMgr::Get_Instance()->Get_ObjList(WATER))) //���Ͱ� �ִٸ� �ߺ����� �ƴ��� ���� ����
								{
									if ((iter->Get_Info().fX == Buff2->Get_Info().fX) && (iter->Get_Info().fY == Buff2->Get_Info().fY))
										return;
								}

								CObj* pObj = CAbstractFactory<CDirt>::Create(iter->Get_Info().fX, iter->Get_Info().fY);
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

		else if (m_iHand == PARSNIPSEED) //�����϶�
		{
			if (dynamic_cast<CTile*>(iter)->Get_Select()) //���õ� Ÿ�� Ŭ���ϸ�
			{
				if (CObjMgr::Get_Instance()->Get_ObjList(DIRT)->size() != 0) //��Ÿ���� �Ѱ� �̻��ϋ�
				{
					for (auto& Buff : *(CObjMgr::Get_Instance()->Get_ObjList(DIRT))) //��Ÿ�� ��ü�� ����
					{
						if ((iter->Get_Info().fX == Buff->Get_Info().fX) && (iter->Get_Info().fY == Buff->Get_Info().fY)) //��Ÿ���� ���� Ÿ�ϰ� ��ġ�ϸ�
						{
							CSoundMgr::Get_Instance()->PlaySoundW(L"seed.wav", CSoundMgr::EFFECT, 0.3f);

							bool Seed = false;

							if (CObjMgr::Get_Instance()->Get_ObjList(SEED)->size() == 0) //������ �Ѱ��� ������ �ٷ� ����
							{
								CObj* pObj = CAbstractFactory<CParsnip>::Create(iter->Get_Info().fX, iter->Get_Info().fY);
								pObj->Set_FrameKey(L"CropsGrow");
								CObjMgr::Get_Instance()->Add_Object(SEED, pObj);
								CObjMgr::Get_Instance()->Get_ObjList(SEED)->back()->Initialize();
								dynamic_cast<CParsnip*>(CObjMgr::Get_Instance()->Get_ObjList(SEED)->back())->Set_Seed(true);
								Seed = true;
							}
							else
							{
								for (auto& Buff2 : *(CObjMgr::Get_Instance()->Get_ObjList(SEED))) //���Ӿ��� �ִٸ� �ߺ����� �ƴ��� ���� ����
								{
									if ((iter->Get_Info().fX == Buff2->Get_Info().fX) && (iter->Get_Info().fY == Buff2->Get_Info().fY))
										return;
								}

								CObj* pObj = CAbstractFactory<CParsnip>::Create(iter->Get_Info().fX, iter->Get_Info().fY);
								pObj->Set_FrameKey(L"CropsGrow");
								CObjMgr::Get_Instance()->Add_Object(SEED, pObj);
								CObjMgr::Get_Instance()->Get_ObjList(SEED)->back()->Initialize();
								dynamic_cast<CParsnip*>(CObjMgr::Get_Instance()->Get_ObjList(SEED)->back())->Set_Seed(true);
								Seed = true;
								

							}

							if (Seed)
							{
								for (auto& iter = (CInvenMgr::Get_Instance()->Get_vecInven())->begin(); iter != (CInvenMgr::Get_Instance()->Get_vecInven())->end(); ++iter) //���Ͱ� �ִٸ� �ߺ����� �ƴ��� ���� ����
								{
									if ((*iter)->Get_ItemID() == PARSNIPSEED)
									{
										if ((dynamic_cast<CParsnipSeed*>(*iter)->Get_Num()) == 1)
										{
											Safe_Delete(*iter);
											iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter);
											iter = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter, CAbstractFactory<CEmpty>::Create());
											return;;
										}
										else if ((dynamic_cast<CParsnipSeed*>(*iter)->Get_Num()) > 1)
										{
											dynamic_cast<CParsnipSeed*>(*iter)->Set_Num(-1);
											return;;
										}

									}
								}
							}
						}
					}
				}
			}
		}

		else if (m_iHand == PICKAX)
		{
			if (dynamic_cast<CTile*>(iter)->Get_Select()) //���õ� Ÿ�� Ŭ���ϸ�
			{
				if (CObjMgr::Get_Instance()->Get_ObjList(DIRT)->size() != 0) //��Ÿ���� �Ѱ� �̻��ϋ�
				{
					
					for (auto& Buff = (CObjMgr::Get_Instance()->Get_ObjList(DIRT))->begin(); Buff != (CObjMgr::Get_Instance()->Get_ObjList(DIRT))->end();) //���Ͱ� �ִٸ� �ߺ����� �ƴ��� ���� ����
					{
						if ((iter->Get_Info().fX == (*Buff)->Get_Info().fX) && (iter->Get_Info().fY == (*Buff)->Get_Info().fY)) //��Ÿ���� ���� Ÿ�ϰ� ��ġ�ϸ�
						{
							CSoundMgr::Get_Instance()->PlaySoundW(L"DirtX.wav", CSoundMgr::EFFECT, 0.1f);
							Safe_Delete(*Buff);
							Buff = CObjMgr::Get_Instance()->Get_ObjList(DIRT)->erase(Buff);
						}
						else
							++Buff;
					}
				}

				if (CObjMgr::Get_Instance()->Get_ObjList(WATER)->size() != 0) //��Ÿ���� �Ѱ� �̻��ϋ�
				{

					for (auto& Buff = (CObjMgr::Get_Instance()->Get_ObjList(WATER))->begin(); Buff != (CObjMgr::Get_Instance()->Get_ObjList(WATER))->end();) //���Ͱ� �ִٸ� �ߺ����� �ƴ��� ���� ����
					{
						if ((iter->Get_Info().fX == (*Buff)->Get_Info().fX) && (iter->Get_Info().fY == (*Buff)->Get_Info().fY)) //��Ÿ���� ���� Ÿ�ϰ� ��ġ�ϸ�
						{
							Safe_Delete(*Buff);
							Buff = CObjMgr::Get_Instance()->Get_ObjList(WATER)->erase(Buff);

						}
						else
							++Buff;
					}
				}

				if (CObjMgr::Get_Instance()->Get_ObjList(SEED)->size() != 0) //��Ÿ���� �Ѱ� �̻��ϋ�
				{

					for (auto& Buff = (CObjMgr::Get_Instance()->Get_ObjList(SEED))->begin(); Buff != (CObjMgr::Get_Instance()->Get_ObjList(SEED))->end();) //���Ͱ� �ִٸ� �ߺ����� �ƴ��� ���� ����
					{
						if ((iter->Get_Info().fX == (*Buff)->Get_Info().fX) && (iter->Get_Info().fY == (*Buff)->Get_Info().fY)) //��Ÿ���� ���� Ÿ�ϰ� ��ġ�ϸ�
						{
							Safe_Delete(*Buff);
							Buff = CObjMgr::Get_Instance()->Get_ObjList(SEED)->erase(Buff);
						}
						else
							++Buff;
					}
				}


				for (auto& Buff = (CObjMgr::Get_Instance()->Get_ObjList(OBJ))->begin(); Buff != (CObjMgr::Get_Instance()->Get_ObjList(OBJ))->end();) //���Ͱ� �ִٸ� �ߺ����� �ƴ��� ���� ����
				{
					if ((iter->Get_Info().fX == (*Buff)->Get_Info().fX) && (iter->Get_Info().fY == (*Buff)->Get_Info().fY) && (*Buff)->Get_ItemID() == ROCK)
					{
						CSoundMgr::Get_Instance()->PlaySoundW(L"Rock.wav", CSoundMgr::EFFECT, 0.1f);

						Safe_Delete(*Buff);
						Buff = CObjMgr::Get_Instance()->Get_ObjList(OBJ)->erase(Buff);
						dynamic_cast<CTile*>(iter)->Set_DrawID(0);
						dynamic_cast<CTile*>(iter)->Set_Option(0);

						bool Rock = false;

						for (auto& iter1 : *(CInvenMgr::Get_Instance()->Get_vecInven()))
						{
							if (iter1->Get_ItemID() == ROCK)
							{
								dynamic_cast<CRock*>(iter1)->Set_Num(1);
								Rock = true;
								break;
							}
						}

						if (!Rock)
						{
							for (auto iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->begin(); iter1 != CInvenMgr::Get_Instance()->Get_vecInven()->end(); ++iter1)
							{
								if ((*iter1)->Get_ItemID() == ITEM_END)
								{
									Safe_Delete(*iter1);
									iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter1);
									iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter1, CAbstractFactory<CRock>::Create());
									dynamic_cast<CRock*>(*iter1)->Set_Seed(0);
									break;
								}
							}
						}
					}
					else
						++Buff;

				}
			}
		}

		else if (m_iHand == AX)
		{
			if (dynamic_cast<CTile*>(iter)->Get_Select())
			{
				for (auto& Buff = (CObjMgr::Get_Instance()->Get_ObjList(OBJ))->begin(); Buff != (CObjMgr::Get_Instance()->Get_ObjList(OBJ))->end();) //���Ͱ� �ִٸ� �ߺ����� �ƴ��� ���� ����
				{
					if ((iter->Get_Info().fX == (*Buff)->Get_Info().fX) && (iter->Get_Info().fY == (*Buff)->Get_Info().fY) && (*Buff)->Get_ItemID() == TREE)
					{
						CSoundMgr::Get_Instance()->PlaySoundW(L"axe.wav", CSoundMgr::EFFECT, 0.1f);

						dynamic_cast<CTree*>(*Buff)->Set_Num(-1);

						if (dynamic_cast<CTree*>(*Buff)->Get_Apple())
						{
							dynamic_cast<CTree*>(*Buff)->Set_Apple(false);
							bool Apple = false;

							for (auto& iter1 : *(CInvenMgr::Get_Instance()->Get_vecInven()))
							{
								if (iter1->Get_ItemID() == APPLE)
								{
									dynamic_cast<CApple*>(iter1)->Set_Num(1);
									Apple = true;
									break;
								}
							}
							if (!Apple)
							{
								for (auto iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->begin(); iter1 != CInvenMgr::Get_Instance()->Get_vecInven()->end(); ++iter1)
								{
									if ((*iter1)->Get_ItemID() == ITEM_END)
									{
										Safe_Delete(*iter1);
										iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter1);
										iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter1, CAbstractFactory<CApple>::Create());
										dynamic_cast<CApple*>(*iter1)->Set_Seed(0);
										break;
									}
								}
							}
						}

						if (dynamic_cast<CTree*>(*Buff)->Get_Num() == 3)
						{
							dynamic_cast<CTree*>(*Buff)->Set_Cut(1);

							bool Wood = false;

							for (auto& iter1 : *(CInvenMgr::Get_Instance()->Get_vecInven()))
							{
								if (iter1->Get_ItemID() == WOOD)
								{
									dynamic_cast<CWood*>(iter1)->Set_Num(3);
									Wood = true;
									break;
								}
							}
							if (!Wood)
							{
								for (auto iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->begin(); iter1 != CInvenMgr::Get_Instance()->Get_vecInven()->end(); ++iter1)
								{
									if ((*iter1)->Get_ItemID() == ITEM_END)
									{
										Safe_Delete(*iter1);
										iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter1);
										iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter1, CAbstractFactory<CWood>::Create());
										dynamic_cast<CWood*>(*iter1)->Set_Seed(0);
										dynamic_cast<CWood*>(*iter1)->Set_Num(2);
										break;
									}
								}
							}


							++Buff;
						}
						else if (dynamic_cast<CTree*>(*Buff)->Get_Num() == 0)
						{
							Safe_Delete(*Buff);
							Buff = CObjMgr::Get_Instance()->Get_ObjList(OBJ)->erase(Buff);
							dynamic_cast<CTile*>(iter)->Set_DrawID(0);
							dynamic_cast<CTile*>(iter)->Set_Option(0);

							bool Wood = false;

							for (auto& iter1 : *(CInvenMgr::Get_Instance()->Get_vecInven()))
							{
								if (iter1->Get_ItemID() == WOOD)
								{
									dynamic_cast<CWood*>(iter1)->Set_Num(3);
									Wood = true;
									break;
								}
							}
							if (!Wood)
							{
								for (auto iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->begin(); iter1 != CInvenMgr::Get_Instance()->Get_vecInven()->end(); ++iter1)
								{
									if ((*iter1)->Get_ItemID() == ITEM_END)
									{
										Safe_Delete(*iter1);
										iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter1);
										iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter1, CAbstractFactory<CWood>::Create());
										dynamic_cast<CWood*>(*iter1)->Set_Seed(0);
										dynamic_cast<CWood*>(*iter1)->Set_Num(2);
										break;
									}
								}
							}
						}
						else
							++Buff;
					}
					else if ((iter->Get_Info().fX == (*Buff)->Get_Info().fX) && (iter->Get_Info().fY == (*Buff)->Get_Info().fY) && (*Buff)->Get_ItemID() == WOOD)
					{
						CSoundMgr::Get_Instance()->PlaySoundW(L"axe.wav", CSoundMgr::EFFECT, 0.1f);
						Safe_Delete(*Buff);
						Buff = CObjMgr::Get_Instance()->Get_ObjList(OBJ)->erase(Buff);
						dynamic_cast<CTile*>(iter)->Set_DrawID(0);
						dynamic_cast<CTile*>(iter)->Set_Option(0);

						bool Wood = false;

						for (auto& iter1 : *(CInvenMgr::Get_Instance()->Get_vecInven()))
						{
							if (iter1->Get_ItemID() == WOOD)
							{
								dynamic_cast<CWood*>(iter1)->Set_Num(1);
								Wood = true;
								break;
							}
						}
						if (!Wood)
						{
							for (auto iter1 = CInvenMgr::Get_Instance()->Get_vecInven()->begin(); iter1 != CInvenMgr::Get_Instance()->Get_vecInven()->end(); ++iter1)
							{
								if ((*iter1)->Get_ItemID() == ITEM_END)
								{
									Safe_Delete(*iter1);
									iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter1);
									iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter1, CAbstractFactory<CWood>::Create());
									dynamic_cast<CWood*>(*iter1)->Set_Seed(0);
									break;
								}
							}
						}
					}
					else
						++Buff;

				}
			}
		}

		else if (m_iHand == GUN)
		{
			POINT pt{};
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);
			m_sin = (pt.y - (m_tInfo.fY + CScrollMgr::Get_Instance()->Get_ScrollY())) / sqrtf((pt.x - (m_tInfo.fX + CScrollMgr::Get_Instance()->Get_ScrollX()))*(pt.x - (m_tInfo.fX + CScrollMgr::Get_Instance()->Get_ScrollX())) + (pt.y - (m_tInfo.fY + CScrollMgr::Get_Instance()->Get_ScrollY()))*(pt.y - (m_tInfo.fY + CScrollMgr::Get_Instance()->Get_ScrollY())));
			m_cos = (pt.x - (m_tInfo.fX + CScrollMgr::Get_Instance()->Get_ScrollX())) / sqrtf((pt.x - (m_tInfo.fX + CScrollMgr::Get_Instance()->Get_ScrollX()))*(pt.x - (m_tInfo.fX + CScrollMgr::Get_Instance()->Get_ScrollX())) + (pt.y - (m_tInfo.fY + CScrollMgr::Get_Instance()->Get_ScrollY()))*(pt.y - (m_tInfo.fY + CScrollMgr::Get_Instance()->Get_ScrollY())));
			

				if (m_dwTime + 50 < GetTickCount()) {

					CSoundMgr::Get_Instance()->PlaySoundW(L"bullet.wav", CSoundMgr::EFFECT, 0.1f);
					CObj* pBullet = new CBullet;
					pBullet->Initialize();
					dynamic_cast<CBullet*>(pBullet)->Set_Pos(m_tInfo.fX, m_tInfo.fY);
					dynamic_cast<CBullet*>(pBullet)->Set_Tri(m_sin, m_cos);
					CObjMgr::Get_Instance()->Get_ObjList(BULLET)->push_back(pBullet);

					m_dwTime = GetTickCount();
			}
		}

		else if (m_iHand == PARSNIP)
		{
			if (dynamic_cast<CTile*>(iter)->Get_Select())
			{
				for (auto& Buff = (CObjMgr::Get_Instance()->Get_ObjList(OBJ))->begin(); Buff != (CObjMgr::Get_Instance()->Get_ObjList(OBJ))->end();++Buff) //���Ͱ� �ִٸ� �ߺ����� �ƴ��� ���� ����
				{
					if ((iter->Get_Info().fX == (*Buff)->Get_Info().fX) && (iter->Get_Info().fY == (*Buff)->Get_Info().fY) && (*Buff)->Get_ItemID() == KEG)
					{
						if (!(dynamic_cast<CKeg*>(*Buff)->Get_Parsnip()))
						{
							CSoundMgr::Get_Instance()->PlaySoundW(L"Keg.wav", CSoundMgr::EFFECT, 0.1f);
							dynamic_cast<CKeg*>(*Buff)->Set_Parsnip(true);

							for (auto& iter1 = (CInvenMgr::Get_Instance()->Get_vecInven())->begin(); iter1 != (CInvenMgr::Get_Instance()->Get_vecInven())->end(); ++iter1) //���Ͱ� �ִٸ� �ߺ����� �ƴ��� ���� ����
							{
								if ((*iter1)->Get_ItemID() == PARSNIP)
								{
									if ((dynamic_cast<CParsnip*>(*iter1)->Get_Num()) == 1)
									{
										Safe_Delete(*iter1);
										iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).erase(iter1);
										iter1 = (*CInvenMgr::Get_Instance()->Get_vecInven()).insert(iter1, CAbstractFactory<CEmpty>::Create());
										return;;
									}
									else if ((dynamic_cast<CParsnip*>(*iter1)->Get_Num()) > 1)
									{
										dynamic_cast<CParsnip*>(*iter1)->Set_Num(-1);
										return;;
									}

								}
							}
						}
					}
				}
			}
		}

		else
			return;
	}

}
