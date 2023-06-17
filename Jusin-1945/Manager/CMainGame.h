#pragma once
#include "Define.h"
#include "Unit/Player.h"
#include "Unit/Monster.h"

#include "Projectile/Shield.h"
#include "Projectile/Laser.h"

#include "Projectile/Bullet/NormalBullet.h"
#include "Projectile/Bullet/GuidedBullet.h"

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

	int		m_iScore;
	TCHAR	m_szScore[32];

private:
	DWORD	m_dwTime;
	int		m_iTime;	// ½Ã°£
};

