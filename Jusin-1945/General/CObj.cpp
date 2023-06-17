#include "CObj.h"

CObj::CObj() 
	: m_fSpeed(0.f), m_bDead(false), m_fAcceleration(0.f), m_fDistance(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
}

CObj::~CObj()
{
	
}

void CObj::Update_Rect()
{
	m_tRect.left	= LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5));
	m_tRect.top		= LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5));
	m_tRect.right	= LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5));
	m_tRect.bottom	= LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5));

}
