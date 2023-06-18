#include "Laser.h"

CLaser::CLaser() : m_iTime(0)
{
}

CLaser::~CLaser()
{
    Release();
}

void CLaser::Initialize(void)
{
    m_fDistance = 100.f;
}

int CLaser::Update(void)
{
    if (m_bDead)
        return OBJ_DEAD;

    if (m_dwTime + 1000 <= GetTickCount()) {
        m_dwTime = GetTickCount();
        m_iTime++;
    }

    m_tInfo.fCX = (const float)m_pTarget->Get_Info().fCX + m_fDistance;
    m_tInfo.fCY += (const float)m_fDistance;

    m_tInfo.fX = (const float)m_pTarget->Get_Info().fX;
    m_tInfo.fY = (const float)m_pTarget->Get_Info().fY - m_fDistance;

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CLaser::Late_Update(void)
{
    if (m_iTime == 5)
        m_bDead = true;

}

void CLaser::Render(HDC hDC)
{
    HBRUSH  hBrush, oldBrush;
    HPEN	hPen, oldPen;

    hBrush = CreateSolidBrush(RGB(255, 255, 102));		// 색 입히는 코드
    oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

    hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 102));
    oldPen = (HPEN)SelectObject(hDC, hPen);

    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    SelectObject(hDC, oldBrush);
    DeleteObject(hBrush);

    SelectObject(hDC, oldPen);
    DeleteObject(hPen);
}

void CLaser::Release(void)
{
}
