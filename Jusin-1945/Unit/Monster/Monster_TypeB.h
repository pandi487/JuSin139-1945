#pragma once
#include "Unit/Monster/Monster.h"
class CMonster_TypeB : public CMonster
{
public:
	CMonster_TypeB() {};
	~CMonster_TypeB() {};

public:
	virtual void Initialize(void)	override;
	virtual int  Update(void)		override;
	virtual void Late_Update(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

	virtual void TimeLimit(void)	override;

	CObj* Create_Bullet(float _fRadian, float _fMuzzleX, float _fMuzzleY);
	
};
