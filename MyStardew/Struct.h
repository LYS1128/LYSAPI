#pragma once

typedef struct tagInfo
{
	float		fX;			// 중점의 X좌표
	float		fY;			// 중점의 Y좌표
	float		fCX;		// 가로 사이즈
	float		fCY;		// 세로 사이즈
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