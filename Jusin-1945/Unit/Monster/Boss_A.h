#pragma once
#include "Unit/Monster/Monster.h"


class CBoss_A : public CMonster
{
public:
	CBoss_A() {};
	~CBoss_A() {};

	bool m_bArrive = false;



public:

	virtual void Initialize(void)	override;
	virtual int  Update(void)		override;
	virtual void Late_Update(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;
	virtual void Collide(CObj& _rDst) 	override;
	virtual void TimeLimit(void)	override;

	CObj* Create_NormalBullet(float _fRadian, float _fMuzzleX, float _fMuzzleY);
	CObj* Create_GuidedBullet(float _fRadian, float _fMuzzleX, float _fMuzzleY);
};

