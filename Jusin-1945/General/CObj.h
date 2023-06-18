#pragma once

#include "framework.h"
#include "Define.h"

class CObj {
public:
	CObj();
	virtual ~CObj();
	
public:
	INFO	Get_Info() { return m_tInfo; }
	RECT&	Get_Rect() { return m_tRect; }
	bool 	Get_Dead() { return m_bDead; }

	void	Set_Pos(float _fX, float _fY) {
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void	Set_Dead(void) { m_bDead = true; }
	void	Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void	Set_Angle(float _fAngle) { m_fAngle = _fAngle; }

public:
	virtual void	Initialize(void)			PURE;
	virtual int		Update(void)				PURE;
	virtual void 	Late_Update(void)			PURE;
	virtual void	Render(HDC hDC)				PURE;
	virtual void	Release(void)				PURE;
	virtual void 	Collide(CObj& _rDst)	 	PURE;

protected:
	void	Update_Rect();
	void	Update_Timers();

protected:
	INFO	m_tInfo;
	RECT	m_tRect;

	CObj*	m_pTarget;
	CObj*	m_pBullet;

	bool	m_bDead;

	vector<DWORD>	m_dwTimers;

	// 주인놈
	CObj*	m_pOwner = nullptr;

	int 	m_iTeam;
	
	float	m_fSpeed;			// 속도
	float	m_fAcceleration;	// 가속도
	float	m_fDistance;		// 거리
	float	m_fAngle;			// 각도

protected:
	DWORD	m_dwTime = 0;			// 시간

public:
	void Set_Owner(CObj* value) { m_pOwner = value; }
	CObj* Get_Owner() { return m_pOwner; }

	void Set_Team(int value) { m_iTeam = value; }
	int Get_TeamID() { return m_iTeam; }
};

