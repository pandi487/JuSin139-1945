#include "Unit/Monster/Monster_TypeB.h"
#include "AbstractFactory.h"
#include "Projectile/Bullet/NormalBullet.h"
#include "Manager/CMainGame.h"

void CMonster_TypeB::Initialize(void)
{
	m_tInfo = { 400.f, 500.f, 20.f, 20.f };
	m_fSpeed = 2.f;
	m_spinspeed = 300.f;
	m_isOnField = false;
	m_fAngle = 180;

	m_pBullet = &CMainGame::Get_Instance().Get_ObjList()[BULLET];
	m_pTarget = CMainGame::Get_Instance().Get_ObjFront(PLAYER);
}

int CMonster_TypeB::Update(void)
{
	m_fMove_Radian = m_fAngle * (PI / 180);

	if (m_bDead) {
		return OBJ_DEAD;
	}
	else {
		m_tInfo.fX += cos(m_fMove_Radian) * m_fSpeed;
		m_tInfo.fY -= sin(m_fMove_Radian) * m_fSpeed;

		if (m_isOnField) {
			TimeLimit();
			if (SwitchOn)
				m_pBullet->push_back(Create_Bullet(-m_fRadian, m_fMuzzleX, m_fMuzzleY));
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

}

void CMonster_TypeB::Late_Update(void)
{
	float fDistX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fDistY = m_pTarget->Get_Info().fY - m_tInfo.fY;

	if (fDistX <= 0) {
		m_fRadian = atan(fDistY / fDistX)+PI;
	}else
		m_fRadian = atan(fDistY/ fDistX);

	

	m_fMuzzleX = m_tInfo.fX + (cos(m_fRadian) * 30.f);
	m_fMuzzleY = m_tInfo.fY + (sin(m_fRadian) * 30.f);
}

void CMonster_TypeB::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CMonster_TypeB::Release(void)
{
}

void CMonster_TypeB::TimeLimit(void)
{
	DWORD waitTime = 500;
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


CObj* CMonster_TypeB::Create_Bullet(float _fRadian, float _fMuzzleX, float _fMuzzleY)
{
	CObj* pNormalBullet = CAbstractFactory<CNormalBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	CNormalBullet* pTemp = dynamic_cast<CNormalBullet*>(pNormalBullet);
	pNormalBullet->Initialize();
	pTemp->Set_Bulletinfo(_fRadian, _fMuzzleX, _fMuzzleY,10.f,3.f);
	

	return pNormalBullet;
}