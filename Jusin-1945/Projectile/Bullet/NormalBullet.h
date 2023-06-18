#pragma once
#include "Projectile/Bullet/Bullet.h"

class CNormalBullet		// Radian을 받으면 그 방향으로만 돌진하는 일반 총알
	: public CBullet
{
public:
	CNormalBullet();
	virtual ~CNormalBullet();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(CObj& _rDst) override;
};
