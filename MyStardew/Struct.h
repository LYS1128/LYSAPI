#pragma once

typedef struct tagInfo
{
	float		fX;			// ������ X��ǥ
	float		fY;			// ������ Y��ǥ
	float		fCX;		// ���� ������
	float		fCY;		// ���� ������
}INFO;

typedef struct tagLinePos
{
	float		fX;
	float		fY;

	tagLinePos() { ZeroMemory(this, sizeof(tagLinePos)); }
	tagLinePos(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOS;


typedef struct tagLineInfo
{
	LINEPOS		tLeftPos;
	LINEPOS		tRightPos;

	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOS& tLeft, LINEPOS& tRight)
		: tLeftPos(tLeft), tRightPos(tRight) {}

}LINEINFO;

typedef struct	tagFrame
{
	int			iFrameStart;
	int			iFrameEnd;
	int			iFrameScene;

	DWORD		dwFrameSpeed;
	DWORD		dwFrameTime;

}FRAME;