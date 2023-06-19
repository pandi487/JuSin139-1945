#pragma once

#define		WINCX	600
#define		WINCY	800
#define		PURE	= 0
#define		PI		3.141592f

#define		OBJ_DEAD	1
#define		OBJ_NOEVENT	0

typedef struct tagInfo {
	float	fX;		// 중점 X
	float	fY;		// 중점 Y
	float	fCX;	// 가로 길이
	float	fCY;	// 세로 길이

	float	fDirX;
	float	fDirY;
} INFO;

enum OBJID { MANAGER, GENERATOR, LASER, PLAYER, BULLET, MONSTER, SHIELD, MINIAIRPLANE, MOUSE, SCORE, OBJID_END };

template<typename T>
void Safe_Delete(T& Temp) {
	if (Temp) {
		delete	Temp;
		Temp = nullptr;
	}
}

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif

extern	HWND	g_hWnd;
