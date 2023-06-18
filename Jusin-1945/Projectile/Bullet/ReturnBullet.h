#pragma once
#include "Projectile/Bullet/Bullet.h"
class CReturnBullet :
    public CBullet
{
public:
    CReturnBullet();
    virtual ~CReturnBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(CObj& _rDst) override;

private:
	float m_fFollow_SpeedX = 0.f;
	
public:
	void Set_Follow_Speed(float value) { m_fFollow_SpeedX = value; }
};

