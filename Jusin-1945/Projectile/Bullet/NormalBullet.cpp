#include "NormalBullet.h"
#include "Manager/CMainGame.h"

CNormalBullet::CNormalBullet()
{

}

CNormalBullet::~CNormalBullet()
{
	Release();
}

void CNormalBullet::Initialize(void)
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;

	m_fSpeed = 5.f;
}

int CNormalBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += (m_fSpeed * (cos(m_fRadian)));
	m_tInfo.fY -= (m_fSpeed * (sin(m_fRadian)));

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CNormalBullet::Late_Update(void)
{
}

void CNormalBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CNormalBullet::Release(void)
{

}

void CNormalBullet::Collide(CObj& _rDst)
{
    CGameObject* pGObj = dynamic_cast<CGameObject*>(&_rDst);
	if (nullptr != pGObj && this->Get_Owner() != pGObj 
		&& this->Get_TeamID() != pGObj->Get_TeamID())
	{
		if (pGObj->Get_StatusInfo().fHP > 0)
			pGObj->Get_StatusInfo().fHP -= 3;
		else if (pGObj->Get_StatusInfo().fHP <= 0)
			pGObj->Set_Dead();

		this->Set_Dead();
	}

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(&_rDst);
	if (nullptr != pPlayer && this->Get_Owner() != pPlayer
		&& this->Get_TeamID() != pPlayer->Get_TeamID())
	{
		if (pPlayer->Get_StatusInfo().fHP > 0)
			pPlayer->Get_StatusInfo().fHP -= 3;
		else if (pPlayer->Get_StatusInfo().fHP <= 0)
			pPlayer->Set_Dead();

		this->Set_Dead();
	}

	CMiniAirplane* pMini = dynamic_cast<CMiniAirplane*>(&_rDst);
	if (nullptr != pMini && this->Get_Owner() != pMini
		&& this->Get_TeamID() != pMini->Get_TeamID())
	{
		if (pMini->Get_StatusInfo().fHP > 0)
			pMini->Get_StatusInfo().fHP -= 3;
		else if (pMini->Get_StatusInfo().fHP <= 0)
			pMini->Set_Dead();

		this->Set_Dead();
	}
}