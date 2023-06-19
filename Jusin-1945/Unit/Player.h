#pragma once

#include "GameObject.h"
#include "Manager/CMainGame.h"

#include "Projectile/Bullet/Bullet.h"
#include "Projectile/Bullet/NormalBullet.h"
#include "Projectile/Bullet/GuidedBullet.h"
#include "Projectile/Bullet/MissileBullet.h"
#include "Projectile/Bullet/ReturnBullet.h"
#include "Projectile/Bullet/Bomb.h"
#include "Projectile/Bullet/NapalmBullet.h"
#include "Projectile/Bullet/SonicWaveBullet.h"

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
	TCHAR		m_szHp[32];

private:
	CObj*		Create_NormalBullet		(float _fMuzzleX, float _fMuzzleY);		// -y방향으로만 나가는 총알 발사
	CObj*		Create_GuidedBullet		(float _fMuzzleX, float _fMuzzleY);		// 유도 총알 발사
	CObj*		Create_MissileBullet	(float _fMuzzleX, float _fMuzzleY);		// 미사일 발사
	CObj*		Create_ReturnBullet		(float _fMuzzleX, float _fMuzzleY);		// 중간에 떨어지는 총알
	CObj*		Create_NapalmBullet		(float _fMuzzleX, float _fMuzzleY);		// 네이팜탄 발사
	CObj*		Create_Bomb		   		();										// 폭격기 발사
	CObj*		Create_CSonicWaveBullet	(float _fMuzzleX, float _fMuzzleY);		// 음파 발사
	
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
	int					m_iPrimaryWeapon_MaxDelay = 6;	// 0.1초
	int					m_iPrimaryWeapon_Delay = 0;		// 주무기 발사 딜레이

	int 				m_icount = 0;					// 실드 원 개수
	int 				m_iSonicWaveCount = 0; 			//음파 개수
	int 				m_iNapalm_Bomb_Count = 0; 		//네이팜탄 개수
};

