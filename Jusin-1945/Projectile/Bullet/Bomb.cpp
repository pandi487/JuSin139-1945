#include "Bomb.h"
#include "Manager/CMainGame.h"

CBomb::CBomb() : b_Bomb(false)
{
}

CBomb::~CBomb()
{
	Release();
}

void CBomb::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 5.f;
}

int CBomb::Update()
{
	if (m_bDead == true) {
		return OBJ_DEAD;
	}
	First_Bomb();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CBomb::Late_Update()
{
	if (120 > this->Get_Info().fX || WINCX - 120 < this->Get_Info().fX
		|| 120 > this->Get_Info().fY || WINCY - 120 < this->Get_Info().fY)
	{
		m_bDead = true;
	}
}

void CBomb::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

}

void CBomb::Release()
{
}

void CBomb::Collide(CObj& _rDst)
{
	CGameObject* pGObj = dynamic_cast<CGameObject*>(&_rDst);
	if (nullptr != pGObj && this->Get_Owner() != pGObj
		&& this->Get_TeamID() != pGObj->Get_TeamID())
	{
		pGObj->Set_Dead();
		this->Set_Dead();
	}
}

void CBomb::First_Bomb()
{

	if (!b_Bomb)
	{
		m_tInfo.fCX += 5.f;
		m_tInfo.fCY += 5.f;
		if (m_tInfo.fCX >= 200.f && m_tInfo.fCY >= 200.f)
		{
			b_Bomb = true;
		}
	}

	if (b_Bomb)
	{
		m_tInfo.fCX -= 5.f;
		m_tInfo.fCY -= 5.f;
		if (m_tInfo.fCX <= 0.f && m_tInfo.fCY <= 0.f)
		{
			b_Bomb = false;
			m_bDead = true;
		}
		b_Bomb = true;
	}


}

void CBomb::Double_Bomb()
{
	if (!b_Bomb)
	{
		m_tInfo.fCX += 5.f;
		m_tInfo.fCY += 5.f;
		if (m_tInfo.fCX >= 200.f && m_tInfo.fCY >= 200.f)
		{
			b_Bomb = true;
		}
	}

	if (b_Bomb)
	{
		m_tInfo.fCX -= 5.f;
		m_tInfo.fCY -= 5.f;
		if (m_tInfo.fCX <= 0.f && m_tInfo.fCY <= 0.f)
		{
			b_Bomb = false;
			m_bDead = true;
		}
		b_Bomb = true;
	}
}
