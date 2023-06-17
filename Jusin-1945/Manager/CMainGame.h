#pragma once
#include "Define.h"
#include "Unit/Player.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render();
	void Release();

private:
	HDC		m_hDC;

	list<CObj*> m_ObjList[OBJID_END];
};

