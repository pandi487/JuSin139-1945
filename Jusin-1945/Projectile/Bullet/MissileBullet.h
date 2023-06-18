#pragma once
#include "Projectile/Bullet/Bullet.h"
class CMissileBullet :		// 미사일 총알 (그냥 위로)
    public CBullet
{
public:
    CMissileBullet();
    virtual ~CMissileBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(CObj& _rDst) override;

};

