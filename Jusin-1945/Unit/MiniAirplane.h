#pragma once
#include "CObj.h"
#include "Projectile/Bullet/Bullet.h"
#include "Projectile/Bullet/NormalBullet.h"

class CMiniAirplane : public CObj
{
public:
	CMiniAirplane();
	virtual ~CMiniAirplane();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(CObj& _rDst) override;

public:
	void		Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }

private:
	CObj*		Create_NormalBullet(float _fMuzzleX, float _fMuzzleY); // -y�������θ� ������ �Ѿ� �߻�

private:
	list<CObj*>* m_pBullet;

private:
	int					m_iPrimaryWeapon_MaxDelay = 6;	// 0.1��
	int					m_iPrimaryWeapon_Delay = 0;		// �ֹ��� �߻� ������

};

