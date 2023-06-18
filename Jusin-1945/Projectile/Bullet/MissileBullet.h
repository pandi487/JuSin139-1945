#pragma once
#include "Projectile/Bullet/Bullet.h"
class CMissileBullet :		// �̻��� �Ѿ� (�׳� ����)
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

