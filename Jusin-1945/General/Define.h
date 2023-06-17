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
} INFO;

enum OBJID { PLAYER, BULLET, MONSTER, MOUSE, SHIELD, OBJID_END };

template<typename T>
void Safe_Delete(T& Temp) {
	if (Temp) {
		delete	Temp;
		Temp = nullptr;
	}
}

extern	HWND	g_hWnd;