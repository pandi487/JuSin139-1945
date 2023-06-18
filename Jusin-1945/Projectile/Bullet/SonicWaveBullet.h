#pragma once
#include "Projectile/Bullet/Bullet.h"

class CSonicWaveBullet : public CBullet
{
public:
	CSonicWaveBullet();
	virtual ~CSonicWaveBullet();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize()			override;
	virtual int	 Update()				override;
	virtual void Late_Update()			override;
	virtual void Render(HDC hDC)		override;
	virtual void Release()				override;
	virtual void Collide(CObj& _rDst)	override;

};

