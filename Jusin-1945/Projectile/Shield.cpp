#include "Shield.h"

CShield::CShield() : m_iTime(0)
{
}

CShield::~CShield()
{
	Release();
}

void CShield::Initialize(void)
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;

	m_fSpeed = 5.f;
	m_fDistance = 100.f;
}

int CShield::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_dwTime + 1000 <= GetTickCount()) {
		m_dwTime = GetTickCount();
		m_iTime++;
	}

	m_fAngle += m_fSpeed;

	m_tInfo.fX = m_pTarget->Get_Info().fX + m_fDistance * cosf(m_fAngle * (PI / 180.f));
	m_tInfo.fY = m_pTarget->Get_Info().fY - m_fDistance * sinf(m_fAngle * (PI / 180.f));

	__super::Update_Rect();
	
	return OBJ_NOEVENT;
}

void CShield::Late_Update(void)
{
	if (m_iTime == 10)
		m_bDead = true;
}

void CShield::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CShield::Release(void)
{
}
