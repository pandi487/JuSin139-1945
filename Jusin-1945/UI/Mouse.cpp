#include "UI/Mouse.h"

CMouse::CMouse()
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
}

int CMouse::Update(void)
{
	POINT	ptMouse{};

	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	__super::Update_Rect();
	ShowCursor(FALSE);

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
}

void CMouse::Render(HDC hDC)
{
	HPEN	hPen, oldPen;

	hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(hDC, hPen);

	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(hDC, m_tInfo.fX - 15.f, m_tInfo.fY, nullptr);
	LineTo(hDC, m_tInfo.fX + 15.f, m_tInfo.fY);
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY - 15.f, nullptr);
	LineTo(hDC, m_tInfo.fX, m_tInfo.fY + 15.f);

	SelectObject(hDC, oldPen);
	DeleteObject(hPen);

}

void CMouse::Release(void)
{
}

void CMouse::Collide(CObj& _rDst)
{
    
}