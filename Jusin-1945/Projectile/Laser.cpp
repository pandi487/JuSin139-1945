#include "Laser.h"

CLaser::CLaser()
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
    m_tInfo.fCX = (const float)m_pTarget->Get_Info().fCX + m_fDistance;
    m_tInfo.fCY = (const float)m_fDistance * 15;

    m_tInfo.fX = (const float)m_pTarget->Get_Info().fX;
    m_tInfo.fY = (const float)m_pTarget->Get_Info().fY - m_fDistance;

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CLaser::Late_Update(void)
{
}

void CLaser::Render(HDC hDC)
{
    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CLaser::Release(void)
{
}
