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

public:
	void		Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }

private:
	CObj*	Create_NormalBullet(float _fMuzzleX, float _fMuzzleY); // -y방향으로만 나가는 총알 발사

private:
	list<CObj*>* m_pBullet;
	list<CObj*> m_ObjList[OBJID_END];
};

