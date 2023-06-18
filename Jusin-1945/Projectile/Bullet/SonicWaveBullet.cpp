#include "SonicWaveBullet.h"
#include "Manager/CMainGame.h"

CSonicWaveBullet::CSonicWaveBullet()
{
}

CSonicWaveBullet::~CSonicWaveBullet()
{
	Release();
}

void CSonicWaveBullet::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 5.f;
}

int CSonicWaveBullet::Update()
{
	if (m_bDead == true) {
		return OBJ_DEAD;
	}
	m_tInfo.fY -= m_fSpeed * sin(m_fRadian);

	m_tInfo.fCX += 2.f;
	m_tInfo.fCY += 2.f;
	if (m_tInfo.fCX == 50.f && m_tInfo.fCY == 50.f)
	{
		m_tInfo.fCX == 50.f;
		m_tInfo.fCY == 50.f;
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CSonicWaveBullet::Late_Update()
{
	if (120 > this->Get_Info().fX || WINCX - 120 < this->Get_Info().fX
		|| 120 > this->Get_Info().fY || WINCY - 120 < this->Get_Info().fY)
	{
		m_bDead = true;
	}
}

void CSonicWaveBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CSonicWaveBullet::Release()
{
}

void CSonicWaveBullet::Collide(CObj& _rDst)
{
	CGameObject* pGObj = dynamic_cast<CGameObject*>(&_rDst);
	if (nullptr != pGObj && this->Get_Owner() != pGObj
		&& this->Get_TeamID() != pGObj->Get_TeamID())
	{
		pGObj->Set_Dead();
		this->Set_Dead();
	}
}