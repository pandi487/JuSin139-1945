#pragma once
#include "Define.h"
#include "Unit/Player.h"
#include "Unit/Monster/Monster.h"
#include "Unit/Monster/Monster_TypeA.h"

#include "Projectile/Shield.h"
#include "Projectile/Laser.h"
#include "Projectile/Bullet/NormalBullet.h"
#include "Projectile/Bullet/GuidedBullet.h"
#include "Projectile/Bullet/MissileBullet.h"
#include "Projectile/Bullet/Bomb.h"
#include "Projectile/Bullet/NapalmBullet.h"
#include "Projectile/Bullet/SonicWaveBullet.h"

#include "UI/Mouse.h"

#include "MonsterGenerateManager.h"

#include "UI/Score.h"

class CMainGame
{
private:
	CMainGame();
	~CMainGame();

	CMainGame& operator =(CMainGame& ref)
	{
		if (this == &ref)
			return *this;

		return *this;
	}

private:
	static CMainGame g_pInstance;

public:
	static CMainGame& Get_Instance()
	{
		return g_pInstance;
	}

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render();
	void Release();

private:
	HDC		m_hDC;

	list<CObj*> m_ObjList[OBJID_END];

	TCHAR	m_szTime[32];
	TCHAR	m_szName[32];

private:
	DWORD	m_dwTime;
	int		m_iTime;	// ½Ã°£

public:
	list<CObj*>* Get_ObjList() { return m_ObjList; }
	CObj* Get_ObjFront(int _OBJID) { return m_ObjList[_OBJID].front(); }
};

