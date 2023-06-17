#include "Shield.h"

CShield::CShield()
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
	return OBJ_NOEVENT;
}

void CShield::Late_Update(void)
{
}

void CShield::Render(HDC hDC)
{
}

void CShield::Release(void)
{
}
