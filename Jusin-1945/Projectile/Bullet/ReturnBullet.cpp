#include "ReturnBullet.h"
#include "Manager/CMainGame.h"

CReturnBullet::CReturnBullet()
{
}

CReturnBullet::~CReturnBullet()
{
	Release();
}

void CReturnBullet::Initialize(void)
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;

	m_fSpeed = 5.f;
	m_fAcceleration = -0.02;
}

int CReturnBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	while (m_fSpeed == 0) {
		m_fSpeed += m_fAcceleration;
	}
	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY -= m_fSpeed;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CReturnBullet::Late_Update(void)
{
}

void CReturnBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CReturnBullet::Release(void)
{
}

void CReturnBullet::Collide(CObj& _rDst)
{
	CGameObject* pGObj = dynamic_cast<CGameObject*>(&_rDst);
	if (nullptr != pGObj && this->Get_Owner() != pGObj 
		&& this->Get_TeamID() != pGObj->Get_TeamID())
	{
		pGObj->Set_Dead();
		this->Set_Dead();
	}
}