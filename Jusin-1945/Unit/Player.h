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
	// �÷��̾ �Ѿ� ���� �ϸ鼭 ���ʹ̸���Ʈ�� ���� ����� �����Ѿ��� ������!

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
	CObj*		Create_NormalBullet(float _fMuzzleX, float _fMuzzleY);	 // -y�������θ� ������ �Ѿ� �߻�
	CObj*		Create_GuidedBullet(float _fMuzzleX, float _fMuzzleY);	 // ���� �Ѿ� �߻�
	CObj*		Create_MissileBullet(float _fMuzzleX, float _fMuzzleY);  // �̻��� �߻�
	
	CObj*		Create_Shield();
	CObj*		Create_Laser();
	CObj*		Create_Mini();		// �̴� �����

private:
	list<CObj*>*		m_pBullet;
	list<CObj*>*		m_pTarget;
	list<CObj*>*		m_pShield;
	list<CObj*>*		m_pLaser;
	list<CObj*>*		m_pMini;

private:
	int 				m_icount = 0;		// �ǵ� �� ����
};

