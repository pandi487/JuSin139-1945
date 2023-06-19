#include "Unit/Monster/Monster_TypeA.h"
#include "AbstractFactory.h"
#include "Projectile/Bullet/NormalBullet.h"
#include "Manager/CMainGame.h"

void CMonster_TypeA::Initialize(void)
{
	__super::Initialize();

	m_tInfo = { 400.f, 500.f, 60.f, 60.f };
	m_StatusInfo = { 3.f, 3.f, false };

	m_fSpeed = 2.f;
	m_spinspeed = 300.f;
	m_isOnField = false;
	m_fAngle = 270.f;

	m_pBullet = &CMainGame::Get_Instance().Get_ObjList()[BULLET];

	
}

int CMonster_TypeA::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fMove_Radian = m_fAngle * (PI / 180);

	m_tInfo.fX += cos(m_fMove_Radian) * m_fSpeed;
	m_tInfo.fY -= sin(m_fMove_Radian) * m_fSpeed;

	if (m_isOnField) {
		TimeLimit();
		if (SwitchOn)
			m_pBullet->push_back(Create_Bullet(m_fRadian, m_tInfo.fX + m_fMuzzleX, m_tInfo.fY + m_fMuzzleY));
		if (125 > m_tInfo.fX || WINCX - 125 < m_tInfo.fX
			|| 125 > m_tInfo.fY || WINCY - 125 < m_tInfo.fY)
			Change_Angle();
	}
	else if (!m_isOnField) {
		if (125 < m_tInfo.fX && WINCX - 125 > m_tInfo.fX
			&& 125 < m_tInfo.fY && WINCY - 125 > m_tInfo.fY)
			m_isOnField = !m_isOnField;
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster_TypeA::Late_Update(void)
{
	if ( WINCY + 125 < m_tInfo.fY)
		m_bDead = true;

	m_fRadian += m_spinspeed;

	m_fMuzzleX = cos(m_fRadian) * 30.f;
	m_fMuzzleY = sin(m_fRadian) * 30.f;	// ÃÑ±¸È¸Àü
}

void CMonster_TypeA::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CMonster_TypeA::Release(void)
{
}

void CMonster_TypeA::Collide(CObj& _rDst)
{
	
}

void CMonster_TypeA::TimeLimit(void)
{
	DWORD dwCurrentTime = GetTickCount64();
	if (dwCurrentTime - m_dwTime >= 1)
	{
		SwitchOn = false;
	}
	if (dwCurrentTime - m_dwTime >= 800)
	{
		SwitchOn = true;
		m_dwTime = dwCurrentTime;
	}
}

CObj* CMonster_TypeA::Create_Bullet(float _fRadian, float _fMuzzleX, float _fMuzzleY)
{
	CNormalBullet* pCreated = dynamic_cast<CNormalBullet*>(
								CAbstractFactory<CNormalBullet>::Create());
	pCreated->Set_Bulletinfo(_fRadian, _fMuzzleX, _fMuzzleY);
	pCreated->Set_Owner(this);
	pCreated->Set_Team(this->m_iTeam);

	return pCreated;
}