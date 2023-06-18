#pragma once

#include "CObj.h"

class CBullet abstract : public CObj
{

public:
	CBullet();
	virtual ~CBullet();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override		PURE;
	virtual int  Update(void) override			PURE;
	virtual void Late_Update(void) override		PURE;
	virtual void Render(HDC hDC) override		PURE;
	virtual void Release(void) override 		PURE;
	virtual void Collide(CObj& _rDst) override	PURE;

public:
	void Set_Bulletinfo(float _fRadian, float _Xpos, float _Ypos, float _size, float _speed);
	void Set_Bulletinfo(float _fRadian, float _Xpos, float _Ypos);
	void Set_Bulletinfo(float _Xpos, float _Ypos);

public:
	// 날아가는 방향
    float	m_fRadian;
	float	m_fDamage;
};

