#pragma once

#include "GameObject.h"
#include "Projectile/Bullet/Bullet.h"
#include "Projectile/Bullet/NormalBullet.h"
#include "Projectile/Bullet/GuidedBullet.h"
#include "Projectile/Bullet/MissileBullet.h"

#include "Projectile/Shield.h"
#include "Projectile/Laser.h"
#include "MiniAirplane.h"


class CPlayer : public CGameObject
{

public:
	CPlayer();
	virtual ~CPlayer();

public:
	void		Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }
	void		Set_Target(list<CObj*>* pTarget) { m_pTarget = pTarget; }
	// 플레이어에 총알 세팅 하면서 에너미리스트도 세팅 해줘야 유도총알이 나가요!

	void		Set_Shield(list<CObj*>* pShield) { m_pShield = pShield; }
	void		Set_Laser(list<CObj*>* pLaser) { m_pLaser = pLaser; }
	void		Set_Mini(list<CObj*>* pMini) { m_pMini = pMini; }

public:
	virtual void Initialize(void)		override;
	virtual int  Update(void)			override;
	virtual void Late_Update(void)		override;
	virtual void Render(HDC hDC)		override;
	virtual void Release(void)			override;
	virtual void Collide(CObj& _rDst) 	override;

private:
	void		Draw_Body(HDC hDC);
	void		Key_Input(void);

private:
	CObj*		Create_NormalBullet(float _fMuzzleX, float _fMuzzleY);	 // -y방향으로만 나가는 총알 발사
	CObj*		Create_GuidedBullet(float _fMuzzleX, float _fMuzzleY);	 // 유도 총알 발사
	CObj*		Create_MissileBullet(float _fMuzzleX, float _fMuzzleY);  // 미사일 발사
	
	CObj*		Create_Shield();
	CObj*		Create_Laser();
	CObj*		Create_Mini();		// 미니 비행기

private:
	list<CObj*>*		m_pBullet;
	list<CObj*>*		m_pTarget;
	list<CObj*>*		m_pShield;
	list<CObj*>*		m_pLaser;
	list<CObj*>*		m_pMini;

private:
	int 				m_icount = 0;		// 실드 원 개수
};

