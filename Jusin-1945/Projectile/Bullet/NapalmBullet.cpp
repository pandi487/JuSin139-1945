#include "NapalmBullet.h"
#include "Manager/CMainGame.h"

CNapalmBullet::CNapalmBullet()
{

}

CNapalmBullet::~CNapalmBullet()
{
	Release();
}

void CNapalmBullet::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
}

int CNapalmBullet::Update()
{
	if (m_bDead == true) {
		return OBJ_DEAD;
	}

	m_tInfo.fY -= m_fSpeed * sinf(m_fRadian);


	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CNapalmBullet::Late_Update()
{
	if (120 > this->Get_Info().fX || WINCX - 120 < this->Get_Info().fX
		|| 120 > this->Get_Info().fY || WINCY - 120 < this->Get_Info().fY)
	{
		m_bDead = true;
	}
}

void CNapalmBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

}

void CNapalmBullet::Release()
{
}

void CNapalmBullet::Collide(CObj& _rDst)
{
	CGameObject* pGObj = dynamic_cast<CGameObject*>(&_rDst);
	if (nullptr != pGObj && this->Get_Owner() != pGObj
		&& this->Get_TeamID() != pGObj->Get_TeamID())
	{
		pGObj->Set_Dead();
		this->Set_Dead();
	}
}