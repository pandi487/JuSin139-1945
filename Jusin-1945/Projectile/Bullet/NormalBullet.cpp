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
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += (m_fSpeed * (cos(m_fRadian)));
	m_tInfo.fY -= (m_fSpeed * (sin(m_fRadian)));

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CNormalBullet::Late_Update(void)
{
}

void CNormalBullet::Render(HDC hDC)
{
	//HBRUSH  hBrush, oldBrush;
	//HPEN	hPen, oldPen;

	//hBrush = CreateSolidBrush(RGB(255, 255, 153));		// 색 입히는 코드
	//oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	//hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 153));
	//oldPen = (HPEN)SelectObject(hDC, hPen);

	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	//SelectObject(hDC, oldBrush);
	//DeleteObject(hBrush);

	//SelectObject(hDC, oldPen);
	//DeleteObject(hPen);

}

void CNormalBullet::Release(void)
{

}

void CNormalBullet::Collide(CObj& _rDst)
{
    
}