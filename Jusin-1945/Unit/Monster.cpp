#include "Monster.h"

CMonster::CMonster()
{
	m_isDead = false;
}

CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_tInfo = { (float)WINCX / 2.f, 120.f, 20.f, 20.f, 1, 0 };
	m_fSpeed = 2.f;
}

int CMonster::Update(void)
{
	if (m_isDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_ALIVE;
}

void CMonster::LateUpdate(void)
{
	
}

void CMonster::Render(HDC hDC)
{
	if (m_isDead)
		return;

	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CMonster::Release(void)
{
}