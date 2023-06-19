#pragma once

#define		WINCX	600
#define		WINCY	800
#define		PURE	= 0
#define		PI		3.141592f

#define		OBJ_DEAD	1
#define		OBJ_NOEVENT	0

typedef struct tagInfo {
	float	fX;		// ���� X
	float	fY;		// ���� Y
	float	fCX;	// ���� ����
	float	fCY;	// ���� ����

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
