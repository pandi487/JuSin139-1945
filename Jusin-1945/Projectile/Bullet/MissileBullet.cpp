#include "MissileBullet.h"

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
	HBRUSH  hBrush, oldBrush;
	HPEN	hPen, oldPen;

	hBrush = CreateSolidBrush(RGB(255, 255, 153));		// 색 입히는 코드
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 153));
	oldPen = (HPEN)SelectObject(hDC, hPen);

	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);

	SelectObject(hDC, oldPen);
	DeleteObject(hPen);

}

void CMissileBullet::Release(void)
{
}
