#pragma once

#include "GameObject.h"
#include "Projectile/Bullet/NormalBullet.h"
#include "Projectile/Bullet/GuidedBullet.h"
#include "Projectile/Bullet/Bullet.h"
#include "Projectile/Shield.h"
#include "Projectile/Laser.h"


class CPlayer : public CGameObject
{

public:
	CPlayer();
	virtual ~CPlayer();

public:
	void		Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }
	void		Set_Enemy(list<CObj*>* pEnemy) { m_pEnemy = pEnemy; }
	// 플레이어에 총알 세팅 하면서 에너미리스트도 세팅 해줘야 유도총알이 나가요!

	void		Set_Shield(list<CObj*>* pShield) { m_pShield = pShield; }
	void		Set_Laser(list<CObj*>* pLaser) { m_pLaser = pLaser; }

public:
	virtual void Initialize(void)	override;
	virtual int  Update(void)		override;
	virtual void Late_Update(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

private:
	void		Draw_Body(HDC hDC);
	void		Key_Input(void);

private:
	CObj*		Create_NormalBullet(float _fMuzzleX, float _fMuzzleY); // -y방향으로만 나가는 총알 발사
	CObj*		Create_GuidedBullet(float _fMuzzleX, float _fMuzzleY); // 유도 총알 발사
	
	CObj*		Create_Shield();
	CObj*		Create_Laser();

private:
	list<CObj*>*		m_pBullet;
	list<CObj*>*		m_pEnemy;
	list<CObj*>*		m_pShield;
	list<CObj*>*		m_pLaser;
};

