#pragma once
#include "Unit/Monster/Monster.h"


class CMonster_TypeA : public CMonster
{
public:
	CMonster_TypeA() {};
	~CMonster_TypeA() {};

public:
	virtual void Initialize(void)		override;
	virtual int  Update(void)			override;
	virtual void Late_Update(void)		override;
	virtual void Render(HDC hDC)		override;
	virtual void Release(void)			override;

	virtual void Collide(CObj& _rDst) 	override;
	virtual void TimeLimit(void)		override;

	CObj* Create_Bullet(float _fRadian, float _fMuzzleX, float _fMuzzleY);
};

