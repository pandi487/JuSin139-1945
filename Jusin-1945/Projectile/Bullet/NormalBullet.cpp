#include "NormalBullet.h"

CNormalBullet::CNormalBullet()
{

}

CNormalBullet::~CNormalBullet()
{
	Release();
}

void CNormalBullet::Initialize(void)
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 5.f;
}

int CNormalBullet::Update(void)
{
	if (m_bDead == true) {
		return OBJ_DEAD;
	}

	m_tInfo.fX -= (m_fSpeed * (cos(m_fRadian)));
	m_tInfo.fY -= (m_fSpeed * (sin(m_fRadian)));

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CNormalBullet::Late_Update(void)
{
	
	if (120 > this->Get_Info().fX || WINCX - 120 < this->Get_Info().fX
		|| 120 > this->Get_Info().fY || WINCY - 120 < this->Get_Info().fY)
	{
		m_bDead = true;
	}
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
