#pragma once

#include "framework.h"
#include "Define.h"

class CObj {
public:
	CObj();
	virtual ~CObj();
	
public:
	void	Set_Pos(float _fX, float _fY) {
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual void 	Late_Update(void)	PURE;
	virtual void	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

protected:
	void	Update_Rect();

protected:
	INFO	m_tInfo;
	RECT	m_tRect;

	CObj*	m_pTarget;

	bool	m_bDead;
	
	float	m_fSpeed;
	float	m_fAcceleration;
	float	m_fDistance;
	float	m_fAngle;
};

