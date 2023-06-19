#include "MissileBullet.h"
#include "Manager/CMainGame.h"

CMissileBullet::CMissileBullet()
{
}

CMissileBullet::~CMissileBullet()
{
	Release();
}

void CMissileBullet::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 5.f;
	m_fAcceleration = 0.25;
}

int CMissileBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fSpeed += m_fAcceleration;

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY -= m_fSpeed;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMissileBullet::Late_Update(void)
{
}

void CMissileBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CMissileBullet::Release(void)
{
}

void CMissileBullet::Collide(CObj& _rDst)
{
    CGameObject* pGObj = dynamic_cast<CGameObject*>(&_rDst);
	if (nullptr != pGObj && this->Get_Owner() != pGObj 
		&& this->Get_TeamID() != pGObj->Get_TeamID())
	{
		if (pGObj->Get_StatusInfo().fHP > 0)
			pGObj->Get_StatusInfo().fHP -= 10;
		else if (pGObj->Get_StatusInfo().fHP <= 0)
			pGObj->Set_Dead();

		this->Set_Dead();
	}


}