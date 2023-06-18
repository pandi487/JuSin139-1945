#pragma once
#include "Projectile/Bullet/Bullet.h"

class CBomb : public CBullet
{
public:
	CBomb();
	virtual ~CBomb();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize()			override;
	virtual int	 Update()				override;
	virtual void Late_Update()			override;
	virtual void Render(HDC hDC)		override;
	virtual void Release()				override;
	virtual void Collide(CObj& _rDst)	override;

public:
	void	First_Bomb();
	void	Double_Bomb();

	bool	b_Bomb;
};

