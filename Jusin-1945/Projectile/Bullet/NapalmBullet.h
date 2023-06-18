#pragma once
#include "Projectile/Bullet/Bullet.h"

class CNapalmBullet : public CBullet
{
public:
	CNapalmBullet();
	virtual ~CNapalmBullet();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize()			override;
	virtual int	 Update()				override;
	virtual void Late_Update()			override;
	virtual void Render(HDC hDC)		override;
	virtual void Release()				override;
	virtual void Collide(CObj& _rDst)	override;

private:
	int		m_iNapalmCount; //네이팜탄의 개수
	POINT		m_tCenter;
};

