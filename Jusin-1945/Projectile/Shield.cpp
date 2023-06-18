#include "Shield.h"
#include "Manager/CMainGame.h"

CShield::CShield() : m_iTime(0)
{
}

CShield::~CShield()
{
	Release();
}

void CShield::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

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
	if (m_iTime == 10)		// 10초 뒤에 삭제
		m_bDead = true;
}

void CShield::Render(HDC hDC)
{
	HBRUSH  hBrush, oldBrush;
	HPEN	hPen, oldPen;

	hBrush = CreateSolidBrush(RGB(0, 153, 0));		// 색 입히는 코드
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	hPen = CreatePen(PS_SOLID, 2, RGB(0, 153, 0));
	oldPen = (HPEN)SelectObject(hDC, hPen);

	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);

	SelectObject(hDC, oldPen);
	DeleteObject(hPen);

}

void CShield::Release(void)
{
}

void CShield::Collide(CObj& _rDst)
{
	CGameObject* pGObj = dynamic_cast<CGameObject*>(&_rDst);
	if (nullptr != pGObj && this->Get_Owner() != pGObj 
		&& this->Get_TeamID() != pGObj->Get_TeamID())
	{
		pGObj->Set_Dead();
	}

	CBullet* pBullet = dynamic_cast<CBullet*>(&_rDst);
	if (nullptr != pBullet && this->Get_Owner() != pBullet 
		&& this->Get_TeamID() != pBullet->Get_TeamID())
	{
		pBullet->Set_Dead();
	}


}